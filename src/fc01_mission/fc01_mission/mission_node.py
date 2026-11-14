"""Vision guidance / mission node.

This is the flight logic that used to live inside ``fc01_vision_sim``: the
takeoff -> seek -> strike -> push -> retreat -> hold state machine, plus the
``track`` and ``impact`` modes. It is deliberately independent of MuJoCo and
of the simulator package:

  inputs
    /fc01/vision/target_relative      target relative to the camera, body FRD
    /fc01/vision/state                optional VisionState (use_vision_state)
    /sim/platform_pose                platform position + attitude (world)
    /sim/platform_velocity            platform linear velocity (world)
    /sim/platform_angular_velocity    body rates (body FLU)
    /sim/target_contact_force         |contact force| with the target, N
    /sim/impact                       episode ended by contact (impact mode)
    /sim/reset_event                  simulator respawned the aircraft

  output
    /visioncontrol                    jikl_fc01_system/VelocityCommand,
                                      body FRD m/s, at vision_control_hz

The simulator subscribes to the same ``/visioncontrol`` a real flight
controller would, so the guidance can be moved onto the aircraft unchanged.

The node never reads ground truth about the target: the light's map
coordinates are a configuration prior (``target_x/y/z``), used for the blind
cruise before vision locks on and for the static strike, exactly as the old
in-sim controller did.
"""

import math
import time

import numpy as np
import rclpy
from geometry_msgs.msg import PointStamped, PoseStamped, Vector3Stamped
from rclpy.node import Node
from rclpy.qos import (DurabilityPolicy, HistoryPolicy, QoSProfile,
                       ReliabilityPolicy)
from std_msgs.msg import Bool, Empty, Float32, String

try:  # The mission node publishes the real flight-controller contract.
    from jikl_fc01_system.msg import NavigationCommand as NavigationCommandMsg
    from jikl_fc01_system.msg import VelocityCommand as VelocityCommandMsg
except Exception:  # pragma: no cover - depends on the workspace
    NavigationCommandMsg = None
    VelocityCommandMsg = None

try:  # Optional: consume the vision state adapter directly.
    from jikl_fc01_system.msg import VisionState as VisionStateMsg
except Exception:  # pragma: no cover - depends on the workspace
    VisionStateMsg = None


# The vision image node publishes best-effort sensor data.
SENSOR_QOS = QoSProfile(
    depth=5,
    history=HistoryPolicy.KEEP_LAST,
    reliability=ReliabilityPolicy.BEST_EFFORT,
    durability=DurabilityPolicy.VOLATILE,
)


class MissionNode(Node):
    def __init__(self):
        super().__init__("fc01_mission")

        # ---- Parameters ---------------------------------------------------
        p = self.declare_parameter
        self.control_hz = max(10.0, float(p("control_hz", 100.0).value))
        self.control_enabled = bool(p("control_enabled", True).value)
        self.engage_mode = str(p("engage_mode", "push").value).strip().lower()
        if self.engage_mode not in ("track", "impact", "push"):
            raise ValueError(
                "engage_mode must be 'track', 'impact' or 'push', got '%s'"
                % self.engage_mode)

        # The RMUC green light on the map. This is a prior, not a
        # measurement: vision is the only feedback used in the loop.
        self.target_x = float(p("target_x", 0.315).value)
        self.target_y = float(p("target_y", -4.958).value)
        self.target_base_z = float(p("target_base_z", 1.373).value)
        # Yaw the airframe should hold while striking/pushing the light face
        # (the light faces -x, so the nose points +x at yaw 0).
        self.target_face_yaw = math.radians(
            float(p("target_face_yaw_deg", 0.0).value))
        self.target_motion = str(
            p("target_motion", "static").value).strip().lower()
        if self.target_motion not in ("random", "sinusoid", "static"):
            raise ValueError(
                "target_motion must be 'random', 'sinusoid' or 'static', "
                "got '%s'" % self.target_motion)
        self.target_pos = np.array(
            [self.target_x, self.target_y, self.target_base_z])

        # Camera mount offset in the body FLU frame (x forward, y left,
        # z up). Vision reports the target relative to the camera optical
        # centre, so the world estimate needs this offset. Must match the
        # simulator scene / the real airframe.
        self.camera_pos = np.array([
            float(p("camera_pos_x", 0.08).value),
            float(p("camera_pos_y", 0.0).value),
            float(p("camera_pos_z", 0.015).value),
        ])

        # ---- Flight profile ----------------------------------------------
        # Takeoff: vertical climb, a short hover, then the chase.
        self.takeoff_altitude_m = float(
            p("takeoff_altitude_m", 1.2).value)
        self.takeoff_climb_mps = max(
            0.1, float(p("takeoff_climb_mps", 0.8).value))
        self.takeoff_hover_s = max(
            0.0, float(p("takeoff_hover_s", 0.8).value))
        self.seek_ramp_s = max(
            0.05, float(p("seek_ramp_s", 1.2).value))
        self.cruise_descent_mps = max(
            0.1, float(p("cruise_descent_mps", 0.9).value))
        self.standoff_m = float(p("standoff_m", 2.0).value)
        self.controller_gain = float(p("controller_gain", 2.0).value)
        self.max_speed = float(p("max_speed", 2.5).value)
        self.search_speed = max(0.1, float(p("search_speed", 0.9).value))
        self.track_max_speed = float(p("track_max_speed", 2.0).value)

        # Sustained push.
        self.push_speed = float(p("push_speed", 0.35).value)
        self.push_engage_m = float(p("push_engage_m", 0.55).value)
        self.push_release_m = float(p("push_release_m", 0.95).value)
        self.push_max_force_n = float(p("push_max_force_n", 90.0).value)
        self.push_altitude_m = float(p("push_altitude_m", 0.0).value)
        self.push_altitude_offset_m = float(
            p("push_altitude_offset_m", 0.05).value)
        self.push_hold_s = float(p("push_hold_s", 3.0).value)
        self.retreat_speed = max(0.1, float(p("retreat_speed", 0.8).value))
        self.retreat_distance_m = max(
            0.1, float(p("retreat_distance_m", 1.0).value))
        self.retreat_ramp_s = max(
            0.05, float(p("retreat_ramp_s", 0.5).value))

        # Terminal strike before the push.
        self.strike_speed = float(p("strike_speed", 2.0).value)
        self.strike_trigger_m = float(p("strike_trigger_m", 2.6).value)
        self.strike_engage_m = float(p("strike_engage_m", 0.10).value)
        self.strike_timeout_s = float(p("strike_timeout_s", 3.0).value)
        self.strike_settle_s = float(p("strike_settle_s", 0.25).value)
        self.strike_settle_brake_mps = float(
            p("strike_settle_brake_mps", 0.4).value)

        # Impact mode: single terminal dive, motors cut by the plant on
        # contact.
        self.impact_speed = float(p("impact_speed", 3.0).value)
        self.terminal_trigger_m = float(
            p("terminal_trigger_m", 1.0).value)
        self.terminal_timeout_s = float(p("terminal_timeout_s", 1.0).value)

        self.min_altitude_m = float(p("min_altitude_m", 0.16).value)

        # ---- Topics -------------------------------------------------------
        self.relative_topic = p(
            "relative_topic", "/fc01/vision/target_relative").value
        self.vision_state_topic = p(
            "vision_state_topic", "/fc01/vision/state").value
        self.use_vision_state = bool(p("use_vision_state", False).value)
        self.platform_pose_topic = p(
            "platform_pose_topic", "/sim/platform_pose").value
        self.platform_velocity_topic = p(
            "platform_velocity_topic", "/sim/platform_velocity").value
        self.platform_omega_topic = p(
            "platform_angular_velocity_topic",
            "/sim/platform_angular_velocity").value
        self.contact_force_topic = p(
            "contact_force_topic", "/sim/target_contact_force").value
        self.impact_topic = p("impact_topic", "/sim/impact").value
        self.reset_event_topic = p(
            "reset_event_topic", "/sim/reset_event").value
        self.state_topic = p("state_topic", "/mission/state").value
        self.state_publish_hz = max(
            0.0, float(p("state_publish_hz", 10.0).value))

        self.publish_vision_control = bool(
            p("publish_vision_control", True).value)
        self.vision_control_topic = str(
            p("vision_control_topic", "/visioncontrol").value)
        # Heading is commanded as a body yaw RATE in VelocityCommand.wz, not
        # as an absolute angle: the mission closes the heading loop using the
        # platform attitude it already receives, and the flight controller
        # only has to track the rate.
        self.yaw_rate_gain = max(
            0.0, float(p("yaw_rate_gain", 3.0).value))
        # Per-axis body-FRD velocity limits applied just before publishing.
        # 0 disables a limit.
        self.max_vx_mps = max(0.0, float(p("max_vx_mps", 0.0).value))
        self.max_vy_mps = max(0.0, float(p("max_vy_mps", 0.0).value))
        self.max_vz_mps = max(0.0, float(p("max_vz_mps", 0.0).value))
        self.vision_control_hz = max(
            1.0, float(p("vision_control_hz", 50.0).value))
        self.vision_control_source_id = str(
            p("vision_control_source_id", "fc01_mission").value)

        # Waypoint command for the flight controller, published on its own
        # topic while the target is not yet detected. The FC follows this
        # when it is valid/fresh and falls back to /visioncontrol otherwise.
        self.publish_navigation_command = bool(
            p("publish_navigation_command", True).value)
        self.navigation_command_topic = str(
            p("navigation_command_topic", "/navigation_command").value)
        self.navigation_command_hz = max(
            1.0, float(p("navigation_command_hz", 10.0).value))

        # Freshness limits. Vision older than this is ignored; a command is
        # held for command_timeout_s by the plant if this node stalls.
        self.command_timeout_s = float(p("command_timeout_s", 0.5).value)
        self.pose_timeout_s = float(p("pose_timeout_s", 0.5).value)
        self.contact_timeout_s = float(p("contact_timeout_s", 0.2).value)
        self.control_debug_hz = float(p("control_debug_hz", 0.0).value)

        # ---- ROS I/O ------------------------------------------------------
        self.vision_control_pub = None
        if self.publish_vision_control:
            if VelocityCommandMsg is not None:
                self.vision_control_pub = self.create_publisher(
                    VelocityCommandMsg, self.vision_control_topic, 10)
            else:
                self.get_logger().error(
                    "publish_vision_control=true but VelocityCommand is not "
                    "built; rebuild jikl_fc01_system")
        self.navigation_command_pub = None
        if self.publish_navigation_command:
            if NavigationCommandMsg is not None:
                self.navigation_command_pub = self.create_publisher(
                    NavigationCommandMsg, self.navigation_command_topic, 10)
            else:
                self.get_logger().error(
                    "publish_navigation_command=true but NavigationCommand "
                    "is not built; rebuild jikl_fc01_system")
        self.relative_sub = self.create_subscription(
            PointStamped, self.relative_topic, self._on_relative, SENSOR_QOS)
        self.state_sub = None
        self.vision_state_time = 0.0
        if self.use_vision_state:
            if VisionStateMsg is not None:
                self.state_sub = self.create_subscription(
                    VisionStateMsg, self.vision_state_topic, self._on_state,
                    SENSOR_QOS)
                self.get_logger().info(
                    "consuming %s (takes precedence over %s)"
                    % (self.vision_state_topic, self.relative_topic))
            else:
                self.get_logger().warn(
                    "use_vision_state=true but jikl_fc01_system is not "
                    "available; using %s" % self.relative_topic)
        else:
            self.get_logger().info(
                "consuming %s (use_vision_state=false)"
                % self.relative_topic)

        self.pose_sub = self.create_subscription(
            PoseStamped, self.platform_pose_topic, self._on_pose, 10)
        self.velocity_sub = self.create_subscription(
            Vector3Stamped, self.platform_velocity_topic,
            self._on_velocity, 10)
        self.omega_sub = self.create_subscription(
            Vector3Stamped, self.platform_omega_topic, self._on_omega, 10)
        self.contact_sub = self.create_subscription(
            Float32, self.contact_force_topic, self._on_contact, 10)
        self.impact_sub = self.create_subscription(
            Bool, self.impact_topic, self._on_impact, 10)
        self.reset_sub = self.create_subscription(
            Empty, self.reset_event_topic, self._on_reset_event, 10)
        self.state_pub = self.create_publisher(String, self.state_topic, 10)
        self.last_state_time = 0.0

        # ---- State --------------------------------------------------------
        self.platform_pos = None
        self.platform_vel = np.zeros(3)
        self.platform_omega = np.zeros(3)   # body FLU
        self.platform_rot = np.eye(3)
        self.platform_pose_time = 0.0
        self.platform_start = None
        self.yaw_cmd = None
        # Yaw-rate feedforward published in VelocityCommand.wz. Derived from
        # the rate of change of yaw_cmd; body FRD (z down), so the world yaw
        # rate is negated when it goes into the message.
        self.last_published_yaw = None
        self.last_published_yaw_time = 0.0
        self.yaw_rate_cmd = 0.0
        self.yaw_rate_ff = 0.0

        # Vision-only target world position and velocity (never ground
        # truth). Velocity is estimated from successive estimates.
        self.vision_rel = None
        self.vision_time = 0.0
        self.vision_source = "none"
        self.est_pos = None
        self.est_time = 0.0
        self.target_vel_est = np.zeros(3)
        self.last_los_world = None

        self.contact_force = 0.0
        self.contact_time = 0.0

        self.flight_state = "takeoff"
        self.takeoff_complete_time = None
        self.seek_start = -1.0e9
        self.push_aim = None
        self.pushing = False
        self.push_time = 0.0
        self.push_contact_force = 0.0
        self.retreat_start = 0.0
        self.retreat_dir = np.array([-1.0, 0.0, 0.0])
        self.strike_start = 0.0
        self.terminal_start = None
        self.terminal_cmd = np.zeros(3)
        self.impacted = False
        self.impact_time = 0.0
        self.reset_time = 0.0

        self.vision_control_seq = 0
        self.navigation_seq = 0
        self.reset_counter = 0
        self.last_vision_control_time = 0.0
        self.last_navigation_time = 0.0
        self.last_control_debug = 0.0
        self.last_v_cmd = np.zeros(3)
        self.last_tick_time = time.monotonic()
        self.start_time = self.last_tick_time

        self.get_logger().info(
            "mission: mode=%s, vision=%s, plant pose=%s, out=%s at %.0f Hz"
            % (self.engage_mode, self.relative_topic,
               self.platform_pose_topic, self.vision_control_topic,
               self.vision_control_hz))
        self.control_timer = self.create_timer(
            1.0 / self.control_hz, self._tick)

    # ---- Inputs ----------------------------------------------------------
    def _message_age(self, stamp):
        """Seconds since an image was captured (clamped to a sane window)."""
        now_s = self.get_clock().now().nanoseconds * 1e-9
        age = now_s - (float(stamp.sec) + float(stamp.nanosec) * 1e-9)
        return float(min(max(age, 0.0), 0.15))

    def _on_pose(self, msg):
        self.platform_pos = np.array(
            [msg.pose.position.x, msg.pose.position.y,
             msg.pose.position.z], dtype=float)
        q = msg.pose.orientation
        self.platform_rot = self._quat_rotation(q.w, q.x, q.y, q.z)
        self.platform_pose_time = time.monotonic()
        if self.platform_start is None:
            # First word from the plant after start/reset: this is where the
            # takeoff begins (the "clear the H pad" blend needs it).
            self.platform_start = self.platform_pos.copy()
        if self.yaw_cmd is None:
            self.yaw_cmd = math.atan2(
                self.platform_rot[1, 0], self.platform_rot[0, 0])

    def _on_velocity(self, msg):
        self.platform_vel = np.array(
            [msg.vector.x, msg.vector.y, msg.vector.z], dtype=float)

    def _on_omega(self, msg):
        self.platform_omega = np.array(
            [msg.vector.x, msg.vector.y, msg.vector.z], dtype=float)

    def _on_contact(self, msg):
        self.contact_force = max(0.0, float(msg.data))
        self.contact_time = time.monotonic()

    def _on_impact(self, msg):
        if bool(msg.data) and not self.impacted:
            self.impacted = True
            self.impact_time = time.monotonic()
            self.get_logger().info("impact reported by the plant: holding")

    def _on_reset_event(self, _msg):
        self._reset_mission()

    def _on_relative(self, msg):
        if (self.state_sub is not None and
                time.monotonic() - self.vision_state_time <=
                self.command_timeout_s):
            return  # VisionState is the configured source and is fresh.
        p = np.array([msg.point.x, msg.point.y, msg.point.z], dtype=float)
        if np.all(np.isfinite(p)):
            self._ingest(p, time.monotonic(), "relative",
                         self._message_age(msg.header.stamp))

    def _on_state(self, msg):
        # Respect the field mask: POSITION set means position is usable.
        if not (msg.valid_fields & msg.POSITION):
            return
        p = np.array(msg.position[0:3], dtype=float)
        if np.all(np.isfinite(p)):
            now = time.monotonic()
            self._ingest(p, now, "vision_state",
                         self._message_age(msg.stamp))
            self.vision_state_time = now

    # ---- Helpers ---------------------------------------------------------
    @staticmethod
    def _quat_rotation(w, x, y, z):
        """Quaternion (w, x, y, z) to a body-FLU -> world rotation."""
        norm = math.sqrt(w * w + x * x + y * y + z * z)
        if norm < 1e-12:
            return np.eye(3)
        w, x, y, z = w / norm, x / norm, y / norm, z / norm
        return np.array([
            [1.0 - 2.0 * (y * y + z * z), 2.0 * (x * y - z * w),
             2.0 * (x * z + y * w)],
            [2.0 * (x * y + z * w), 1.0 - 2.0 * (x * x + z * z),
             2.0 * (y * z - x * w)],
            [2.0 * (x * z - y * w), 2.0 * (y * z + x * w),
             1.0 - 2.0 * (x * x + y * y)],
        ])

    def _camera_world_position(self):
        if self.platform_pos is None:
            return None
        return self.platform_pos + self.platform_rot @ self.camera_pos

    def _ingest(self, p_frd, now, source, age=0.0):
        if self.platform_pos is None:
            return
        # The measurement is expressed in the body frame at image-capture
        # time, but we hold the body attitude at ingestion time. During a
        # fast pitch-over those differ by tens of degrees within the ~20-50
        # ms transport delay, so rotate the vector back along the body's
        # rotation over the message age and move the origin back by the
        # distance flown in that time (first-order small-angle corrections).
        p = np.array(p_frd, dtype=float)
        if age > 1e-4:
            # Body angular velocity in FRD, to match the FRD measurement.
            omega_frd = np.array([self.platform_omega[0],
                                  -self.platform_omega[1],
                                  -self.platform_omega[2]])
            p = p - np.cross(omega_frd * age, p)
        rel_world = self.platform_rot @ np.array([p[0], -p[1], -p[2]])
        origin = self._camera_world_position() - self.platform_vel * age
        estimate = origin + rel_world
        # Last known world-frame line of sight, used to point the nose (and
        # so the camera) back at the target if detection is lost.
        self.last_los_world = rel_world / max(
            float(np.linalg.norm(rel_world)), 1e-6)
        dt_est = now - self.est_time
        if self.est_pos is not None and 1e-3 < dt_est < 0.5:
            raw_velocity = (estimate - self.est_pos) / dt_est
            blend = min(1.0, dt_est / 0.3)
            self.target_vel_est += (raw_velocity - self.target_vel_est) * blend
            # The light itself never moves; anything larger is residual
            # estimate noise and would be fed back as a violent command.
            speed = float(np.linalg.norm(self.target_vel_est))
            if speed > 2.0:
                self.target_vel_est *= 2.0 / speed
        self.est_pos = estimate
        self.est_time = now

        self.vision_rel = p
        self.vision_time = now
        self.vision_source = source

    def _blend_angle(self, current, target, alpha):
        diff = math.atan2(math.sin(target - current),
                          math.cos(target - current))
        return current + diff * alpha

    def _reset_mission(self):
        self.flight_state = "takeoff"
        self.takeoff_complete_time = None
        self.seek_start = -1.0e9
        self.terminal_start = None
        self.terminal_cmd = np.zeros(3)
        self.impacted = False
        self.pushing = False
        self.push_time = 0.0
        self.push_contact_force = 0.0
        self.strike_start = 0.0
        self.retreat_start = 0.0
        self.retreat_dir = np.array([-1.0, 0.0, 0.0])
        self.last_published_yaw = None
        self.last_published_yaw_time = 0.0
        self.yaw_rate_cmd = 0.0
        self.yaw_rate_ff = 0.0
        self.push_aim = None
        self.vision_rel = None
        self.est_pos = None
        self.est_time = 0.0
        self.target_vel_est[:] = 0.0
        self.last_los_world = None
        self.last_v_cmd[:] = 0.0
        # Re-capture the start pose from the next plant message: the sim
        # respawns on the H pad.
        self.platform_start = None
        self.yaw_cmd = None
        self.reset_counter += 1
        self.last_navigation_time = 0.0
        self.reset_time = time.monotonic()
        self.get_logger().info("mission reset: takeoff from the plant pose")

    # ---- Guidance --------------------------------------------------------
    def _tick(self):
        now = time.monotonic()
        dt = float(min(max(now - self.last_tick_time, 0.0), 0.05))
        self.last_tick_time = now

        pose_fresh = (self.platform_pos is not None and
                      now - self.platform_pose_time <= self.pose_timeout_s)
        if not pose_fresh:
            # No recent plant state: stay silent. The plant holds/hovers
            # after its command timeout.
            return

        v_cmd, valid = self._update_mission(now, dt)
        self.last_v_cmd = v_cmd.copy()
        self._publish_command(v_cmd, now, valid=valid)
        self._publish_navigation(now)
        self._publish_state(now)
        self._debug_log(now)

    def _update_mission(self, now, dt):
        """Run the state machine; return a world-frame velocity command."""
        v_cmd = np.zeros(3)
        valid = True
        platform_pos = self.platform_pos
        platform_vel = self.platform_vel

        # Sustained impact is a timed phase: after pressing for push_hold_s
        # the aircraft backs straight out and holds a hover. Check before the
        # state chain so the push branch does not run one more tick of
        # forward thrust into the contact.
        if (self.engage_mode == "push" and self.control_enabled and
                self.flight_state == "push" and self.push_hold_s > 0.0 and
                now - self.push_time >= self.push_hold_s):
            self.flight_state = "retreat"
            self.retreat_start = now
            if self.push_aim is not None:
                away = platform_pos - self.push_aim
            else:
                away = -np.array([math.cos(self.target_face_yaw),
                                  math.sin(self.target_face_yaw), 0.0])
            if float(np.linalg.norm(away[:2])) < 1e-3:
                away = -np.array([math.cos(self.target_face_yaw),
                                  math.sin(self.target_face_yaw), 0.0])
            self.retreat_dir = away[:2] / float(
                np.linalg.norm(away[:2]))
            self.pushing = False
            self.get_logger().info(
                "push hold done: %.1f s pressed -> retreat %.2f m "
                "at %.2f m/s"
                % (self.push_hold_s, self.retreat_distance_m,
                   self.retreat_speed))

        if self.impacted:
            valid = False
        elif (self.engage_mode == "push" and self.control_enabled and
              self.flight_state == "push"):
            # Sustained impact: keep a small velocity into the fixed light.
            # The plant's velocity loop turns that setpoint into a
            # continuous contact force.
            #
            # Push toward the world point captured at hand-over instead of
            # the live estimate: within about a metre the light fills most
            # of the frame, its contour gets clipped and the monocular range
            # grows wildly.
            if self.push_aim is None and self.est_pos is not None:
                self.push_aim = self.est_pos.copy()
            if self.push_aim is not None:
                to_target = self.push_aim - platform_pos
                range_m = float(np.linalg.norm(to_target))
                if range_m > self.push_release_m:
                    self.flight_state = "seek"
                    self.pushing = False
                    self.push_aim = None
                    self.push_contact_force = 0.0
                    self.get_logger().info(
                        "push released: moved %.2f m off the aim point -> seek"
                        % range_m)
                else:
                    self.pushing = True
                    # Hold the heading captured when push engaged: re-aiming
                    # every step is unstable when the drone is ~0.1 m away
                    # (a 2 cm lateral offset becomes a 15-20 deg yaw
                    # command).
                    if range_m > 1e-3:
                        dir_xy = to_target[:2] / max(
                            float(np.linalg.norm(to_target[:2])), 1e-6)
                    else:
                        dir_xy = np.array([
                            math.cos(self.yaw_cmd), math.sin(self.yaw_cmd)])
                    speed = self.push_speed
                    settling = (self.strike_settle_s > 0.0 and
                                now - self.push_time < self.strike_settle_s)
                    contact = (now - self.contact_time <=
                               self.contact_timeout_s)
                    force = self.contact_force if contact else 0.0
                    self.push_contact_force = force
                    if contact and self.push_max_force_n > 0.0:
                        if force > self.push_max_force_n:
                            speed *= max(
                                0.15, self.push_max_force_n / force)
                    v_cmd = np.array(
                        [dir_xy[0] * speed, dir_xy[1] * speed, 0.0])
                    if settling:
                        # Right after a strike, damp the horizontal velocity
                        # instead of pressing: commanding forward thrust into
                        # the contact pumps energy into it and the drone
                        # rebounds one to two metres.
                        brake = max(0.0, self.strike_settle_brake_mps)
                        v_cmd[:2] = np.clip(
                            -2.0 * platform_vel[:2], -brake, brake)
                    altitude = self._push_altitude()
                    vz = (1.5 * (altitude - float(platform_pos[2])) -
                          0.6 * float(platform_vel[2]))
                    v_cmd[2] = float(np.clip(vz, -0.6, 0.8))
                    if (float(platform_pos[2]) < self.min_altitude_m
                            and v_cmd[2] < 0.0):
                        v_cmd[2] = 0.0
        elif (self.engage_mode == "push" and self.control_enabled and
              self.flight_state == "strike"):
            # Terminal strike: charge the light's map point at a constant
            # speed instead of letting the position loop brake with
            # distance. The strike does not depend on the detection staying
            # in frame: for a static map target its world position is exact.
            to_target = self.target_pos - platform_pos
            range_m = float(np.linalg.norm(to_target))
            # Hold the airframe square to the light's face, not along the
            # bearing to the target: at 0.1 m the bearing is dominated by
            # the last centimetres of lateral offset, and striking the flat
            # panel at an angle spins the 240 g frame.
            self.yaw_cmd = self._blend_angle(
                self.yaw_cmd, self.target_face_yaw, min(1.0, dt / 0.15))
            dir_xy = to_target[:2] / max(
                float(np.linalg.norm(to_target[:2])), 1e-6)
            v_cmd = np.array([dir_xy[0] * self.strike_speed,
                              dir_xy[1] * self.strike_speed, 0.0])
            altitude = self._push_altitude()
            v_cmd[2] = float(np.clip(
                1.5 * (altitude - float(platform_pos[2])) -
                0.6 * float(platform_vel[2]), -0.6, 0.5))
            if range_m <= self.strike_engage_m:
                # Hand over to the push loop, which presses with push_speed
                # and holds the altitude. The charge momentum is absorbed by
                # the soft, damped target contact.
                self.flight_state = "push"
                self.pushing = True
                self.push_time = now
                self.push_contact_force = 0.0
                self.push_aim = self.target_pos.copy()
                self.get_logger().info(
                    "strike contact: range=%.2f m, speed=%.2f m/s "
                    "-> hold/push at %.2f m/s"
                    % (range_m, float(np.linalg.norm(platform_vel)),
                       self.push_speed))
                v_cmd = np.zeros(3)
            elif now - self.strike_start > self.strike_timeout_s:
                # Overshot or was deflected: drop the charge and let seek
                # re-acquire. The map position is still known.
                self.flight_state = "seek"
                self.get_logger().warn(
                    "strike timeout at range=%.2f m -> seek" % range_m)
        elif (self.engage_mode == "push" and self.control_enabled and
              self.flight_state == "retreat"):
            # Back straight out along the line the drone flew in on, nose
            # still facing the light, then hold a stable hover. The speed is
            # eased in with a smoothstep and eased out over the last 25 cm.
            if self.push_aim is not None:
                offset = platform_pos - self.push_aim
            else:
                offset = np.array(
                    [self.retreat_dir[0], self.retreat_dir[1], 0.0])
            d_xy = float(np.linalg.norm(offset[:2]))
            remaining = self.retreat_distance_m - d_xy
            if remaining <= 0.02:
                self.flight_state = "hold"
                self.get_logger().info(
                    "retreat complete: holding %.2f m off the light at "
                    "(%.2f, %.2f, %.2f) m"
                    % (d_xy, platform_pos[0], platform_pos[1],
                       platform_pos[2]))
                v_cmd = np.zeros(3)
            else:
                ease = min(1.0, max(
                    0.0, (now - self.retreat_start) / self.retreat_ramp_s))
                ease = ease * ease * (3.0 - 2.0 * ease)
                brake = min(1.0, remaining / 0.25)
                speed = self.retreat_speed * ease * brake
                v_cmd = np.array([self.retreat_dir[0] * speed,
                                  self.retreat_dir[1] * speed, 0.0])
            altitude = self._push_altitude()
            v_cmd[2] = float(np.clip(
                1.5 * (altitude - float(platform_pos[2])) -
                0.6 * float(platform_vel[2]), -0.6, 0.8))
            if (float(platform_pos[2]) < self.min_altitude_m
                    and v_cmd[2] < 0.0):
                v_cmd[2] = 0.0
        elif self.terminal_start is not None:
            if now - self.terminal_start >= self.terminal_timeout_s:
                # A real contact still ends it; otherwise report a miss and
                # stop commanding.
                self.impacted = True
                self.impact_time = now
                self.terminal_start = None
                self.get_logger().warn(
                    "terminal guidance timeout without contact")
                valid = False
            else:
                # Keep refining the aim while detections are fresh.
                if (self.vision_rel is not None and
                        (now - self.vision_time) <= self.command_timeout_s):
                    self._update_terminal_command()
                v_cmd = self.terminal_cmd
        elif self.control_enabled:
            if self.flight_state == "takeoff":
                remaining = self.takeoff_altitude_m - float(
                    platform_pos[2])
                if remaining <= 0.03:
                    if self.takeoff_complete_time is None:
                        self.takeoff_complete_time = now
                        self.get_logger().info(
                            "takeoff complete: z=%.2f m, hover %.2f s "
                            "before the chase"
                            % (platform_pos[2], self.takeoff_hover_s))
                    # Hold zero velocity: stops the residual climb and lets
                    # the attitude and the camera settle before the chase.
                    v_cmd = np.zeros(3)
                    if (now - self.takeoff_complete_time >=
                            self.takeoff_hover_s):
                        self.flight_state = "seek"
                        self.seek_start = now
                        self.get_logger().info(
                            "takeoff hover done: seeking at up to %.2f m/s"
                            % self.search_speed)
                else:
                    # Climb straight up only: the nose already points at the
                    # target and the camera must stabilise before the chase.
                    v_cmd = np.array([
                        0.0, 0.0,
                        min(self.takeoff_climb_mps,
                            max(0.1, 2.5 * remaining))])
            if self.flight_state == "seek":
                v_cmd = self._seek_command(now, dt)
        else:
            v_cmd = np.zeros(3)

        if (float(platform_pos[2]) < self.min_altitude_m and
                v_cmd[2] < 0.0):
            v_cmd[2] = 0.0
        return v_cmd, valid

    def _push_altitude(self):
        return (self.push_altitude_m if self.push_altitude_m > 0.0 else
                self.target_base_z + self.push_altitude_offset_m)

    def _seek_command(self, now, dt):
        """Seek: vision chase when locked, map-point cruise otherwise."""
        platform_pos = self.platform_pos
        platform_vel = self.platform_vel
        v_cmd = np.zeros(3)
        fresh = (self.vision_rel is not None and
                 (now - self.vision_time) <= self.command_timeout_s)
        if fresh:
            to_target = self.est_pos - platform_pos
            # Keep the nose (and the fixed camera) pointed at the target,
            # otherwise it leaves the narrow FOV in a cross-track chase.
            target_yaw = math.atan2(to_target[1], to_target[0])
            self.yaw_cmd = self._blend_angle(
                self.yaw_cmd, target_yaw, min(1.0, dt / 0.2))
            error = to_target.copy()
            if self.engage_mode == "track":
                # Hold standoff_m before the target along the line of sight
                # (subtracting it from world x only works at +x targets).
                los = to_target / max(
                    float(np.linalg.norm(to_target)), 1e-6)
                error = to_target - los * self.standoff_m
            # Feed the target's estimated world velocity forward, otherwise
            # track mode lags and oscillates on a moving ball. The velocity
            # comes from the vision estimate, never ground truth.
            v_cmd = (self.target_vel_est +
                     self.controller_gain * error)
            speed = float(np.linalg.norm(v_cmd))
            speed_limit = (self.track_max_speed
                           if self.engage_mode == "track"
                           else self.max_speed)
            if speed > speed_limit:
                v_cmd *= speed_limit / speed
            if (self.engage_mode == "push" and
                    self.push_altitude_m > 0.0):
                # Approach at the height the light will be pushed at, not
                # at the estimated light height.
                v_cmd[2] = float(np.clip(
                    1.5 * (self.push_altitude_m -
                           float(platform_pos[2])) -
                    0.6 * float(platform_vel[2]), -0.5, 0.6))

            if (self.engage_mode == "push" and
                    self.target_motion == "static" and
                    self.strike_speed > 0.0 and
                    float(np.linalg.norm(to_target)) <=
                    self.strike_trigger_m):
                # Vision has locked the light: stop creeping in with the
                # position loop and charge. This tick keeps the seek
                # command; the strike branch takes over on the next tick.
                self.flight_state = "strike"
                self.strike_start = now
                self.push_aim = self.target_pos.copy()
                self.get_logger().info(
                    "target locked: range=%.2f m -> strike at %.2f m/s"
                    % (float(np.linalg.norm(to_target)), self.strike_speed))
            elif (self.engage_mode == "impact" and
                    float(np.linalg.norm(self.vision_rel)) <=
                    self.terminal_trigger_m):
                self._begin_terminal(now)
                v_cmd = self.terminal_cmd
            elif (self.engage_mode == "push" and
                  float(np.linalg.norm(to_target)) <=
                  self.push_engage_m):
                # Hand over from the position chase to the sustained push
                # while the light is still in front of the nose.
                self.flight_state = "push"
                self.pushing = True
                self.push_time = now
                self.push_contact_force = 0.0
                # Freeze the aim while the target still fits in the frame;
                # close-range measurements are unreliable. For a static map
                # target the map coordinates are exact.
                if self.target_motion == "static":
                    self.push_aim = self.target_pos.copy()
                else:
                    self.push_aim = self.est_pos.copy()
                self.get_logger().info(
                    "push engage: range=%.2f m, closing at %.2f m/s"
                    % (float(np.linalg.norm(to_target)), self.push_speed))
                v_cmd = np.zeros(3)
        elif self.last_los_world is not None:
            # Detection lost: point the camera down the last known line of
            # sight, sink back to the working altitude and sweep the nose
            # slowly until the light reappears.
            lost_s = now - self.vision_time
            search_altitude = (
                self.push_altitude_m
                if (self.engage_mode == "push" and
                    self.push_altitude_m > 0.0)
                else self.takeoff_altitude_m)
            search_yaw = math.atan2(self.last_los_world[1],
                                    self.last_los_world[0])
            if lost_s > 1.0:
                search_yaw += 0.6 * (lost_s - 1.0)
            self.yaw_cmd = self._blend_angle(
                self.yaw_cmd, search_yaw, min(1.0, dt / 0.5))
            if lost_s > 0.5:
                dz = search_altitude - float(platform_pos[2])
                v_cmd = np.array([
                    0.0, 0.0, float(np.clip(2.0 * dz, -0.4, 0.4))])
        else:
            # 还没看到目标：按地图上灯的已知位置巡航过去。起飞点（白色 H
            # 牌）离灯约 10 m，5.7 cm 的灯在那时不到一个像素，视觉要飞到
            # 2 m 左右才能锁定；在那之前就朝灯的地图坐标盲飞，速度随距离
            # 收窄（离灯 1 m 时减到零），一出现检测立刻切回视觉闭环。
            to_target = self.target_pos - platform_pos
            target_yaw = math.atan2(to_target[1], to_target[0])
            self.yaw_cmd = self._blend_angle(
                self.yaw_cmd, target_yaw, min(1.0, dt / 0.2))
            dist_xy = float(np.linalg.norm(to_target[:2]))
            # 制动剖面：v = 1.0 * (d - 1.4)。斜率 1.0 意味着 dv/dt = -v，
            # 4 m/s 时减速度 4 m/s²（约 22° 机头上仰），相机轴只抬到
            # 32°，灯仍在 35° 半视场内。2.6 m 视觉交接时速度约 1.2 m/s。
            speed = min(self.search_speed,
                        1.0 * max(dist_xy - 1.4, 0.0))
            # Ease the cruise in: zero acceleration at both ends, so the
            # nose comes down smoothly instead of stepping to the tilt
            # limit.
            ease = min(1.0, max(
                0.0, (now - self.seek_start) / self.seek_ramp_s))
            speed *= ease * ease * (3.0 - 2.0 * ease)
            v_cmd = np.array([
                math.cos(self.yaw_cmd) * speed,
                math.sin(self.yaw_cmd) * speed, 0.0])
            cruise_altitude = (
                self.push_altitude_m
                if (self.engage_mode == "push" and
                    self.push_altitude_m > 0.0)
                else self.takeoff_altitude_m)
            # 起飞点是一块离地面 1.73 m 的 H 牌，牌面只有约 0.35 m 宽。
            # 离起飞点 0.4 m 内保持起飞高度，0.4–1.0 m 之间平滑过渡到
            # 巡航高度（0.3–0.8 m 的过渡带）。
            start = (self.platform_start
                     if self.platform_start is not None else platform_pos)
            clear = float(np.clip(
                (float(np.linalg.norm(
                    (platform_pos - start)[:2])) - 0.3) / 0.5, 0.0, 1.0))
            cruise_altitude = (self.takeoff_altitude_m +
                               (cruise_altitude -
                                self.takeoff_altitude_m) * clear)
            # Gain 2.5 (tau 0.4 s) rather than 1.5: the last 20 cm of the
            # 1.4 m descent are an exponential tail; arriving high is what
            # makes the aircraft catch the head's top edge on the way down.
            v_cmd[2] = float(np.clip(
                2.5 * (cruise_altitude - float(platform_pos[2])) -
                0.6 * float(platform_vel[2]),
                -self.cruise_descent_mps, 0.6))
        return v_cmd

    # ---- Terminal (impact mode) -----------------------------------------
    def _terminal_aim(self):
        range_m = float(np.linalg.norm(self.vision_rel))
        time_to_go = min(range_m / max(self.impact_speed, 0.1), 0.5)
        if self.est_pos is not None:
            lead = self.target_vel_est * time_to_go
            # A real light does not move; the vision velocity estimate can
            # spike during the takeoff->seek pitch-over. Cap the lead.
            lead[2] = float(np.clip(lead[2], -0.25, 0.25))
            lead_norm = float(np.linalg.norm(lead))
            if lead_norm > 0.6:
                lead *= 0.6 / lead_norm
            aim = self.est_pos + lead
        else:
            aim = self.platform_pos + np.array(
                [self.vision_rel[0], -self.vision_rel[1],
                 -self.vision_rel[2]])
        return aim, range_m, time_to_go

    def _update_terminal_command(self):
        aim, range_m, time_to_go = self._terminal_aim()
        direction = aim - self.platform_pos
        distance = float(np.linalg.norm(direction))
        if distance < 1e-3:
            direction = np.array([1.0, 0.0, 0.0])
            distance = 1.0
        self.terminal_cmd = direction / distance * self.impact_speed
        # Follow the refreshed aim with a short ~0.1 s lag instead of
        # rotating the nose in one step.
        desired_yaw = math.atan2(self.terminal_cmd[1],
                                 self.terminal_cmd[0])
        self.yaw_cmd = self._blend_angle(self.yaw_cmd, desired_yaw, 0.06)
        return aim, range_m, time_to_go

    def _begin_terminal(self, now):
        self.terminal_start = now
        aim, range_m, time_to_go = self._update_terminal_command()
        self.get_logger().info(
            "terminal guidance: range=%.2f m, lead=%.2f s, aim=(%.2f, %.2f, "
            "%.2f), speed=%.1f m/s"
            % (range_m, time_to_go, aim[0], aim[1], aim[2],
               self.impact_speed))

    # ---- Outputs ---------------------------------------------------------
    def _publish_command(self, v_world, now, valid):
        """Publish the guidance output as a body-FRD velocity command."""
        period = 1.0 / max(self.vision_control_hz, 1.0)
        if now - self.last_vision_control_time < period:
            return
        self.last_vision_control_time = now

        # Heading is closed here and sent as a body yaw RATE: a proportional
        # term on the measured heading error plus a smoothed derivative of
        # the setpoint (feedforward). World yaw is positive about +z up;
        # VelocityCommand.wz is body FRD (z down), so it is negated below.
        # The rate is clamped so a setpoint jump cannot ask for an absurd
        # turn.
        self.yaw_rate_cmd = 0.0
        if self.yaw_cmd is not None:
            feedforward = 0.0
            if (self.last_published_yaw is not None and
                    now - self.last_published_yaw_time > 1e-4):
                dt = now - self.last_published_yaw_time
                delta = math.atan2(
                    math.sin(self.yaw_cmd - self.last_published_yaw),
                    math.cos(self.yaw_cmd - self.last_published_yaw))
                feedforward = max(-2.0, min(2.0, delta / dt))
                self.yaw_rate_ff += (
                    feedforward - self.yaw_rate_ff) * min(1.0, dt / 0.05)
            self.last_published_yaw = self.yaw_cmd
            self.last_published_yaw_time = now

            rot = self.platform_rot
            current_yaw = math.atan2(rot[1, 0], rot[0, 0])
            error = math.atan2(
                math.sin(self.yaw_cmd - current_yaw),
                math.cos(self.yaw_cmd - current_yaw))
            rate = self.yaw_rate_gain * error + self.yaw_rate_ff
            self.yaw_rate_cmd = max(-2.0, min(2.0, rate))
        if self.vision_control_pub is None:
            return

        velocity_body_flu = self.platform_rot.T @ np.asarray(
            v_world, dtype=float)
        # Body FRD components, with optional per-axis limits. Clamping here
        # applies to every phase and is what the flight controller actually
        # receives (the debug log still shows the unclamped demand).
        vx_frd = float(velocity_body_flu[0])
        vy_frd = float(-velocity_body_flu[1])
        vz_frd = float(-velocity_body_flu[2])
        if self.max_vx_mps > 0.0:
            vx_frd = max(-self.max_vx_mps, min(self.max_vx_mps, vx_frd))
        if self.max_vy_mps > 0.0:
            vy_frd = max(-self.max_vy_mps, min(self.max_vy_mps, vy_frd))
        if self.max_vz_mps > 0.0:
            vz_frd = max(-self.max_vz_mps, min(self.max_vz_mps, vz_frd))
        msg = VelocityCommandMsg()
        msg.schema_version = 1
        msg.sequence = self.vision_control_seq
        msg.stamp = self.get_clock().now().to_msg()
        msg.reset_counter = self.reset_counter
        msg.source_id = self.vision_control_source_id
        msg.frame_id = "body_frd"
        msg.valid = bool(valid)
        msg.vx = vx_frd
        msg.vy = vy_frd
        msg.vz = vz_frd
        msg.wz = float(-self.yaw_rate_cmd)
        self.vision_control_seq += 1
        self.vision_control_pub.publish(msg)

    def _publish_navigation(self, now):
        """Waypoint command for the flight controller, on its own topic.

        Active only before the target is detected: while the mission has no
        vision lock the FC follows the map prior. As soon as a fresh
        measurement arrives (or the state machine leaves takeoff/seek) the
        message goes valid=false and the FC switches to /visioncontrol.
        """
        if self.navigation_command_pub is None:
            return
        if now - self.last_navigation_time < 1.0 / self.navigation_command_hz:
            return
        self.last_navigation_time = now

        fresh_vision = (
            self.vision_rel is not None and
            now - self.vision_time <= self.command_timeout_s)
        waypoint_active = (
            self.control_enabled and not self.impacted and
            not fresh_vision and
            self.flight_state in ("takeoff", "seek"))

        msg = NavigationCommandMsg()
        msg.schema_version = 1
        msg.sequence = self.navigation_seq
        msg.stamp = self.get_clock().now().to_msg()
        msg.reset_counter = self.reset_counter
        msg.source_id = self.vision_control_source_id
        msg.frame_id = "fc01_vision_ned"
        msg.valid = bool(waypoint_active)
        msg.mode = (NavigationCommandMsg.CRUISE if waypoint_active
                    else NavigationCommandMsg.HOLD)
        msg.position_valid = bool(waypoint_active)
        # World is ENU (x east, y north, z up); the message is NED.
        waypoint_x = float(self.target_x)
        waypoint_y = float(self.target_y)
        waypoint_z = float(self._push_altitude())
        msg.position = [waypoint_y, waypoint_x, -waypoint_z]
        msg.yaw_valid = bool(waypoint_active and self.yaw_cmd is not None)
        if self.yaw_cmd is not None:
            # ENU yaw (CCW from +x/east) -> NED heading (CW from north).
            ned_yaw = math.pi / 2.0 - self.yaw_cmd
            msg.yaw = math.atan2(math.sin(ned_yaw), math.cos(ned_yaw))
        else:
            msg.yaw = 0.0
        msg.sticks_valid = False
        msg.sticks = [0.0, 0.0, 0.0, 0.0]
        self.navigation_seq += 1
        self.navigation_command_pub.publish(msg)

    def _publish_state(self, now):
        if self.state_publish_hz <= 0.0:
            return
        if now - self.last_state_time < 1.0 / self.state_publish_hz:
            return
        self.last_state_time = now
        self.state_pub.publish(String(data=self.flight_state))

    def _debug_log(self, now):
        if self.control_debug_hz <= 0.0:
            return
        if now - self.last_control_debug < 1.0 / self.control_debug_hz:
            return
        self.last_control_debug = now
        age = (now - self.vision_time
               if self.vision_rel is not None else -1.0)
        if self.push_aim is not None:
            push_range = float(np.linalg.norm(
                self.push_aim - self.platform_pos))
        else:
            push_range = -1.0
        rot = self.platform_rot
        roll = math.degrees(math.atan2(rot[2, 1], rot[2, 2]))
        pitch = math.degrees(math.asin(max(-1.0, min(1.0, -rot[2, 0]))))
        yaw_meas = math.degrees(math.atan2(rot[1, 0], rot[0, 0]))
        self.get_logger().info(
            "ctrl state=%s v_cmd=(%.2f, %.2f, %.2f) "
            "vel=(%.2f, %.2f, %.2f) pos=(%.2f, %.2f, %.2f) "
            "rpy=(%.0f, %.0f) yaw=%.0fdeg yaw_meas=%.0fdeg "
            "wz=%.2frad/s age=%.3fs "
            "pose_age=%.3fs tvel=(%.2f, %.2f, %.2f) "
            "push_range=%.2fm force=%.1fN"
            % (self.flight_state, self.last_v_cmd[0], self.last_v_cmd[1],
               self.last_v_cmd[2], self.platform_vel[0],
               self.platform_vel[1], self.platform_vel[2],
               self.platform_pos[0], self.platform_pos[1],
               self.platform_pos[2], roll, pitch,
               math.degrees(self.yaw_cmd) if self.yaw_cmd is not None else 0.0,
               yaw_meas, self.yaw_rate_cmd,
               age, now - self.platform_pose_time,
               self.target_vel_est[0], self.target_vel_est[1],
               self.target_vel_est[2], push_range, self.push_contact_force))


def main(args=None):
    rclpy.init(args=args)
    node = MissionNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
