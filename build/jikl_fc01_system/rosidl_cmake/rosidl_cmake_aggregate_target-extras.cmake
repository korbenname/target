# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target jikl_fc01_system::jikl_fc01_system
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${jikl_fc01_system_TARGETS}.
if(jikl_fc01_system_TARGETS AND NOT TARGET jikl_fc01_system::jikl_fc01_system)
  add_library(jikl_fc01_system::jikl_fc01_system INTERFACE IMPORTED)
  set_target_properties(jikl_fc01_system::jikl_fc01_system PROPERTIES
    INTERFACE_LINK_LIBRARIES "${jikl_fc01_system_TARGETS}")
endif()
