"""Real-aircraft bringup: USB camera vision + mission/guidance.

Launches:
  fc01_vision   fc01_vision_node: V4L2 camera -> /fc01/vision/state
  fc01_mission  mission node: guidance state machine -> /visioncontrol

The flight controller is expected to subscribe /visioncontrol (body-FRD
velocity + wz yaw rate) and publish /sim/platform_pose,
/sim/platform_velocity, /sim/platform_angular_velocity and
/sim/target_contact_force (names configurable in mission.yaml).

The simulation has its own bringup:
  ros2 launch fc01_vision_sim vision_sim.launch.py
"""

import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import (DeclareLaunchArgument, ExecuteProcess,
                            IncludeLaunchDescription,
                            SetEnvironmentVariable, UnsetEnvironmentVariable)
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    vision_share = get_package_share_directory("fc01_vision")
    mission_share = get_package_share_directory("fc01_mission")
    vision_params = os.path.join(vision_share, "config", "vision.yaml")
    mission_launch = os.path.join(
        mission_share, "launch", "mission.launch.py")

    control = LaunchConfiguration("control_enabled")
    engage_mode = LaunchConfiguration("engage_mode")
    control_debug = LaunchConfiguration("control_debug_hz")
    show_debug = LaunchConfiguration("show_debug")
    publish_debug = LaunchConfiguration("publish_debug_image")
    show_tuning = LaunchConfiguration("show_tuning_window")

    vision_node = Node(
        package="fc01_vision",
        executable="fc01_vision_node",
        name="fc01_vision",
        output="screen",
        parameters=[
            vision_params,
            {
                # visualization itself comes from vision.yaml; these are
                # one-off overrides for the individual outputs.
                "publish_debug_image": ParameterValue(
                    publish_debug, value_type=bool),
                "show_tuning_window": ParameterValue(
                    show_tuning, value_type=bool),
            },
        ],
    )

    # The real vision node publishes VisionState only (no target_relative),
    # so the mission must consume VisionState.
    mission = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(mission_launch),
        launch_arguments={
            "control_enabled": control,
            "engage_mode": engage_mode,
            "use_vision_state": "true",
            "control_debug_hz": control_debug,
        }.items(),
    )

    debug_viewer = ExecuteProcess(
        cmd=["env",
             "GSETTINGS_SCHEMA_DIR=/usr/share/glib-2.0/schemas",
             "ros2", "run", "rqt_image_view", "rqt_image_view",
             "/fc01/vision/debug_image"],
        output="screen",
        condition=IfCondition(show_debug),
    )

    return LaunchDescription([
        # Terminals opened from a snap-packaged editor (VS Code) inherit its
        # GTK/GIO paths. Any GTK-based window (the OpenCV tuning window, rqt)
        # then loads snap libraries and dies with a libpthread/GLIBC_PRIVATE
        # symbol error, so strip those variables for every launched process.
        UnsetEnvironmentVariable("GTK_PATH"),
        UnsetEnvironmentVariable("GTK_EXE_PREFIX"),
        UnsetEnvironmentVariable("GDK_PIXBUF_MODULE_FILE"),
        UnsetEnvironmentVariable("GIO_MODULE_DIR"),
        SetEnvironmentVariable(
            "GSETTINGS_SCHEMA_DIR", "/usr/share/glib-2.0/schemas"),
        DeclareLaunchArgument(
            "control_enabled", default_value="true",
            description="Run the mission and command the platform."),
        DeclareLaunchArgument(
            "engage_mode", default_value="push",
            description="'push' keeps pushing into the target after contact; "
                        "'impact' hits once; 'track' holds standoff_m."),
        DeclareLaunchArgument(
            "control_debug_hz", default_value="0.0",
            description="Log the mission command and vision estimate at "
                        "this rate (0 = off)."),
        DeclareLaunchArgument(
            "show_debug", default_value="false",
            description="Open rqt_image_view on /fc01/vision/debug_image "
                        "(implies publish_debug_image)."),
        DeclareLaunchArgument(
            "publish_debug_image",
            default_value=LaunchConfiguration("show_debug"),
            description="Publish the annotated detection image."),
        DeclareLaunchArgument(
            "show_tuning_window", default_value="false",
            description="Open the OpenCV slider window for HSV/shape tuning "
                        "(one-off override; the persistent switch is "
                        "visualization in fc01_vision/config/vision.yaml)."),
        vision_node,
        mission,
        debug_viewer,
    ])
