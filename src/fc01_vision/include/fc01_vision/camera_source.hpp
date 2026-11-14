#pragma once

#include <condition_variable>
#include <cstdint>
#include <functional>
#include <mutex>
#include <string>
#include <thread>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include "fc01_vision/types.hpp"

namespace fc01_vision {

// Threaded V4L2 capture. Frames are kept in a single "latest" slot so a slow
// consumer never builds up latency. Reopens the device automatically.
class CameraSource {
 public:
  using LogFn = std::function<void(const std::string&)>;

  explicit CameraSource(CameraConfig config, LogFn log = nullptr);
  ~CameraSource();

  CameraSource(const CameraSource&) = delete;
  CameraSource& operator=(const CameraSource&) = delete;

  bool start();
  void stop();

  // Blocks until a frame newer than the previous delivered one arrives.
  // Returns false on timeout or when the source has stopped.
  bool waitNext(cv::Mat& frame, int64_t& stamp_ns, uint64_t& seq,
                int timeout_ms = 1000);

  // Non-blocking copy of the latest frame.
  bool lastFrame(cv::Mat& frame, int64_t& stamp_ns, uint64_t& seq) const;

  bool running() const;
  int actualWidth() const;
  int actualHeight() const;

 private:
  void threadLoop();
  bool openCapture(cv::VideoCapture& cap);
  void log(const std::string& message) const;

  CameraConfig config_;
  LogFn log_;

  mutable std::mutex mutex_;
  std::condition_variable cv_;
  cv::Mat latest_;
  int64_t latest_stamp_ns_{0};
  uint64_t seq_{0};
  uint64_t delivered_seq_{0};
  bool have_frame_{false};
  bool running_{false};
  int actual_width_{0};
  int actual_height_{0};

  std::thread thread_;
};

}  // namespace fc01_vision
