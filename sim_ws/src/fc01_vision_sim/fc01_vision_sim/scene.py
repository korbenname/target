"""MuJoCo scene for the fc01 vision pipeline.

World frame: X forward, Y left, Z up.

The platform is a 6-DoF quadrotor (free joint) with four rotors. The node
computes thrust for each rotor and applies it at the rotor positions, so
attitude, acceleration and impacts emerge from the rigid-body dynamics. The
target is still a mocap body with a scripted trajectory (infinite mass), but
contacts with it are real.

Camera: FPV camera at the nose, pitched up by ``camera_pitch_deg``. The same
angle must be configured in the vision node so that ``target_relative`` is
expressed in body FRD rather than in the tilted camera frame.
"""

import math

# Rotor plane height in the body frame.
ARM_Z = 0.02
# Spin direction of each rotor, FL, FR, RL, RR (used for yaw torque).
ROTOR_SPIN = (1.0, -1.0, -1.0, 1.0)
# Camera position in the body frame (body origin = centre of mass). The
# supplied model is only 11.9 cm across, so the lens sits just off the nose
# (2 cm ahead of the 5.9 cm half-length) instead of the 24 cm used by the old
# scaled-up placeholder.
CAMERA_POS = (0.08, 0.0, 0.015)

# Largest side of the supplied model's bounding box, in metres. Both
# tools/decimate_stl.py and tools/make_hull.py write their OBJ in metres,
# centred on the bounding-box centre, so the visual and the collision hull
# share one scale factor and sit directly on the body origin.
IMPACT_MESH_MAX_DIM_M = 0.1187974472

# The supplied STL is Y-up (its 7.3 cm thickness is the height), so used raw
# in this Z-up world the aircraft lies on its side. Rotate it +90 deg about
# body x to stand it upright: (x, y, z) -> (x, -z, y).
MESH_UP_QUAT = "0.707107 0.707107 0 0"

# Invisible contact panel on the base head's front face, centred on the
# light. The plate normal points along world x, the direction the drone
# approaches from. It is deliberately much larger than the 5.7 cm lamp:
#  - half-width 12 cm (24 cm wide) so the 12 cm wide drone always meets the
#    flat face even when the strike arrives a few centimetres off-centre;
#    a narrow plate lets a strike catch its side edge and spin the airframe;
#  - half-height 20 cm (40 cm tall) so the drone cannot climb onto the top
#    edge after a 1.6 m/s impact. The hull is 7.3 cm tall and the strike
#    rebound can lift it ~0.15 m; with the panel top at 1.573 m the hull's
#    lowest corner stays below it, so the contact stays face-on.
#  - half-thickness 4 cm: a 2 m/s strike sinks ~1 cm into a soft contact, and
#    a 1 cm plate could be straddled or punched through entirely (the drone
#    ended up wedged behind the plate). A thick slab cannot be crossed.
# The west face sits TARGET_PROXY_FACE_OFFSET in front of the light centre.
# Both numbers are invisible to the viewer and the camera (rgba 0).
TARGET_PROXY_HALF_THICKNESS = 0.04
TARGET_PROXY_HALF_WIDTH = 0.12
TARGET_PROXY_HALF_HEIGHT = 0.20
TARGET_PROXY_FACE_OFFSET = -0.01

# Contact class shared by the invisible nose pad and the panel, and no other
# geom (see contype/conaffinity below). The map's collision heightfield does
# not match its visual model: around the light it is a steep wall whose west
# edge sits at x ~= 0.309 m, only a few millimetres behind the panel. A nose
# pad that also collided with the map caught that slope with its lower edge,
# took a ~100 N upward kick (contact normal (0, 0, 1)), rebounded and then
# hung on the head's top edge pitched 18 deg - the visible "hit with a
# corner". With a private contact class the pad meets only the flat panel,
# while the visible hull still collides with the map as before.
# Bit 4 is free: the map heightfield is contype=2 conaffinity=1, the drone
# hull is 1/1, so (4 & 1) | (2 & 4) = 0 keeps this class away from the map.
TARGET_CONTACT_CLASS = "4 4"

SCENE_TEMPLATE = """
<mujoco model="fc01_vision_sim">
  <compiler angle="degree"/>
  <option timestep="0.005" gravity="0 0 -9.81"/>
  <visual>
    <headlight ambient="0.35 0.35 0.35" diffuse="0.6 0.6 0.6"
               specular="0.1 0.1 0.1"/>
    <map znear="0.01" zfar="100"/>
  </visual>
{map_include}
  <asset>
    <texture name="grid" type="2d" builtin="checker" width="512"
             height="512" rgb1="0.22 0.24 0.26" rgb2="0.34 0.36 0.38"/>
    <material name="grid" texture="grid" texrepeat="10 10"
              reflectance="0.05"/>
{platform_assets}
  </asset>
  <worldbody>
    <light name="sun" pos="0 0 8" dir="0 0 -1" diffuse="0.9 0.9 0.9"
           ambient="0.4 0.4 0.4"/>
{ground_geom}
{pad_geom}
{marker_geom}

    <body name="target" mocap="true" pos="{target_x} {target_y} {target_z}">
      <!-- A soft contact (20 Hz, critical damping) so a push settles into
           steady contact instead of bouncing the drone off the fixed ball.
           The real light is a flat face on the vertical side of the base
           head, so the proxy is a thin vertical plate rather than a sphere:
           a sphere lets the drone's belly ride up over it (the contact
           normal tilts upward and the airframe climbs and slowly pitches
           over). With a flat west face the contact normal stays horizontal
           at any altitude, so the strike transfers no pitching torque. -->
      <geom name="target_geom" type="box" pos="{target_proxy_dx} 0 {target_proxy_dz}"
            size="{target_thickness} {target_half_width} {target_half_height}"
            rgba="{target_rgba}" contype="{target_contype}"
            conaffinity="{target_conaffinity}"
            solref="0.05 1" solimp="0.9 0.99 0.001"/>
    </body>

    <body name="platform" pos="0 0 {platform_z}">
      <freejoint name="platform_free"/>
      <!-- 1 kg class frame; COM at the body origin. -->
      <inertial pos="0 0 0" mass="{mass}"
                diaginertia="{ixx} {iyy} {izz}"/>
      <!-- Camera at the nose, pitched up for forward flight. -->
      <camera name="fpv" pos="{cam_x} 0 {cam_z}"
              xyaxes="0 -1 0 {cam_up_y} 0 {cam_up_z}"
              fovy="{camera_fovy_deg}"/>
{platform_geoms}
    </body>
  </worldbody>
</mujoco>
"""


def rotor_positions(arm_length):
    """Rotor positions in the body frame, order FL, FR, RL, RR."""
    a = float(arm_length)
    return (
        (a, a, ARM_Z),
        (a, -a, ARM_Z),
        (-a, a, ARM_Z),
        (-a, -a, ARM_Z),
    )


def _primitive_platform_geoms(arm_length, camera_pos):
    """The original simplified quadrotor drawing (no mesh model)."""
    arm = float(arm_length)
    cam_x, _, cam_z = camera_pos
    return """
      <!-- Collidable frame and camera boom. Class 5/5: they touch both the
           map (bits 1/2) and the light panel (bit 4). -->
      <geom name="frame" type="box" size="0.10 0.06 0.03"
            rgba="0.10 0.10 0.10 1" contype="5" conaffinity="5"/>
      <!-- Canopy: visual only. -->
      <geom name="canopy" type="box" size="0.065 0.042 0.014"
            pos="0 0 0.038" rgba="0.15 0.32 0.62 1"
            contype="0" conaffinity="0"/>
      <geom name="boom" type="capsule" size="0.012"
            fromto="0.08 0 0.01 {cam_x} 0 {cam_z}"
            rgba="0.16 0.16 0.16 1" contype="5" conaffinity="5"/>
      <!-- X-frame arms and rotor discs; props do not collide. -->
      <geom name="arm_fl" type="capsule" size="0.008"
            fromto="0 0 0 {arm} {arm} {arm_z}"
            rgba="0.16 0.16 0.16 1" contype="0" conaffinity="0"/>
      <geom name="arm_fr" type="capsule" size="0.008"
            fromto="0 0 0 {arm} -{arm} {arm_z}"
            rgba="0.16 0.16 0.16 1" contype="0" conaffinity="0"/>
      <geom name="arm_rl" type="capsule" size="0.008"
            fromto="0 0 0 -{arm} {arm} {arm_z}"
            rgba="0.16 0.16 0.16 1" contype="0" conaffinity="0"/>
      <geom name="arm_rr" type="capsule" size="0.008"
            fromto="0 0 0 -{arm} -{arm} {arm_z}"
            rgba="0.16 0.16 0.16 1" contype="0" conaffinity="0"/>
      <geom name="rotor_fl" type="cylinder" size="0.08 0.004"
            pos="{arm} {arm} {arm_z}" rgba="0.18 0.18 0.20 0.55"
            contype="0" conaffinity="0"/>
      <geom name="rotor_fr" type="cylinder" size="0.08 0.004"
            pos="{arm} -{arm} {arm_z}" rgba="0.18 0.18 0.20 0.55"
            contype="0" conaffinity="0"/>
      <geom name="rotor_rl" type="cylinder" size="0.08 0.004"
            pos="-{arm} {arm} {arm_z}" rgba="0.18 0.18 0.20 0.55"
            contype="0" conaffinity="0"/>
      <geom name="rotor_rr" type="cylinder" size="0.08 0.004"
            pos="-{arm} -{arm} {arm_z}" rgba="0.18 0.18 0.20 0.55"
            contype="0" conaffinity="0"/>
""".format(arm=arm, arm_z=ARM_Z, cam_x=cam_x, cam_z=cam_z)


def _mesh_platform_geoms():
    """The supplied impact-drone model, exactly as given.

    The full mesh is drawn as-is (no added rotor discs, arms or camera boom).
    Collision uses a small convex hull generated by tools/make_hull.py so
    MuJoCo does not have to hull 420k triangles at load time; the hull is
    invisible and only collides. Both OBJ files are already centred on their
    bounding-box centre, so the geoms sit directly on the body origin.
    ``MESH_UP_QUAT`` turns the STL's Y-up frame upright in this Z-up world.
    The model is used at its real size: 11.88 x 11.87 x 7.3 cm, 240 g.
    """
    return """
      <!-- Convex hull of the STL: collision only, invisible (alpha 0) so the
           viewer shows the model exactly as supplied. -->
      <geom name="impact_hull" type="mesh" mesh="platform_collision"
            quat="{quat}" rgba="0 0 0 0" contype="1" conaffinity="1"
            group="3"/>
      <!-- Invisible flat nose pad (6 x 6 cm, 8.6 mm proud of the hull's
           front). The hull is a lumpy 157-face convex hull, so pressing it
           against the light panel contacts at an arbitrary point and the
           resulting torque rocks the 240 g airframe until the contact
           spits it sideways. This pad gives a flat vertical face centred
           on the centre of mass, so the contact resultant is horizontal
           and passes through the CoM. It uses contact class 4/4 so it
           touches the light panel only, never the map's collision
           heightfield (see TARGET_CONTACT_CLASS). Collision only; the visual
           mesh is untouched. -->
      <geom name="impact_bumper" type="box" pos="0.062 0 0"
            size="0.006 0.03 0.03" rgba="0 0 0 0"
            contype="4" conaffinity="4" group="3"/>
      <!-- The supplied model, untouched: no added arms, rotors or camera boom.
           Thrust is still applied at the four rotor points (no geoms needed). -->
      <geom name="impact_visual" type="mesh" mesh="platform_visual"
            quat="{quat}" rgba="0.55 0.57 0.62 1" contype="0"
            conaffinity="0"/>
""".format(quat=MESH_UP_QUAT)


def _h_pad_geoms(pad_x, pad_y, pad_z, pad_size, pad_yaw=0.0):
    """A white square pad with a dark H, visual only (no collision)."""
    half = 0.5 * float(pad_size)
    bar_len = 0.62 * float(pad_size)
    bar_w = 0.13 * float(pad_size)
    spacing = 0.34 * float(pad_size)
    cross_w = bar_w
    z = float(pad_z) + 0.004
    c = math.cos(0.5 * pad_yaw)
    s = math.sin(0.5 * pad_yaw)
    quat = "%.6f 0 0 %.6f" % (c, s)

    def box(name, dx, dy, sx, sy, dz, rgba):
        return (
            '\n      <geom name="%s" type="box" pos="%g %g %g" '
            'quat="%s" size="%g %g %g" rgba="%s" contype="0" '
            'conaffinity="0"/>'
            % (name, float(pad_x) + dx, float(pad_y) + dy, z + dz,
               quat, sx, sy, 0.003, rgba))

    out = box("pad_base", 0.0, 0.0, half, half, 0.0, "0.88 0.88 0.88 1")
    out += box("pad_h_left", -0.5 * spacing, 0.0,
               0.5 * bar_w, 0.5 * bar_len, 0.002, "0.04 0.04 0.04 1")
    out += box("pad_h_right", 0.5 * spacing, 0.0,
               0.5 * bar_w, 0.5 * bar_len, 0.002, "0.04 0.04 0.04 1")
    out += box("pad_h_cross", 0.0, 0.0,
               0.5 * spacing, 0.5 * cross_w, 0.002, "0.04 0.04 0.04 1")
    return out


def mesh_scale_for_arm(arm_length):
    """Scale factor so the model spans the rotor diameter."""
    return 2.0 * float(arm_length) / IMPACT_MESH_MAX_DIM_M


def build_scene(target_radius, camera_fovy_deg, target_x=5.0, target_y=0.0,
                target_z=1.2, platform_z=1.2, ground_size=20.0,
                arm_length=0.16, mass=1.0, inertia=(0.010, 0.010, 0.018),
                camera_pitch_deg=10.0, map_xml=None,
                pad=None, marker=None, target_visible=True,
                platform_mesh=None, platform_mesh_hull=None,
                platform_mesh_scale=None, target_proxy_dz=0.0):
    """Build the MJCF string.

    ``map_xml`` is an optional absolute path to a full MJCF file whose
    worldbody/asset sections replace the flat checker ground with a map
    (e.g. the RMUC2027 field). Relative asset paths inside that file are
    resolved by MuJoCo relative to the included file.

    ``pad`` is ``(x, y, z, size, yaw)`` or None. ``marker`` is
    ``(x, y, z, radius)`` or None. ``platform_mesh`` / ``platform_mesh_hull``
    are absolute STL/OBJ paths; when both are set the STL replaces the
    primitive frame for appearance and the hull replaces its collision.
    """
    tilt = math.radians(float(camera_pitch_deg))
    cam_x, _, cam_z = CAMERA_POS

    if map_xml:
        map_include = '<include file="%s"/>' % map_xml
        ground_geom = ""
    else:
        map_include = ""
        ground_geom = (
            '<geom name="ground" type="plane" '
            'size="%g %g 0.1" material="grid" '
            'contype="1" conaffinity="1"/>'
            % (float(ground_size), float(ground_size)))

    pad_geom = ""
    if pad is not None:
        px, py, pz, psize = [float(v) for v in pad[:4]]
        pyaw = float(pad[4]) if len(pad) > 4 else 0.0
        pad_geom = _h_pad_geoms(px, py, pz, psize, pyaw)

    marker_geom = ""
    if marker is not None:
        mx, my, mz, mr = [float(v) for v in marker]
        marker_geom = (
            '\n    <geom name="target_marker" type="cylinder" '
            'pos="%g %g %g" size="%g 0.002" rgba="0.05 0.85 0.15 1" '
            'contype="0" conaffinity="0"/>'
            % (mx, my, mz, mr))

    platform_assets = ""
    if platform_mesh and platform_mesh_hull:
        if platform_mesh_scale is None or float(platform_mesh_scale) <= 0.0:
            mesh_scale = mesh_scale_for_arm(arm_length)
        else:
            mesh_scale = float(platform_mesh_scale)
        # Both OBJ files are in metres, so the same factor scales each of
        # them to the rotor diameter.
        platform_assets = (
            '\n    <mesh name="platform_visual" file="%s" '
            'scale="%.9f %.9f %.9f"/>'
            '\n    <mesh name="platform_collision" file="%s" '
            'scale="%.9f %.9f %.9f"/>'
            % (platform_mesh, mesh_scale, mesh_scale, mesh_scale,
               platform_mesh_hull, mesh_scale, mesh_scale, mesh_scale))
        platform_geoms = _mesh_platform_geoms()
    else:
        platform_geoms = _primitive_platform_geoms(arm_length, CAMERA_POS)

    ixx, iyy, izz = [float(v) for v in inertia]
    return SCENE_TEMPLATE.format(
        map_include=map_include,
        ground_geom=ground_geom,
        pad_geom=pad_geom,
        marker_geom=marker_geom,
        platform_assets=platform_assets,
        platform_geoms=platform_geoms,
        target_half_width=TARGET_PROXY_HALF_WIDTH,
        target_half_height=TARGET_PROXY_HALF_HEIGHT,
        target_thickness=TARGET_PROXY_HALF_THICKNESS,
        target_contype=TARGET_CONTACT_CLASS.split()[0],
        target_conaffinity=TARGET_CONTACT_CLASS.split()[1],
        target_rgba=("0.05 0.85 0.15 1" if target_visible
                     else "0 0 0 0"),
        camera_fovy_deg=float(camera_fovy_deg),
        target_x=float(target_x),
        target_y=float(target_y),
        target_z=float(target_z),
        target_proxy_dx=float(TARGET_PROXY_FACE_OFFSET +
                              TARGET_PROXY_HALF_THICKNESS),
        target_proxy_dz=float(target_proxy_dz),
        platform_z=float(platform_z),
        arm=float(arm_length),
        arm_z=ARM_Z,
        mass=float(mass),
        ixx=ixx, iyy=iyy, izz=izz,
        cam_x=cam_x,
        cam_z=cam_z,
        cam_up_y=-math.sin(tilt),
        cam_up_z=math.cos(tilt),
    )
