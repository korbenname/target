#include <memory>

#include <rclcpp/rclcpp.hpp>

#include "fc01_vision/vision_node.hpp"

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  rclcpp::NodeOptions options;
  auto node = std::make_shared<fc01_vision::VisionNode>(options);
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
