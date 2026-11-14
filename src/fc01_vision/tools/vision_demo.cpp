// Standalone demo: camera -> detector -> estimator -> console / preview.
// Exists so the vision chain can be verified before VisionState.msg is ready.
#include <chrono>
#include <cmath>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#include "fc01_vision/camera_source.hpp"
#include "fc01_vision/vision_pipeline.hpp"

namespace {

volatile std::sig_atomic_t g_stop = 0;

void onSignal(int) { g_stop = 1; }

fc01_vision::HsvRange defaultHsvRange() {
  fc01_vision::HsvRange range;
  range.h_min = 0;
  range.h_max = 10;
  range.s_min = 80;
  range.s_max = 255;
  range.v_min = 50;
  range.v_max = 255;
  return range;
}

bool parseHsv(const std::string& text, fc01_vision::HsvRange& range) {
  std::vector<int> values;
  std::string current;
  for (char c : text + ",") {
    if (c == ',') {
      if (!current.empty()) {
        try {
          values.push_back(std::stoi(current));
        } catch (const std::exception&) {
          return false;
        }
        current.clear();
      }
    } else if (c != ' ') {
      current.push_back(c);
    }
  }
  if (values.size() != 6) {
    return false;
  }
  range.h_min = values[0];
  range.h_max = values[1];
  range.s_min = values[2];
  range.s_max = values[3];
  range.v_min = values[4];
  range.v_max = values[5];
  return true;
}

void printUsage(const char* program) {
  std::printf(
      "Usage: %s [options]\n"
      "  --device N            V4L2 device index (default 0)\n"
      "  --width N             requested width (default 640)\n"
      "  --height N            requested height (default 480)\n"
      "  --fps N               requested fps (default 30)\n"
      "  --hsv h0,h1,s0,s1,v0,v1  add an HSV range (repeatable; default red)\n"
      "  --shape auto|rect|circle (default auto)\n"
      "  --target-width-m M    target physical width  (rectangle)\n"
      "  --target-height-m M   target physical height (rectangle)\n"
      "  --target-diameter-m M target physical diameter (circle)\n"
      "  --fx P --fy P --cx P --cy P   camera intrinsics\n"
      "  --hfov DEG            horizontal FOV when --fx is not given (60)\n"
      "  --frames N            stop after N frames (0 = run forever)\n"
      "  --headless            no preview window\n"
      "  --save PATH           save the first annotated frame as an image\n"
      "  --help\n",
      program);
}

}  // namespace

int main(int argc, char** argv) {
  fc01_vision::CameraConfig camera_config;
  fc01_vision::DetectorConfig detector_config;
  fc01_vision::EstimatorConfig estimator_config;
  fc01_vision::FilterConfig filter_config;

  detector_config.ranges = {defaultHsvRange()};
  detector_config.morph_kernel = 5;
  detector_config.blur_kernel = 5;
  detector_config.min_area_ratio = 0.002;
  detector_config.max_area_ratio = 0.5;

  double hfov_deg = 60.0;
  double fx = 0.0;
  double fy = 0.0;
  double cx = 0.0;
  double cy = 0.0;
  int frame_limit = 0;
  bool headless = false;
  std::string save_path;

  try {
    for (int i = 1; i < argc; ++i) {
      const std::string arg = argv[i];
      const auto next = [&]() -> std::string {
        if (i + 1 >= argc) {
          throw std::runtime_error("missing value for " + arg);
        }
        return argv[++i];
      };

      if (arg == "--device") {
        camera_config.device_index = std::stoi(next());
      } else if (arg == "--width") {
        camera_config.width = std::stoi(next());
      } else if (arg == "--height") {
        camera_config.height = std::stoi(next());
      } else if (arg == "--fps") {
        camera_config.fps = std::stoi(next());
      } else if (arg == "--hsv") {
        fc01_vision::HsvRange range;
        if (!parseHsv(next(), range)) {
          throw std::runtime_error("bad --hsv (want h0,h1,s0,s1,v0,v1)");
        }
        if (detector_config.ranges.size() == 1 &&
            detector_config.ranges[0].h_min == 0 &&
            detector_config.ranges[0].h_max == 10) {
          detector_config.ranges.clear();  // replace the built-in red range
        }
        detector_config.ranges.push_back(range);
      } else if (arg == "--shape") {
        detector_config.shape = next();
      } else if (arg == "--target-width-m") {
        estimator_config.target_width_m = std::stod(next());
      } else if (arg == "--target-height-m") {
        estimator_config.target_height_m = std::stod(next());
      } else if (arg == "--target-diameter-m") {
        estimator_config.target_diameter_m = std::stod(next());
      } else if (arg == "--fx") {
        fx = std::stod(next());
      } else if (arg == "--fy") {
        fy = std::stod(next());
      } else if (arg == "--cx") {
        cx = std::stod(next());
      } else if (arg == "--cy") {
        cy = std::stod(next());
      } else if (arg == "--hfov") {
        hfov_deg = std::stod(next());
      } else if (arg == "--frames") {
        frame_limit = std::stoi(next());
      } else if (arg == "--headless") {
        headless = true;
      } else if (arg == "--save") {
        save_path = next();
      } else if (arg == "--help" || arg == "-h") {
        printUsage(argv[0]);
        return 0;
      } else {
        throw std::runtime_error("unknown argument: " + arg);
      }
    }
  } catch (const std::exception& e) {
    std::cerr << "argument error: " << e.what() << "\n";
    printUsage(argv[0]);
    return 2;
  }

  std::signal(SIGINT, onSignal);
  std::signal(SIGTERM, onSignal);

  fc01_vision::CameraSource camera(
      camera_config, [](const std::string& message) {
        std::printf("[camera] %s\n", message.c_str());
        std::fflush(stdout);
      });

  if (!camera.start()) {
    std::cerr << "failed to start camera\n";
    return 1;
  }

  const int width =
      camera.actualWidth() > 0 ? camera.actualWidth() : camera_config.width;
  const int height =
      camera.actualHeight() > 0 ? camera.actualHeight() : camera_config.height;

  fc01_vision::CameraIntrinsics intrinsics;
  intrinsics.width = width;
  intrinsics.height = height;
  if (fx <= 0.0) {
    fx = 0.5 * static_cast<double>(width) /
         std::tan(hfov_deg * CV_PI / 360.0);
  }
  if (fy <= 0.0) {
    fy = fx;
  }
  if (cx <= 0.0) {
    cx = 0.5 * static_cast<double>(width);
  }
  if (cy <= 0.0) {
    cy = 0.5 * static_cast<double>(height);
  }
  intrinsics.fx = fx;
  intrinsics.fy = fy;
  intrinsics.cx = cx;
  intrinsics.cy = cy;

  std::printf("[demo] intrinsics fx=%.2f fy=%.2f cx=%.2f cy=%.2f (%dx%d)\n",
              fx, fy, cx, cy, width, height);
  std::printf("[demo] target rect=%.3fx%.3f m circle=%.3f m shape=%s\n",
              estimator_config.target_width_m, estimator_config.target_height_m,
              estimator_config.target_diameter_m,
              detector_config.shape.c_str());

  fc01_vision::VisionPipeline pipeline(detector_config, estimator_config,
                                       filter_config);

  int frames = 0;
  int timeouts = 0;
  bool saved = false;

  while (!g_stop) {
    cv::Mat frame;
    int64_t stamp_ns = 0;
    uint64_t seq = 0;
    if (!camera.waitNext(frame, stamp_ns, seq, 1000)) {
      if (!camera.running()) {
        break;
      }
      if (++timeouts > 5) {
        std::cerr << "camera produced no frames for 5 s, stopping\n";
        break;
      }
      continue;
    }
    timeouts = 0;

    const fc01_vision::TargetState state =
        pipeline.process(frame, intrinsics, stamp_ns);
    ++frames;

    std::printf(
        "[%5d] seq=%llu found=%d valid=%d range=%5.2f "
        "pos_frd=(%6.2f,%6.2f,%6.2f) vel=(%5.2f,%5.2f,%5.2f) "
        "pix=(%5.0f,%5.0f) %s\n",
        frames, static_cast<unsigned long long>(seq),
        state.detected ? 1 : 0, state.position_valid ? 1 : 0, state.distance,
        state.x, state.y, state.z, state.vx, state.vy, state.vz, state.u,
        state.v, state.reason.c_str());
    std::fflush(stdout);

    cv::Mat annotated;
    if (!headless || (!save_path.empty() && !saved)) {
      annotated = pipeline.drawDebug(frame);
    }

    if (!save_path.empty() && !saved) {
      if (cv::imwrite(save_path, annotated)) {
        std::printf("[demo] saved annotated frame to %s\n", save_path.c_str());
        saved = true;
      } else {
        std::cerr << "failed to write " << save_path << "\n";
      }
    }

    if (!headless) {
      cv::imshow("fc01_vision", annotated);
      const int key = cv::waitKey(1);
      if (key == 27 || key == 'q') {
        break;
      }
    }

    if (frame_limit > 0 && frames >= frame_limit) {
      break;
    }
  }

  camera.stop();
  if (!headless) {
    cv::destroyAllWindows();
  }

  std::printf("[demo] stopped after %d frames\n", frames);
  return 0;
}
