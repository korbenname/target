cmake_minimum_required(VERSION 3.16)
project(fc01_vision CXX)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED COMPONENTS core imgproc imgcodecs videoio highgui)
find_package(jikl_fc01_system REQUIRED)

# ---------------------------------------------------------------------------
# Pure OpenCV core. No ROS dependency, so it can be built and unit-tested even
# before the VisionState message package is available.
# ---------------------------------------------------------------------------
add_library(vision_core STATIC
  src/camera_source.cpp
  src/color_detector.cpp
  src/target_estimator.cpp
  src/vision_pipeline.cpp
  src/debug_draw.cpp
  src/tuning_window.cpp
)
target_include_directories(vision_core PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_include_directories(vision_core SYSTEM PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(vision_core PUBLIC ${OpenCV_LIBS})
target_compile_options(vision_core PRIVATE -Wall -Wextra -Wpedantic)

add_executable(vision_demo tools/vision_demo.cpp)
target_link_libraries(vision_demo PRIVATE vision_core)

add_executable(vision_core_selftest tools/vision_selftest.cpp)
target_link_libraries(vision_core_selftest PRIVATE vision_core)

if(BUILD_TESTING)
  enable_testing()
  add_test(NAME vision_core_selftest COMMAND vision_core_selftest)
endif()

# ---------------------------------------------------------------------------
# Shared ROS-side parameter loaders.
# ---------------------------------------------------------------------------
add_library(vision_ros_common STATIC src/param_utils.cpp)
target_include_directories(vision_ros_common PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
# ament_target_dependencies uses the plain signature in Humble.
target_link_libraries(vision_ros_common vision_core)
ament_target_dependencies(vision_ros_common rclcpp)

# ---------------------------------------------------------------------------
# The single field-mapping unit for jikl_fc01_system/msg/VisionState.
# Shared by both nodes so the output schema cannot drift between them.
# ---------------------------------------------------------------------------
add_library(vision_state_adapter STATIC src/vision_state_adapter.cpp)
target_include_directories(vision_state_adapter PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(vision_state_adapter vision_core)
ament_target_dependencies(vision_state_adapter rclcpp jikl_fc01_system)

# ---------------------------------------------------------------------------
# ROS-image node: used by the MuJoCo simulator and by any camera driver that
# publishes sensor_msgs/Image. Publishes target_relative and VisionState.
# ---------------------------------------------------------------------------
add_executable(vision_image_node src/vision_image_node.cpp)
target_link_libraries(vision_image_node vision_ros_common vision_state_adapter)
ament_target_dependencies(vision_image_node
  rclcpp
  std_msgs
  sensor_msgs
  geometry_msgs
  cv_bridge
)
install(TARGETS vision_image_node DESTINATION lib/${PROJECT_NAME})

# ---------------------------------------------------------------------------
# Direct-camera node: USB capture, publishes VisionState on /fc01/vision/state.
# ---------------------------------------------------------------------------
add_executable(fc01_vision_node
  src/main.cpp
  src/vision_node.cpp
)
# ament_target_dependencies uses the plain signature in Humble, so this
# target must not mix in keyword (PRIVATE/PUBLIC) link calls.
target_link_libraries(fc01_vision_node vision_ros_common vision_state_adapter)
ament_target_dependencies(fc01_vision_node
  rclcpp
  std_msgs
  sensor_msgs
  geometry_msgs
  cv_bridge
  jikl_fc01_system
)
install(TARGETS fc01_vision_node DESTINATION lib/${PROJECT_NAME})

install(TARGETS vision_demo vision_core_selftest
  DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY config launch
  DESTINATION share/${PROJECT_NAME})

ament_package()
