import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    package_share = get_package_share_directory("fc01_vision")
    default_config = os.path.join(package_share, "config", "vision.yaml")

    show_debug = LaunchConfiguration("show_debug")

    config_arg = DeclareLaunchArgument(
        "config",
        default_value=default_config,
        description="Path to the fc01_vision parameter file",
    )
    show_debug_arg = DeclareLaunchArgument(
        "show_debug",
        default_value="false",
        description="Open an rqt_image_view window with the annotated "
                    "detection image (implies publish_debug_image).",
    )

    vision_node = Node(
        package="fc01_vision",
        executable="fc01_vision_node",
        name="fc01_vision",
        output="screen",
        parameters=[
            LaunchConfiguration("config"),
            {"publish_debug_image": ParameterValue(
                LaunchConfiguration("show_debug"), value_type=bool)},
        ],
    )

    # GSETTINGS_SCHEMA_DIR is forced back to the system dir because terminals
    # opened from a snap-packaged editor (e.g. VS Code) inherit GSettings
    # paths from the snap; any Qt/GTK window then aborts with
    # "Settings schema ... does not contain a key named 'antialiasing'".
    debug_viewer = ExecuteProcess(
        cmd=["env",
             "GSETTINGS_SCHEMA_DIR=/usr/share/glib-2.0/schemas",
             "ros2", "run", "rqt_image_view", "rqt_image_view",
             "/fc01/vision/debug_image"],
        output="screen",
        condition=IfCondition(show_debug),
    )

    return LaunchDescription([
        config_arg,
        show_debug_arg,
        vision_node,
        debug_viewer,
    ])
