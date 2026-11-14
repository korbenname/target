"""Simulation bringup: MuJoCo plant + camera + vision + mission.

Launches:
  vision_sim          MuJoCo scene, FPV camera, quadrotor plant, platform state
  fc01_vision_image   vision_image_node: sim camera topic -> target estimate
  fc01_mission        (included) mission/guidance node -> /visioncontrol

The simulator applies the received /visioncontrol command exactly like a
flight controller would. This is the simulation counterpart of
`ros2 launch fc01_bringup robot.launch.py`.
"""

import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import (DeclareLaunchArgument, ExecuteProcess,
                            IncludeLaunchDescription, SetEnvironmentVariable,
                            UnsetEnvironmentVariable)
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    share = get_package_share_directory("fc01_vision_sim")
    mission_share = get_package_share_directory("fc01_mission")
    sim_params = os.path.join(share, "config", "sim.yaml")
    image_params = os.path.join(share, "config", "vision_image.yaml")
    mission_launch = os.path.join(
        mission_share, "launch", "mission.launch.py")

    headless = LaunchConfiguration("headless")
    control = LaunchConfiguration("control_enabled")
    debug = LaunchConfiguration("publish_debug_image")
    show_debug = LaunchConfiguration("show_debug")
    engage_mode = LaunchConfiguration("engage_mode")
    reset_after_impact = LaunchConfiguration("reset_after_impact_s")
    viewer_camera = LaunchConfiguration("viewer_camera")
    camera_pitch = LaunchConfiguration("camera_pitch_deg")
    use_vision_state = LaunchConfiguration("use_vision_state")
    control_debug = LaunchConfiguration("control_debug_hz")
    show_tuning = LaunchConfiguration("show_tuning_window")

    sim_node = Node(
        package="fc01_vision_sim",
        executable="vision_sim",
        name="fc01_vision_sim",
        output="screen",
        parameters=[
            sim_params,
            {
                "headless": ParameterValue(headless, value_type=bool),
                "engage_mode": ParameterValue(engage_mode, value_type=str),
                "reset_after_impact_s": ParameterValue(
                    reset_after_impact, value_type=float),
                "viewer_camera": ParameterValue(
                    viewer_camera, value_type=str),
                "camera_pitch_deg": ParameterValue(
                    camera_pitch, value_type=float),
            },
        ],
    )

    # Vision recognition for the simulated camera. This node belongs to the
    # shared vision package; its simulation parameters live here.
    vision_node = Node(
        package="fc01_vision",
        executable="vision_image_node",
        name="fc01_vision_image",
        output="screen",
        parameters=[
            image_params,
            {
                "publish_debug_image": ParameterValue(debug, value_type=bool),
                "show_tuning_window": ParameterValue(
                    show_tuning, value_type=bool),
                "camera_pitch_deg": ParameterValue(
                    camera_pitch, value_type=float),
            },
        ],
    )

    # Guidance is deployment-neutral; fc01_bringup starts the same node with
    # the real camera node instead.
    mission = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(mission_launch),
        launch_arguments={
            "control_enabled": control,
            "engage_mode": engage_mode,
            "use_vision_state": use_vision_state,
            "control_debug_hz": control_debug,
        }.items(),
    )

    # Annotated detection image (bounding box / centre) in its own window.
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
            "headless", default_value="false",
            description="Run without the MuJoCo viewer window."),
        DeclareLaunchArgument(
            "show_debug", default_value="false",
            description="Open an rqt_image_view window showing the annotated "
                        "detection image (implies publish_debug_image)."),
        DeclareLaunchArgument(
            "control_enabled", default_value="true",
            description="Run the mission and command the platform."),
        DeclareLaunchArgument(
            "publish_debug_image",
            default_value=LaunchConfiguration("show_debug"),
            description="Publish /fc01/vision/debug_image (defaults to the "
                        "value of show_debug)."),
        DeclareLaunchArgument(
            "viewer_camera", default_value="fpv",
            description="'fpv' shows the camera feed in the MuJoCo viewer; "
                        "'free' shows the third-person orbit view. "
                        "Press V in the viewer to toggle at runtime."),
        DeclareLaunchArgument(
            "show_tuning_window", default_value="true",
            description="Open the OpenCV slider window (HSV threshold, blob "
                        "filters, target diameter) next to the live camera "
                        "preview."),
        DeclareLaunchArgument(
            "engage_mode", default_value="push",
            description="'push' keeps pushing into the target after contact; "
                        "'impact' hits once; 'track' holds standoff_m."),
        DeclareLaunchArgument(
            "camera_pitch_deg", default_value="10.0",
            description="Camera mount pitch (positive = tilted up); passed "
                        "to the simulator and the vision node."),
        DeclareLaunchArgument(
            "use_vision_state", default_value="false",
            description="Close the loop on jikl_fc01_system/VisionState "
                        "instead of target_relative."),
        DeclareLaunchArgument(
            "control_debug_hz", default_value="0.0",
            description="Log the mission command and vision estimate at "
                        "this rate (0 = off); useful when tuning gains."),
        DeclareLaunchArgument(
            "reset_after_impact_s", default_value="0.0",
            description="Respawn the platform this many seconds after an "
                        "impact; 0 lets it fall."),
        sim_node,
        vision_node,
        mission,
        debug_viewer,
    ])
