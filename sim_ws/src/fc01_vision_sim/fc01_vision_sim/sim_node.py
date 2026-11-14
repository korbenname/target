"""MuJoCo vision simulation node (plant + camera only).

Loop:
  MuJoCo renders the platform FPV camera
    -> /sim/camera/image_raw + /sim/camera/camera_info
  The MuJoCo viewer window itself shows the same FPV feed by default
  (viewer_camera=fpv), so the camera picture is visible while it runs.
  fc01_vision_image consumes it
    -> /fc01/vision/target_relative (FRD, metres)
  fc01_mission turns vision + platform state into a body-FRD velocity
  command on /visioncontrol. This node is the flight controller side of
  that contract: it applies the command with a velocity/attitude cascade
  that produces four rotor thrusts, and MuJoCo integrates the motion.
  Impacts are detected from real contacts with the target contact panel.

The platform state (pose, velocity, body rates) and the target contact
force are published for the mission node. The target itself is still a
mocap body with a scripted trajectory, so the target never gets knocked
away and the demo can loop.
"""

import math
import os
import random
import time

import mujoco
import numpy as np
import rclpy
from geometry_msgs.msg import (PointStamped, PoseStamped, Vector3Stamped)
from rclpy.node import Node
from rclpy.qos import (DurabilityPolicy, HistoryPolicy, QoSProfile,
                       ReliabilityPolicy)
from sensor_msgs.msg import CameraInfo, Image
from std_msgs.msg import Bool, Empty, Float32

from .scene import (CAMERA_POS, ROTOR_SPIN, build_scene, rotor_positions)

try:  # Package-share lookup makes the installed assets findable.
    from ament_index_python.packages import get_package_share_directory
except Exception:  # pragma: no cover - depends on the workspace
    get_package_share_directory = None

try:  # Guidance output, published by fc01_mission.
    from jikl_fc01_system.msg import VelocityCommand as VelocityCommandMsg
except Exception:  # pragma: no cover - depends on the workspace
    VelocityCommandMsg = None


SENSOR_QOS = QoSProfile(
    depth=5,
    history=HistoryPolicy.KEEP_LAST,
    reliability=ReliabilityPolicy.BEST_EFFORT,
    durability=DurabilityPolicy.VOLATILE,
)

# Physics steps spent catching up after a slow render, per loop iteration
# (12 * 5 ms = 60 ms of simulated time). Keeps a stalled frame from growing
# an unbounded backlog.
MAX_CATCHUP_STEPS = 12


def _stamp(node):
    return node.get_clock().now().to_msg()


class VisionSimNode(Node):
    def __init__(self):
        super().__init__("fc01_vision_sim")

        # ---- Parameters ---------------------------------------------------
        p = self.declare_parameter
        self.headless = bool(p("headless", False).value)
        self.render_width = int(p("render_width", 320).value)
        self.render_height = int(p("render_height", 240).value)
        self.render_fps = float(p("render_fps", 30.0).value)
        self.physics_hz = float(p("physics_hz", 200.0).value)
        self.camera_fovy_deg = float(p("camera_fovy_deg", 45.0).value)
        self.target_radius = float(p("target_radius", 0.25).value)
        self.target_x = float(p("target_x", 8.0).value)
        self.target_y = float(p("target_y", 0.0).value)
        self.target_base_z = float(p("target_base_z", 1.2).value)
        # When false the target plate is drawn fully transparent but still
        # collides: the map's own green light is the visible target and the
        # plate is only its contact proxy.
        self.target_visible = bool(p("target_visible", True).value)
        # Bounds of the random target around (target_x, target_y,
        # target_base_z).
        self.target_amp_y = float(p("target_amp_y", 0.8).value)
        self.target_amp_z = float(p("target_amp_z", 0.3).value)
        self.target_freq_hz = float(p("target_freq_hz", 0.15).value)
        self.target_motion = str(
            p("target_motion", "random").value).strip().lower()
        if self.target_motion not in ("random", "sinusoid", "static"):
            raise ValueError(
                "target_motion must be 'random', 'sinusoid' or 'static', "
                "got '%s'" % self.target_motion)
        self.target_segment_s = max(
            0.2, float(p("target_segment_s", 1.5).value))
        seed = int(p("target_random_seed", 0).value)
        self.traj_seed = (seed if seed != 0 else
                          random.SystemRandom().randrange(1, 1 << 30))
        self.traj_episode = 0
        self._waypoint_cache = {}
        self.platform_start = np.array([
            float(p("platform_start_x", 0.0).value),
            float(p("platform_start_y", 0.0).value),
            float(p("platform_start_z", 0.03).value),
        ])
        # Initial heading (0 = nose toward +x). On the RMUC field the target
        # sits at x=-8, so 180 deg puts the ball in view from takeoff instead
        # of behind the camera.
        self.platform_yaw = math.radians(
            float(p("platform_yaw_deg", 0.0).value))
        self.platform_quat0 = np.array([
            math.cos(0.5 * self.platform_yaw), 0.0, 0.0,
            math.sin(0.5 * self.platform_yaw)])
        # H landing pad painted on the map under the starting position.
        self.landing_pad = bool(p("landing_pad", True).value)
        self.pad_x = float(p("pad_x", self.platform_start[0]).value)
        self.pad_y = float(p("pad_y", self.platform_start[1]).value)
        self.pad_z = float(p("pad_z", 0.024).value)
        self.pad_size = float(p("pad_size", 0.9).value)
        self.pad_yaw_deg = float(p("pad_yaw_deg", 0.0).value)
        # Optional green circle painted on the map at the target.
        self.target_marker = bool(p("target_marker", False).value)
        self.target_marker_radius = float(
            p("target_marker_radius", 0.5).value)
        self.target_marker_z = float(p("target_marker_z", 0.002).value)
        # Optional STL model: appearance + convex-hull collision.
        self.platform_mesh = self._resolve_asset(
            str(p("platform_mesh", "").value))
        self.platform_mesh_hull = self._resolve_asset(
            str(p("platform_mesh_hull", "").value))
        self.platform_mesh_scale = float(
            p("platform_mesh_scale", 0.0).value)
        # The contact proxy is a thin vertical plate on the light's face, so
        # the contact normal is horizontal at any altitude and no vertical
        # offset is needed.
        self.target_proxy_dz = 0.0
        # engage_mode is owned by fc01_mission; the plant only needs to know
        # whether a contact ends the episode (impact/track) or starts the
        # sustained push (push).
        self.engage_mode = str(p("engage_mode", "push").value).strip().lower()
        if self.engage_mode not in ("track", "impact", "push"):
            raise ValueError(
                "engage_mode must be 'track', 'impact' or 'push', got '%s'"
                % self.engage_mode)
        # Safety cap on the commanded tilt while the target is in contact:
        # the sustained press only needs ~10 deg, and a tighter limit keeps
        # the airframe and camera steady during it.
        self.contact_max_tilt_deg = float(
            p("contact_max_tilt_deg", 22.0).value)
        # Apply /visioncontrol (the plant side of the FC contract). Off for
        # a "physics only" run.
        self.apply_vision_control = bool(
            p("apply_vision_control", True).value)
        self.vision_control_topic = str(
            p("vision_control_topic", "/visioncontrol").value)
        # Hold the last command for this long after a message; a stalled
        # guidance node then leaves the aircraft hovering.
        self.command_timeout_s = float(p("command_timeout_s", 0.5).value)
        # State topics for fc01_mission.
        self.pose_topic = str(
            p("platform_pose_topic", "/sim/platform_pose").value)
        self.velocity_topic = str(
            p("platform_velocity_topic", "/sim/platform_velocity").value)
        self.omega_topic = str(
            p("platform_angular_velocity_topic",
              "/sim/platform_angular_velocity").value)
        self.contact_force_topic = str(
            p("contact_force_topic", "/sim/target_contact_force").value)
        self.impact_topic = str(p("impact_topic", "/sim/impact").value)
        self.reset_event_topic = str(
            p("reset_event_topic", "/sim/reset_event").value)
        self.state_publish_hz = max(
            1.0, float(p("state_publish_hz", 100.0).value))
        self.velocity_tau = float(p("velocity_tau", 0.5).value)
        # Quadrotor plant.
        self.platform_mass = float(p("platform_mass", 1.0).value)
        self.platform_ixx = float(p("platform_ixx", 0.010).value)
        self.platform_iyy = float(p("platform_iyy", 0.010).value)
        self.platform_izz = float(p("platform_izz", 0.018).value)
        self.arm_length = float(p("arm_length", 0.16).value)
        self.rotor_max_thrust = float(p("rotor_max_thrust", 6.0).value)
        self.rotor_drag_m = float(p("rotor_drag_m", 0.015).value)
        self.motor_tau = float(p("motor_tau", 0.04).value)
        self.attitude_gain = float(p("attitude_gain", 25.0).value)
        self.attitude_damping = float(p("attitude_damping", 6.0).value)
        self.max_tilt_deg = float(p("max_tilt_deg", 30.0).value)
        # Camera mount pitch (positive = tilted up); must match the vision node.
        self.camera_pitch_deg = float(
            p("camera_pitch_deg", 10.0).value)
        # 只在发布的图像上叠加的“真机感”：镜头振动 + 传感器噪点。
        self.camera_shake_deg = float(
            p("camera_shake_deg", 0.15).value)
        self.camera_noise_lsb = float(
            p("camera_noise_lsb", 1.5).value)
        self._image_rng = np.random.default_rng(20261113)
        # Optional MJCF map (e.g. RMUC2027 field). Empty = flat checker
        # ground. Relative paths are tried against the working directory and
        # the workspace root.
        self.map_xml = self._resolve_map_path(
            str(p("map_xml", "").value))
        self.reset_after_impact_s = float(
            p("reset_after_impact_s", 0.0).value)
        # Recover automatically if the airframe tumbles off the map (e.g.
        # after a hard push): below z=-2 or beyond the field bounds the
        # heightfield no longer supports it and the episode is pointless.
        self.reset_out_of_bounds = bool(
            p("reset_out_of_bounds", True).value)
        self.publish_ground_truth = bool(p("publish_ground_truth", True).value)
        self.log_period_s = float(p("log_period_s", 2.0).value)
        self.image_topic = p("image_topic", "/sim/camera/image_raw").value
        self.camera_info_topic = p(
            "camera_info_topic", "/sim/camera/camera_info").value
        self.reset_topic = p("reset_topic", "/sim/reset").value
        # Which camera the MuJoCo viewer shows: "fpv" (camera feed) or
        # "free" (third-person orbit view).
        self.viewer_camera = str(
            p("viewer_camera", "fpv").value).strip().lower()
        if self.viewer_camera not in ("fpv", "free"):
            raise ValueError(
                "viewer_camera must be 'fpv' or 'free', got '%s'"
                % self.viewer_camera)

        # ---- MuJoCo -------------------------------------------------------
        pad = None
        if self.landing_pad:
            pad = (self.pad_x, self.pad_y, self.pad_z, self.pad_size,
                   math.radians(self.pad_yaw_deg))
        marker = None
        if self.target_marker:
            marker = (self.target_x, self.target_y, self.target_marker_z,
                      self.target_marker_radius)
        platform_mesh = self.platform_mesh
        platform_mesh_hull = self.platform_mesh_hull
        if platform_mesh and not platform_mesh_hull:
            self.get_logger().warn(
                "platform_mesh is set but platform_mesh_hull is missing; "
                "using the primitive frame")
            platform_mesh = None
        xml = build_scene(
            target_radius=self.target_radius,
            camera_fovy_deg=self.camera_fovy_deg,
            target_x=self.target_x,
            target_y=self.target_y,
            target_z=self.target_base_z,
            platform_z=float(self.platform_start[2]),
            arm_length=self.arm_length,
            mass=self.platform_mass,
            inertia=(self.platform_ixx, self.platform_iyy,
                     self.platform_izz),
            camera_pitch_deg=self.camera_pitch_deg,
            map_xml=self.map_xml,
            pad=pad,
            marker=marker,
            target_visible=self.target_visible,
            platform_mesh=platform_mesh,
            platform_mesh_hull=platform_mesh_hull,
            platform_mesh_scale=self.platform_mesh_scale,
            target_proxy_dz=self.target_proxy_dz,
        )
        self.model = mujoco.MjModel.from_xml_string(xml)
        self.data = mujoco.MjData(self.model)
        self.model.opt.timestep = 1.0 / max(self.physics_hz, 1.0)
        self.renderer = mujoco.Renderer(
            self.model, self.render_height, self.render_width)

        self.target_mocap = self._mocap_id("target")
        self.platform_body = mujoco.mj_name2id(
            self.model, mujoco.mjtObj.mjOBJ_BODY, "platform")
        self.target_geom = mujoco.mj_name2id(
            self.model, mujoco.mjtObj.mjOBJ_GEOM, "target_geom")
        # Geoms that belong to the aircraft and can touch the target. The
        # mesh model touches the light panel only with the flat "impact_bumper"
        # pad (the hull uses a separate contact class so it cannot catch the
        # map's collision heightfield); the primitive fallback uses
        # "frame"/"boom". Missing names resolve to -1, so drop those.
        self.drone_collision_geoms = set()
        for name in ("impact_bumper", "impact_hull", "frame", "boom"):
            gid = mujoco.mj_name2id(
                self.model, mujoco.mjtObj.mjOBJ_GEOM, name)
            if gid >= 0:
                self.drone_collision_geoms.add(gid)
        self.fpv_camera_id = mujoco.mj_name2id(
            self.model, mujoco.mjtObj.mjOBJ_CAMERA, "fpv")

        # Rotor geometry, inertia and the thrust -> wrench mixer.
        self.rotor_positions = np.array(
            rotor_positions(self.arm_length), dtype=float)
        self.inertia = np.array(
            [self.platform_ixx, self.platform_iyy, self.platform_izz])
        mixer = np.zeros((4, 4))
        mixer[0, :] = 1.0                                  # total thrust
        mixer[1, :] = self.rotor_positions[:, 1]           # roll
        mixer[2, :] = -self.rotor_positions[:, 0]          # pitch
        mixer[3, :] = np.array(ROTOR_SPIN) * self.rotor_drag_m  # yaw
        self.mixer_inv = np.linalg.inv(mixer)
        self.motor_thrust = np.full(
            4, self.platform_mass * 9.81 / 4.0)
        # The ball is green for the whole run (matching the green HSV
        # thresholds); a hit is reported through /sim/impact and the log.
        # An invisible proxy (target_visible=false) stays fully transparent
        # so only the map's real green light is ever seen by the camera.
        self.target_color = np.array(
            [0.05, 0.85, 0.15, 1.0] if self.target_visible
            else [0.0, 0.0, 0.0, 0.0])

        self.target_pos = self._target_position(0.0)
        self.platform_pos = self.platform_start.copy()
        self.platform_vel = np.zeros(3)
        self.data.qpos[0:3] = self.platform_start
        self.data.qpos[3:7] = self.platform_quat0
        self.data.qfrc_applied[:] = 0.0
        self._write_mocap()
        mujoco.mj_forward(self.model, self.data)

        # Vertical FOV -> pinhole intrinsics. MuJoCo uses square pixels.
        self.fy = (self.render_height / 2.0) / math.tan(
            math.radians(self.camera_fovy_deg) / 2.0)
        self.fx = self.fy
        self.cx = self.render_width / 2.0
        self.cy = self.render_height / 2.0

        # ---- ROS I/O ------------------------------------------------------
        self.image_pub = self.create_publisher(
            Image, self.image_topic, SENSOR_QOS)
        self.info_pub = self.create_publisher(
            CameraInfo, self.camera_info_topic, SENSOR_QOS)

        # Plant side of the flight-controller contract: fc01_mission sends
        # body-FRD velocity commands on /visioncontrol, exactly what a real
        # FC01 receives.
        self.vision_control_sub = None
        if self.apply_vision_control:
            if VelocityCommandMsg is not None:
                # Depth 1: this is a setpoint, not a stream. The guidance
                # publishes at 50 Hz and the plant's loop drains one
                # callback per iteration; with a deeper queue any hiccup
                # leaves the plant flying on commands that are hundreds of
                # milliseconds old (a queue of 10 at 50 Hz is ~200 ms of
                # delay, which excited a +-40 deg pitch oscillation).
                self.vision_control_sub = self.create_subscription(
                    VelocityCommandMsg, self.vision_control_topic,
                    self._on_vision_control,
                    QoSProfile(depth=1, history=HistoryPolicy.KEEP_LAST,
                               reliability=ReliabilityPolicy.RELIABLE))
                self.get_logger().info(
                    "applying %s from %s"
                    % ("jikl_fc01_system/VelocityCommand",
                       self.vision_control_topic))
            else:
                self.get_logger().warn(
                    "apply_vision_control=true but VelocityCommand is not "
                    "built; rebuild jikl_fc01_system (the platform will "
                    "hover)")
        self.last_command = None
        self.last_command_world = np.zeros(3)
        self.last_command_time = 0.0
        self.last_command_valid = False
        # Body-FRD yaw rate command from VelocityCommand.wz. Heading is
        # controlled as a rate only; there is no absolute yaw topic.
        self.wz_cmd = 0.0
        self.command_stale_logged = False
        self.bad_frame_logged = False

        # State consumed by fc01_mission and shown to the operator.
        self.platform_pose_pub = self.create_publisher(
            PoseStamped, self.pose_topic, 10)
        self.platform_velocity_pub = self.create_publisher(
            Vector3Stamped, self.velocity_topic, 10)
        self.platform_omega_pub = self.create_publisher(
            Vector3Stamped, self.omega_topic, 10)
        self.contact_force_pub = self.create_publisher(
            Float32, self.contact_force_topic, 10)
        self.impact_pub = self.create_publisher(Bool, self.impact_topic, 10)
        self.reset_event_pub = self.create_publisher(
            Empty, self.reset_event_topic, 10)
        self.last_state_time = 0.0
        # |contact force| with the target panel, refreshed on every state
        # publish and used for the in-contact tilt cap.
        self.contact_force = 0.0

        self.reset_sub = self.create_subscription(
            Empty, self.reset_topic, self._on_reset_request, 10)

        if self.publish_ground_truth:
            self.target_pose_pub = self.create_publisher(
                PoseStamped, "/sim/target_pose", 10)
            self.gt_relative_pub = self.create_publisher(
                PointStamped, "/sim/target_relative_gt", 10)

        self.last_v_cmd = np.zeros(3)
        self.impacted = False
        self.impact_time = 0.0
        self.pending_reset = False
        self.pending_camera_toggle = False
        self.last_data_time = 0.0

        self.start_time = time.monotonic()
        self.last_step_time = self.start_time
        self.last_log_time = self.start_time
        self.physics_accumulator = 0.0
        self.max_tilt_seen_deg = 0.0
        self.frames = 0

        self.get_logger().info(
            "scene: quadrotor m=%.2f kg, arm=%.2f m, max thrust=%.1f N/rotor; "
            "target at (%.2f, %.2f, %.2f) m, light d=%.2f m; camera fovy=%.1f "
            "deg (fx=%.1f), pitch up %.0f deg; start z=%.2f m; "
            "engage_mode=%s (contact ends the episode: %s)"
            % (self.platform_mass, self.arm_length,
               self.rotor_max_thrust, self.target_x, self.target_y,
               self.target_base_z, 2.0 * self.target_radius,
               self.camera_fovy_deg, self.fx, self.camera_pitch_deg,
               self.platform_start[2], self.engage_mode,
               "no" if self.engage_mode == "push" else "yes"))
        self.get_logger().info(
            "map: %s" % (self.map_xml if self.map_xml else
                         "flat checker ground (map_xml empty)"))

    # ---- Helpers ---------------------------------------------------------
    def _resolve_map_path(self, text):
        """Find an MJCF map file; None means the flat ground is used."""
        text = os.path.expanduser(text.strip())
        if not text:
            return None
        candidates = [text]
        if not os.path.isabs(text):
            candidates.append(os.path.join(os.getcwd(), text))
            # .../fc01_vision_sim/fc01_vision_sim/sim_node.py -> workspace root.
            workspace = os.path.abspath(os.path.join(
                os.path.dirname(__file__), os.pardir, os.pardir, os.pardir))
            candidates.append(os.path.join(workspace, text))
        for cand in candidates:
            if os.path.isfile(cand):
                return os.path.abspath(cand)
        self.get_logger().warn(
            "map_xml '%s' not found; using the flat ground" % text)
        return None

    def _resolve_asset(self, text):
        """Find a packaged mesh: share/assets first, then the source tree."""
        text = os.path.expanduser(text.strip())
        if not text:
            return None
        candidates = [text]
        if not os.path.isabs(text):
            roots = []
            if get_package_share_directory is not None:
                try:
                    roots.append(get_package_share_directory(
                        "fc01_vision_sim"))
                except Exception:
                    pass
            roots.append(os.path.abspath(os.path.join(
                os.path.dirname(__file__), os.pardir)))
            roots.append(os.getcwd())
            for root in roots:
                candidates.append(os.path.join(root, text))
                candidates.append(os.path.join(root, "assets", text))
                candidates.append(os.path.join(
                    os.path.dirname(__file__), "assets", text))
        for cand in candidates:
            if os.path.isfile(cand):
                return os.path.abspath(cand)
        self.get_logger().warn("asset '%s' not found" % text)
        return None

    def _mocap_id(self, body_name):
        body_id = mujoco.mj_name2id(
            self.model, mujoco.mjtObj.mjOBJ_BODY, body_name)
        if body_id < 0:
            raise RuntimeError("body not found: %s" % body_name)
        mocap_id = int(self.model.body_mocapid[body_id])
        if mocap_id < 0:
            raise RuntimeError("body is not mocap: %s" % body_name)
        return mocap_id

    def _write_mocap(self):
        self.data.mocap_pos[self.target_mocap] = self.target_pos
        self.data.mocap_quat[self.target_mocap] = np.array([1.0, 0, 0, 0])

    def _body_rotation(self):
        """Body-to-world rotation matrix."""
        return self.data.xmat[self.platform_body].reshape(3, 3).copy()

    def _tilt_deg(self):
        """Angle between the body z axis and world z (total roll+pitch)."""
        rotation = self._body_rotation()
        return math.degrees(math.acos(
            float(np.clip(rotation[2, 2], -1.0, 1.0))))

    def _camera_world_position(self):
        return (self.data.xpos[self.platform_body] +
                self._body_rotation() @ np.array(CAMERA_POS))

    def _ground_truth_relative_frd(self):
        """Target relative to the camera, in body FRD (same frame as vision)."""
        rel_world = self.target_pos - self._camera_world_position()
        rel_flu = self._body_rotation().T @ rel_world
        return np.array([rel_flu[0], -rel_flu[1], -rel_flu[2]])

    def _target_waypoint(self, index):
        """A reproducible random waypoint for this episode and segment."""
        cached = self._waypoint_cache.get(index)
        if cached is not None:
            return cached
        rng = random.Random(
            "%d:%d:%d" % (self.traj_seed, self.traj_episode, index))
        waypoint = np.array([
            self.target_x,
            self.target_y + rng.uniform(-self.target_amp_y,
                                        self.target_amp_y),
            self.target_base_z + rng.uniform(-self.target_amp_z,
                                             self.target_amp_z),
        ])
        self._waypoint_cache[index] = waypoint
        return waypoint

    def _target_position(self, t):
        if self.target_motion == "static":
            return np.array([self.target_x, self.target_y,
                             self.target_base_z])
        if self.target_motion == "sinusoid":
            phase = 2.0 * math.pi * self.target_freq_hz * t
            return np.array([
                self.target_x,
                self.target_y + self.target_amp_y * math.sin(phase),
                self.target_base_z +
                self.target_amp_z * math.sin(0.5 * phase),
            ])

        # Random waypoints joined by a smoothstep. Velocity is zero at each
        # waypoint, so the target never teleports, and the bob is bounded by
        # target_amp_y / target_amp_z.
        index = int(t // self.target_segment_s)
        alpha = (t - index * self.target_segment_s) / self.target_segment_s
        alpha = 0.5 - 0.5 * math.cos(math.pi * alpha)
        start = self._target_waypoint(index)
        end = self._target_waypoint(index + 1)
        return start + (end - start) * alpha

    def _on_vision_control(self, msg):
        """Receive a body-FRD velocity command from fc01_mission."""
        frame = str(msg.frame_id).strip().lower()
        if frame not in ("", "body_frd"):
            # Only the body-FRD contract is implemented; ignoring a
            # different frame is safer than misinterpreting it.
            if not self.bad_frame_logged:
                self.bad_frame_logged = True
                self.get_logger().warn(
                    "ignoring VelocityCommand frame_id='%s' (only "
                    "body_frd)" % msg.frame_id)
            return
        # Store as body FLU for logging and freeze the equivalent world
        # command here. The guidance computed this body command from the
        # attitude it last received; inverting it with the attitude at
        # application time would couple the command to attitude changes
        # that happened after the command was made. Converting once at
        # reception is the inverse of what the guidance did and matches how
        # the in-process controller consumed a world-frame command.
        body_flu = np.array(
            [float(msg.vx), -float(msg.vy), -float(msg.vz)])
        self.last_command = body_flu
        self.last_command_world = self._body_rotation() @ body_flu
        self.last_command_time = time.monotonic()
        self.last_command_valid = bool(msg.valid)
        wz = float(msg.wz)
        self.wz_cmd = wz if math.isfinite(wz) else 0.0
        self.command_stale_logged = False

    def _on_reset_request(self, _msg):
        self.pending_reset = True

    def _on_viewer_key(self, key):
        # GLFW key codes: R = reset, V = toggle camera view. The viewer's own
        # Reset button is detected separately from the data state.
        if key == 82:
            self.pending_reset = True
        elif key == 86:
            self.pending_camera_toggle = True

    def _toggle_viewer_camera(self, viewer):
        """Toggle between the FPV camera and the free orbit camera.

        Based on the viewer's actual camera state, so it stays in sync when
        the user switches with Esc or [ ] instead.
        """
        cam = viewer.cam
        showing_fpv = (
            cam.type == mujoco.mjtCamera.mjCAMERA_FIXED
            and cam.fixedcamid == self.fpv_camera_id)
        if showing_fpv:
            self._aim_viewer_at_platform(viewer)
            self.viewer_camera = "free"
        elif self.fpv_camera_id < 0:
            self.get_logger().warn("fpv camera not found")
            return
        else:
            cam.type = mujoco.mjtCamera.mjCAMERA_FIXED
            cam.fixedcamid = self.fpv_camera_id
            self.viewer_camera = "fpv"
        self.get_logger().info(
            "viewer camera: %s (V toggles, Esc=free, [ ]=fixed camera)"
            % self.viewer_camera)

    def _aim_viewer_at_platform(self, viewer):
        """Frame the aircraft in the free viewer camera.

        MuJoCo's default free camera fits the whole model: on the RMUC map
        that is an 18 m field, and the 0.32 m aircraft is a few pixels
        across. Put the orbit camera 2.4 m behind and above the airframe,
        looking along the nose, and track the airframe so it stays centred.
        """
        cam = viewer.cam
        pos = np.asarray(self.platform_pos, dtype=float)
        # Tracking keeps the aircraft centred while it flies and still lets
        # the mouse orbit/zoom around it (only azim/elev/distance change).
        cam.type = mujoco.mjtCamera.mjCAMERA_TRACKING
        cam.trackbodyid = self.platform_body
        cam.lookat[:] = (pos[0], pos[1], pos[2] + 0.10)
        cam.distance = 2.6
        # Camera position = lookat + d*(cos az, sin az, tan el). Sitting 45
        # deg off the tail instead of straight behind keeps both the aircraft
        # and the ball it is pushing visible.
        rot = self._body_rotation()
        cam.azimuth = math.degrees(math.atan2(rot[1, 0], rot[0, 0])) - 135.0
        cam.elevation = 30.0

    def _viewer_reset_requested(self):
        if self.data.time + 1e-9 < self.last_data_time:
            return True
        # The viewer's Reset also rewinds the target mocap to its XML pose.
        drift = np.max(np.abs(
            self.data.mocap_pos[self.target_mocap] - self.target_pos))
        return float(drift) > 1e-6

    # ---- Control ---------------------------------------------------------
    def _finish_impact(self, now, contact_force=0.0, approach_speed=None):
        self.impacted = True
        self.impact_time = now
        self.max_tilt_seen_deg = max(self.max_tilt_seen_deg, self._tilt_deg())
        # Cut the motors: from here on the drone is ballistic and falls.
        self.motor_thrust[:] = 0.0
        self.data.qfrc_applied[:] = 0.0
        hit = contact_force > 0.0
        center_distance = float(
            np.linalg.norm(self.target_pos - self.platform_pos))
        if approach_speed is None:
            approach_speed = float(np.linalg.norm(self.platform_vel))
        self.get_logger().info(
            "IMPACT hit=%s contact_force=%.1f N approach_speed=%.2f m/s "
            "max_tilt=%.0f deg "
            "ground_truth_center_distance=%.2f m (light r=%.2f m) "
            "platform=(%.2f, %.2f, %.2f)"
            % ("yes" if hit else "no", contact_force, approach_speed,
               self.max_tilt_seen_deg, center_distance, self.target_radius,
               self.platform_pos[0], self.platform_pos[1],
               self.platform_pos[2]))

    def _reset_simulation(self, now):
        self.impacted = False
        self.max_tilt_seen_deg = 0.0
        self.last_command = None
        self.last_command_world = np.zeros(3)
        self.last_command_valid = False
        self.wz_cmd = 0.0
        self.command_stale_logged = False
        self.model.geom_rgba[self.target_geom] = self.target_color
        self.start_time = now
        self.last_step_time = now
        self.physics_accumulator = 0.0
        # New episode, new random pattern (deterministic per seeded run).
        self.traj_episode += 1
        self._waypoint_cache.clear()
        self.target_pos = self._target_position(0.0)
        # Also reset MuJoCo's own state so the viewer's time display and any
        # internal state match; mocap positions are written back below.
        mujoco.mj_resetData(self.model, self.data)
        self.data.qpos[0:3] = self.platform_start
        self.data.qpos[3:7] = self.platform_quat0
        self.data.qvel[:] = 0.0
        self.data.qfrc_applied[:] = 0.0
        self.motor_thrust[:] = self.platform_mass * 9.81 / 4.0
        self._write_mocap()
        mujoco.mj_forward(self.model, self.data)
        self.platform_pos = self.data.qpos[0:3].copy()
        self.platform_vel[:] = 0.0
        self.last_data_time = self.data.time
        # Tell fc01_mission to restart its state machine from this pose.
        self.reset_event_pub.publish(Empty())
        self.get_logger().info("simulation reset")

    def _target_contact(self):
        force = np.zeros(6)
        for i in range(self.data.ncon):
            contact = self.data.contact[i]
            geom1 = int(contact.geom1)
            geom2 = int(contact.geom2)
            if not ((geom1 == self.target_geom and
                     geom2 in self.drone_collision_geoms) or
                    (geom2 == self.target_geom and
                     geom1 in self.drone_collision_geoms)):
                continue
            mujoco.mj_contactForce(self.model, self.data, i, force)
            return True, float(np.linalg.norm(force[:3]))
        return False, 0.0

    def _desired_rotation(self, body_z_desired, rotation):
        """Rotation matrix whose body z axis is the desired thrust direction.

        Heading is not constrained here: the desired yaw is taken from the
        current body x axis, so the attitude error contains only tilt. Yaw
        is commanded separately as a body rate (VelocityCommand.wz).
        """
        heading = np.array([rotation[0, 0], rotation[1, 0], 0.0])
        body_y = np.cross(body_z_desired, heading)
        norm = float(np.linalg.norm(body_y))
        if norm < 1e-6:
            body_y = np.cross(body_z_desired, np.array([0.0, 1.0, 0.0]))
            norm = float(np.linalg.norm(body_y))
            if norm < 1e-6:
                return np.eye(3)
        body_y /= norm
        body_x = np.cross(body_y, body_z_desired)
        return np.column_stack((body_x, body_y, body_z_desired))

    def _attitude_error(self, rotation_desired, rotation):
        skew = (rotation_desired.T @ rotation -
                rotation.T @ rotation_desired)
        return 0.5 * np.array([skew[2, 1], skew[0, 2], skew[1, 0]])

    def _command_velocity(self, v_cmd, max_tilt_deg=None):
        """Velocity + attitude cascade, then four rotor thrusts."""
        dt = self.model.opt.timestep
        velocity = self.data.qvel[0:3]
        accel_des = (v_cmd - velocity) / max(self.velocity_tau, 1e-3)

        accel_des[2] = float(np.clip(accel_des[2], -0.5 * 9.81, 1.5 * 9.81))

        # Tilt limit on the actual thrust direction: tilt is
        # atan(a_h / (g + a_z)), so the horizontal budget shrinks when the
        # vertical command is negative. Capping a_h against a fixed 9.81
        # (the old behaviour) let the nose pitch to ~47 deg while arresting
        # the climb right after takeoff - a visible lurch that also threw
        # the target out of the camera.
        if max_tilt_deg is None:
            max_tilt_deg = self.max_tilt_deg
        max_tilt = math.radians(max_tilt_deg)
        vertical_thrust = max(9.81 + accel_des[2], 0.1)
        max_horizontal = vertical_thrust * math.tan(max_tilt)
        horizontal = accel_des[:2].copy()
        h_norm = float(np.linalg.norm(horizontal))
        if h_norm > max_horizontal:
            accel_des[:2] = horizontal * (max_horizontal / h_norm)

        force = self.platform_mass * (
            accel_des + np.array([0.0, 0.0, 9.81]))
        force_norm = float(np.linalg.norm(force))
        if force_norm < 1e-9:
            force = np.array([0.0, 0.0, self.platform_mass * 9.81])
            force_norm = float(np.linalg.norm(force))
        total_thrust = min(force_norm, self.rotor_max_thrust * 4.0)
        direction = force / force_norm

        rotation = self._body_rotation()
        rotation_desired = self._desired_rotation(direction, rotation)
        error = self._attitude_error(rotation_desired, rotation)
        omega = self.data.qvel[3:6]
        # Yaw-rate feedforward: damping acts on (omega - omega_cmd), so a
        # moving yaw setpoint is tracked without building a lagging attitude
        # error. wz is body FRD (z down); qvel is body FLU (z up).
        omega_cmd = np.array([0.0, 0.0, -self.wz_cmd])
        torque = self.inertia * (
            -self.attitude_gain * error -
            self.attitude_damping * (omega - omega_cmd))

        wrench = np.array([total_thrust, torque[0], torque[1], torque[2]])
        thrust_cmd = np.clip(
            self.mixer_inv @ wrench, 0.0, self.rotor_max_thrust)
        alpha = min(1.0, dt / max(self.motor_tau, 1e-3))
        self.motor_thrust += (thrust_cmd - self.motor_thrust) * alpha

        self.data.qfrc_applied[:] = 0.0
        rotor_world = (self.data.xpos[self.platform_body][:, None] +
                       rotation @ self.rotor_positions.T)
        for i in range(4):
            thrust = self.motor_thrust[i]
            force_world = rotation @ np.array([0.0, 0.0, thrust])
            torque_world = rotation @ np.array(
                [0.0, 0.0, ROTOR_SPIN[i] * self.rotor_drag_m * thrust])
            mujoco.mj_applyFT(
                self.model, self.data, force_world, torque_world,
                rotor_world[:, i], self.platform_body,
                self.data.qfrc_applied)

    def _update_control(self, now):
        """Apply the latest /visioncontrol command to the plant."""
        self.data.qfrc_applied[:] = 0.0
        allow_control = True

        px, py, pz = (float(self.platform_pos[0]),
                      float(self.platform_pos[1]),
                      float(self.platform_pos[2]))
        if (self.reset_out_of_bounds and
                (abs(px) > 30.0 or abs(py) > 20.0 or
                 pz < -2.0 or pz > 5.0)):
            self.get_logger().warn(
                "platform out of bounds at (%.1f, %.1f, %.1f); respawning"
                % (px, py, pz))
            self._reset_simulation(now)
            return

        if self.impacted:
            # Motors stay cut; the drone falls under gravity and contact.
            allow_control = False
            if (self.reset_after_impact_s > 0.0 and
                    now - self.impact_time >= self.reset_after_impact_s):
                self._reset_simulation(now)
                return

        v_cmd, contact = self._external_command(now)
        self.last_v_cmd = v_cmd.copy()
        if allow_control:
            # The sustained press only needs ~10 deg of tilt; a tighter cap
            # while the target is in contact keeps the airframe and camera
            # steady.
            max_tilt = (self.contact_max_tilt_deg if contact
                        else self.max_tilt_deg)
            self._command_velocity(v_cmd, max_tilt)
        else:
            self.motor_thrust[:] = 0.0

    def _external_command(self, now):
        """World-frame velocity from the latest body-FRD command.

        Returns (v_cmd, in_contact). No command yet, a stale command or a
        valid=false message all mean "hold": a zero velocity keeps the
        aircraft hovering instead of flying on a command the guidance node
        no longer stands behind.
        """
        contact, force = self._target_contact()
        self.contact_force = force if contact else 0.0
        if self.last_command is None:
            self.wz_cmd = 0.0
            return np.zeros(3), contact
        if now - self.last_command_time > self.command_timeout_s:
            if not self.command_stale_logged:
                self.command_stale_logged = True
                self.get_logger().warn(
                    "no /visioncontrol for %.2f s; holding position"
                    % self.command_timeout_s)
            self.wz_cmd = 0.0
            return np.zeros(3), contact
        if not self.last_command_valid:
            self.wz_cmd = 0.0
            return np.zeros(3), contact
        # World command frozen at reception (see _on_vision_control): the
        # body-FRD contract is inverted once with the attitude at receipt and
        # held until the next message, matching how the in-process controller
        # consumed a world-frame command.
        return self.last_command_world.copy(), contact

    def _publish_platform_state(self, now):
        """Plant state for fc01_mission: pose, velocity, rates, contact."""
        if now - self.last_state_time < 1.0 / self.state_publish_hz:
            return
        self.last_state_time = now
        stamp = _stamp(self)

        pose = PoseStamped()
        pose.header.stamp = stamp
        pose.header.frame_id = "world"
        pose.pose.position.x = float(self.data.qpos[0])
        pose.pose.position.y = float(self.data.qpos[1])
        pose.pose.position.z = float(self.data.qpos[2])
        pose.pose.orientation.w = float(self.data.qpos[3])
        pose.pose.orientation.x = float(self.data.qpos[4])
        pose.pose.orientation.y = float(self.data.qpos[5])
        pose.pose.orientation.z = float(self.data.qpos[6])
        self.platform_pose_pub.publish(pose)

        velocity = Vector3Stamped()
        velocity.header.stamp = stamp
        velocity.header.frame_id = "world"
        velocity.vector.x = float(self.data.qvel[0])
        velocity.vector.y = float(self.data.qvel[1])
        velocity.vector.z = float(self.data.qvel[2])
        self.platform_velocity_pub.publish(velocity)

        # Free-joint angular velocity is in the body FLU frame.
        omega = Vector3Stamped()
        omega.header.stamp = stamp
        omega.header.frame_id = "body_flu"
        omega.vector.x = float(self.data.qvel[3])
        omega.vector.y = float(self.data.qvel[4])
        omega.vector.z = float(self.data.qvel[5])
        self.platform_omega_pub.publish(omega)

        contact, force = self._target_contact()
        self.contact_force = force if contact else 0.0
        self.contact_force_pub.publish(Float32(data=self.contact_force))
        self.impact_pub.publish(Bool(data=bool(self.impacted)))

    # ---- Publishing ------------------------------------------------------
    def _vibrate_camera(self):
        """Add a little rotor vibration to the rendered FPV camera.

        The airframe itself stays rigid - this only perturbs the scene camera
        used for the published image, so the physics, the controller and the
        detected geometry are untouched. A perfectly stabilised feed is the
        clearest "this is a render" tell; a real FPV camera is hard-mounted
        to a vibrating frame.
        """
        amp = math.radians(max(0.0, self.camera_shake_deg))
        if amp <= 0.0:
            return
        t = self.data.time
        two_pi = 2.0 * math.pi
        pitch = amp * (0.55 * math.sin(two_pi * 11.3 * t + 0.7) +
                       0.30 * math.sin(two_pi * 23.7 * t + 2.1) +
                       0.15 * math.sin(two_pi * 37.1 * t + 4.0))
        yaw = amp * (0.50 * math.sin(two_pi * 9.1 * t + 1.9) +
                     0.35 * math.sin(two_pi * 19.3 * t + 3.2) +
                     0.15 * math.sin(two_pi * 41.7 * t + 0.4))
        roll = amp * (0.55 * math.sin(two_pi * 13.7 * t + 2.8) +
                      0.30 * math.sin(two_pi * 27.1 * t + 1.1) +
                      0.15 * math.sin(two_pi * 43.9 * t + 3.7))
        cam = self.renderer.scene.camera[0]
        fwd0 = np.array(cam.forward, dtype=float)
        up0 = np.array(cam.up, dtype=float)
        right = np.cross(fwd0, up0)
        norm = float(np.linalg.norm(right))
        if norm < 1e-9:
            return
        right /= norm
        fwd = fwd0 + pitch * up0 + yaw * right
        up = up0 - pitch * fwd0 + roll * right
        fwd /= max(float(np.linalg.norm(fwd)), 1e-9)
        up -= float(np.dot(up, fwd)) * fwd
        up /= max(float(np.linalg.norm(up)), 1e-9)
        cam.forward[:] = fwd
        cam.up[:] = up

    def _publish_frame(self, now):
        self.renderer.update_scene(self.data, camera="fpv")
        self._vibrate_camera()
        rgb = self.renderer.render()
        if self.camera_noise_lsb > 0.0:
            noise = self._image_rng.normal(
                0.0, self.camera_noise_lsb, rgb.shape)
            rgb = np.clip(
                rgb.astype(np.float32) + noise, 0.0, 255.0).astype(np.uint8)
        rgb = np.ascontiguousarray(rgb)

        stamp = _stamp(self)
        frame_id = "sim_camera_optical"

        image = Image()
        image.header.stamp = stamp
        image.header.frame_id = frame_id
        image.height = self.render_height
        image.width = self.render_width
        image.encoding = "rgb8"
        image.is_bigendian = 0
        image.step = self.render_width * 3
        image.data = rgb.tobytes()
        self.image_pub.publish(image)

        info = CameraInfo()
        info.header.stamp = stamp
        info.header.frame_id = frame_id
        info.height = self.render_height
        info.width = self.render_width
        info.distortion_model = "plumb_bob"
        info.d = [0.0, 0.0, 0.0, 0.0, 0.0]
        info.k = [self.fx, 0.0, self.cx,
                  0.0, self.fy, self.cy,
                  0.0, 0.0, 1.0]
        info.r = [1.0, 0.0, 0.0,
                  0.0, 1.0, 0.0,
                  0.0, 0.0, 1.0]
        info.p = [self.fx, 0.0, self.cx, 0.0,
                  0.0, self.fy, self.cy, 0.0,
                  0.0, 0.0, 1.0, 0.0]
        self.info_pub.publish(info)

        if self.publish_ground_truth:
            target_pose = PoseStamped()
            target_pose.header.stamp = stamp
            target_pose.header.frame_id = "world"
            target_pose.pose.position.x = float(self.target_pos[0])
            target_pose.pose.position.y = float(self.target_pos[1])
            target_pose.pose.position.z = float(self.target_pos[2])
            target_pose.pose.orientation.w = 1.0
            self.target_pose_pub.publish(target_pose)

            gt_frd = self._ground_truth_relative_frd()
            gt_msg = PointStamped()
            gt_msg.header.stamp = stamp
            gt_msg.header.frame_id = "body_frd"
            gt_msg.point.x = float(gt_frd[0])
            gt_msg.point.y = float(gt_frd[1])
            gt_msg.point.z = float(gt_frd[2])
            self.gt_relative_pub.publish(gt_msg)

        self.frames += 1
        if now - self.last_log_time >= self.log_period_s:
            self.last_log_time = now
            rotation = self._body_rotation()
            roll = math.degrees(math.atan2(rotation[2, 1], rotation[2, 2]))
            pitch = math.degrees(math.asin(
                float(np.clip(-rotation[2, 0], -1.0, 1.0))))
            yaw = math.degrees(math.atan2(rotation[1, 0], rotation[0, 0]))
            wall_elapsed = max(now - self.start_time, 1e-6)
            sim_ratio = self.data.time / wall_elapsed
            if self.last_command is None:
                control_text = "control=none"
            else:
                control_text = (
                    "control=age %.3fs valid=%s body=(%.2f, %.2f, %.2f) "
                    "cmd=(%.2f, %.2f, %.2f) force=%.1fN"
                    % (now - self.last_command_time,
                       "yes" if self.last_command_valid else "no",
                       self.last_command[0], self.last_command[1],
                       self.last_command[2],
                       self.last_v_cmd[0], self.last_v_cmd[1],
                       self.last_v_cmd[2], self.contact_force))
            self.get_logger().info(
                "frames=%d state=%s platform=(%.2f, %.2f, %.2f) rpy=(%.0f, "
                "%.0f, %.0f)deg vel=(%.2f, %.2f, %.2f) thrust=%.1fN "
                "target=(%.2f, %.2f, %.2f) sim/wall=%.2f %s"
                % (self.frames,
                   "impacted" if self.impacted else "flying",
                   self.platform_pos[0], self.platform_pos[1],
                   self.platform_pos[2], roll, pitch, yaw,
                   self.platform_vel[0], self.platform_vel[1],
                   self.platform_vel[2], float(np.sum(self.motor_thrust)),
                   self.target_pos[0], self.target_pos[1],
                   self.target_pos[2], sim_ratio, control_text))

    # ---- Main loop -------------------------------------------------------
    def run(self):
        viewer = None
        if not self.headless:
            try:
                from mujoco import viewer as mujoco_viewer
                viewer = mujoco_viewer.launch_passive(
                    self.model, self.data, key_callback=self._on_viewer_key)
                self.get_logger().info("MuJoCo viewer opened")
            except Exception as error:  # no display / GL failure
                self.get_logger().warn(
                    "viewer unavailable (%s); running headless"
                    % str(error))

        if viewer is not None and self.viewer_camera == "fpv":
            if self.fpv_camera_id < 0:
                self.get_logger().warn(
                    "fpv camera not found; viewer keeps the free camera")
            else:
                viewer.cam.type = mujoco.mjtCamera.mjCAMERA_FIXED
                viewer.cam.fixedcamid = self.fpv_camera_id
                self.get_logger().info(
                    "viewer is showing the FPV camera feed "
                    "(V toggles view, Esc=free camera)")
        elif viewer is not None:
            self._aim_viewer_at_platform(viewer)
            self.get_logger().info(
                "viewer is showing the third-person camera "
                "(V toggles view, drag to orbit)")

        loop_period = 1.0 / max(self.physics_hz, 1.0)
        render_period = 1.0 / max(self.render_fps, 1.0)
        next_view = time.monotonic()
        next_render = time.monotonic()

        try:
            while rclpy.ok():
                frame_start = time.monotonic()
                rclpy.spin_once(self, timeout_sec=0.0)

                now = time.monotonic()
                if viewer is not None and not viewer.is_running():
                    break

                if self.pending_camera_toggle and viewer is not None:
                    self.pending_camera_toggle = False
                    self._toggle_viewer_camera(viewer)

                if self.pending_reset:
                    self.pending_reset = False
                    self._reset_simulation(now)
                elif viewer is not None and self._viewer_reset_requested():
                    drift = float(np.max(np.abs(
                        self.data.mocap_pos[self.target_mocap] -
                        self.target_pos)))
                    self.get_logger().info(
                        "viewer reset detected: data.time=%.4f last=%.4f "
                        "mocap_drift=%.6f"
                        % (self.data.time, self.last_data_time, drift))
                    self._reset_simulation(now)

                # Advance physics on the fixed 200 Hz clock, decoupled from
                # rendering. Rendering a camera frame takes several physics
                # steps' worth of wall time; without catch-up the simulated
                # world runs in slow motion (the target, driven by simulated
                # time, then moves correctly relative to the slow drone, but
                # every impact looks feeble and the viewer stutters). After a
                # slow frame we run several cheap physics steps at once.
                wall_dt = min(max(now - self.last_step_time, 0.0), 0.1)
                self.last_step_time = now
                timestep = self.model.opt.timestep
                self.physics_accumulator = min(
                    self.physics_accumulator + wall_dt,
                    MAX_CATCHUP_STEPS * timestep)
                steps = 0
                while (self.physics_accumulator >= timestep and
                       steps < MAX_CATCHUP_STEPS):
                    self.platform_pos = self.data.qpos[0:3].copy()
                    self.platform_vel = self.data.qvel[0:3].copy()
                    # Target motion follows simulated time, so its speed
                    # relative to the drone is independent of render rate.
                    self.target_pos = self._target_position(self.data.time)
                    self._update_control(now)
                    if self.pending_reset:
                        # A reset reinitialised the data; drop the backlog.
                        self.physics_accumulator = 0.0
                        break
                    self._write_mocap()
                    # Velocity just before the step: the contact impulse
                    # inside mj_step would otherwise hide the true
                    # approach speed.
                    approach_speed = float(np.linalg.norm(self.platform_vel))
                    expected_time = self.last_data_time + timestep
                    mujoco.mj_step(self.model, self.data)
                    # A viewer reset rewinds data.time (and mocap positions)
                    # at an arbitrary moment; catch it here too.
                    if abs(self.data.time - expected_time) > 1e-9:
                        self.pending_reset = True
                        self.physics_accumulator = 0.0
                        break
                    self.last_data_time = self.data.time
                    self.platform_pos = self.data.qpos[0:3].copy()
                    self.platform_vel = self.data.qvel[0:3].copy()
                    self.max_tilt_seen_deg = max(
                        self.max_tilt_seen_deg, self._tilt_deg())
                    if (not self.impacted and
                            self.engage_mode != "push"):
                        # Push mode wants the contact to persist, so it never
                        # ends the episode from here.
                        contact, force = self._target_contact()
                        if contact:
                            self._finish_impact(now, force, approach_speed)
                    self.physics_accumulator -= timestep
                    steps += 1

                # Plant state for fc01_mission (pose, velocity, body rates,
                # contact force), throttled to state_publish_hz.
                self._publish_platform_state(now)

                if viewer is not None and now >= next_view:
                    viewer.sync()
                    next_view = now + 1.0 / 60.0

                if now >= next_render:
                    self._publish_frame(now)
                    next_render = now + render_period

                sleep_time = loop_period - (time.monotonic() - frame_start)
                if sleep_time > 0.0:
                    time.sleep(sleep_time)
        except KeyboardInterrupt:
            pass
        finally:
            if viewer is not None:
                viewer.close()
            self.get_logger().info("simulation stopped")


def main(args=None):
    rclpy.init(args=args)
    node = VisionSimNode()
    try:
        node.run()
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
