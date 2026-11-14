"""Mission/guidance node only.

This launch is deployment-neutral: it starts the node that consumes vision +
platform state and publishes /visioncontrol. The vision source is provided by
the bringup:

  real aircraft   ros2 launch fc01_bringup robot.launch.py
  MuJoCo demo     ros2 launch fc01_vision_sim vision_sim.launch.py
                  (that launch includes this file)
"""

import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    share = get_package_share_directory("fc01_mission")
    mission_params = os.path.join(share, "config", "mission.yaml")

    control = LaunchConfiguration("control_enabled")
    engage_mode = LaunchConfiguration("engage_mode")
    use_vision_state = LaunchConfiguration("use_vision_state")
    control_debug = LaunchConfiguration("control_debug_hz")

    mission_node = Node(
        package="fc01_mission",
        executable="mission",
        name="fc01_mission",
        output="screen",
        parameters=[
            mission_params,
            {
                "control_enabled": ParameterValue(control, value_type=bool),
                "engage_mode": ParameterValue(engage_mode, value_type=str),
                "use_vision_state": ParameterValue(
                    use_vision_state, value_type=bool),
                "control_debug_hz": ParameterValue(
                    control_debug, value_type=float),
            },
        ],
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            "control_enabled", default_value="true",
            description="Run the mission and command the platform."),
        DeclareLaunchArgument(
            "engage_mode", default_value="push",
            description="'push' keeps pushing into the target after contact; "
                        "'impact' hits once; 'track' holds standoff_m."),
        DeclareLaunchArgument(
            "use_vision_state", default_value="false",
            description="Close the loop on jikl_fc01_system/VisionState "
                        "instead of target_relative. Real camera nodes need "
                        "this; the simulated image node publishes both."),
        DeclareLaunchArgument(
            "control_debug_hz", default_value="0.0",
            description="Log the mission command and vision estimate at "
                        "this rate (0 = off)."),
        mission_node,
    ])
