"""Render a set of stills of the map and the sim scene.

Usage:
  python3 src/fc01_vision_sim/tools/render_scene_images.py \
      <workspace_root> <output_dir>

Writes PNGs of the RMUC2027 map (top-down and eye level) and of the full
scene (map + the supplied impact-drone mesh, at its real 1:1 size, hovering
over the map's black/red-ring/white-H badge on the central ROBOMASTER mount
at (-10.15, -3.93, 1.731), ~10.5 m west of the green indicator light). The
green light is part of the map; the contact proxy is invisible, so no fake
ball appears. Uses MuJoCo's offscreen renderer, so no viewer window is
needed.
"""
import math
import os
import struct
import sys
import zlib

os.environ.setdefault("MUJOCO_GL", "egl")  # offscreen, no viewer needed

import mujoco

WORKSPACE = os.path.abspath(sys.argv[1])
OUT = os.path.abspath(sys.argv[2])
os.makedirs(OUT, exist_ok=True)

SRC = os.path.join(WORKSPACE, "src", "fc01_vision_sim")
sys.path.insert(0, SRC)
from fc01_vision_sim.scene import build_scene  # noqa: E402

MAP_XML = os.path.join(WORKSPACE, "RMUC2027", "scene_rmuc.xml")
ASSETS = os.path.join(SRC, "assets")

WIDTH, HEIGHT = 1000, 700


def write_png(path, rgb):
    h, w, _ = rgb.shape
    raw = b"".join(b"\x00" + rgb[y].tobytes() for y in range(h))

    def chunk(tag, payload):
        return (struct.pack(">I", len(payload)) + tag + payload +
                struct.pack(">I", zlib.crc32(tag + payload) & 0xFFFFFFFF))

    with open(path, "wb") as f:
        f.write(b"\x89PNG\r\n\x1a\n" +
                chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, 8, 2, 0, 0, 0)) +
                chunk(b"IDAT", zlib.compress(raw, 6)) +
                chunk(b"IEND", b""))


def make_renderer(model):
    model.vis.global_.offwidth = WIDTH
    model.vis.global_.offheight = HEIGHT
    model.vis.global_.fovy = 60.0
    model.vis.headlight.ambient[:] = (0.6, 0.6, 0.6)
    model.vis.headlight.diffuse[:] = (0.7, 0.7, 0.7)
    return mujoco.Renderer(model, HEIGHT, WIDTH)


def render_views(model, views, pose=None):
    """Render each (name, lookat, azimuth, elevation, distance) view.

    MuJoCo free-camera convention (verified against the compiled camera's
    pos/forward): ``azimuth`` is the direction the camera *looks* in the xy
    plane, measured from +x towards +y, and the camera sits on the opposite
    side of the lookat:

      az=0    camera on -x, looking +x
      az=90   camera on -y, looking +y
      az=180  camera on +x, looking -x
      az=270  camera on +y, looking -y

    ``elevation`` is likewise the view direction's elevation: positive looks
    up (camera below), negative looks down (camera above).
    """
    data = mujoco.MjData(model)
    if pose is not None:
        x, y, z, yaw_deg = pose
        jid = mujoco.mj_name2id(model, mujoco.mjtObj.mjOBJ_JOINT,
                                "platform_free")
        adr = model.jnt_qposadr[jid]
        yaw = math.radians(0.5 * yaw_deg)
        data.qpos[adr:adr + 3] = (x, y, z)
        data.qpos[adr + 3] = math.cos(yaw)
        data.qpos[adr + 6] = math.sin(yaw)
    mujoco.mj_forward(model, data)
    renderer = make_renderer(model)
    cam = mujoco.MjvCamera()
    mujoco.mjv_defaultCamera(cam)
    cam.type = mujoco.mjtCamera.mjCAMERA_FREE
    for name, lookat, az, el, dist in views:
        cam.lookat[:] = lookat
        cam.azimuth = az
        cam.elevation = el
        cam.distance = dist
        renderer.update_scene(data, cam)
        path = os.path.join(OUT, name + ".png")
        write_png(path, renderer.render())
        print("wrote", path)


# ---- map only -------------------------------------------------------------
map_model = mujoco.MjModel.from_xml_path(MAP_XML)
c = map_model.stat.center
# The field is 28 m along x and 16 m along y. With azimuth 90 the camera's up
# axis (and therefore the image vertical) runs along -y, so the long x axis is
# horizontal and 1.15 * extent (19.6 m) just fits the frame at fovy 60.
map_views = [
    ("01_map_topdown_field", (float(c[0]), float(c[1]), 0.0),
     90.0, -89.0, 1.15 * float(map_model.stat.extent)),
    # Eye level from the west, looking east (+x) at the green indicator light
    # on the ROBOMASTER base head: (0.315, -4.958, 1.373).
    ("02_map_eye_green_light_from_west", (0.315, -4.958, 1.36),
     0.0, -5.0, 2.6),
    ("03_map_eye_centre_structure", (-11.0, -5.0, 1.0), 90.0, -8.0, 5.0),
]
render_views(map_model, map_views)

# ---- full scene: map + drone + invisible contact proxy --------------------
# The green target is the map's own indicator light at
# (0.315, -4.958, 1.373); a 3 cm invisible sphere sits on it for contact.
xml = build_scene(
    target_radius=0.03, camera_fovy_deg=70.0, target_x=0.315,
    target_y=-4.958, target_z=1.373, platform_z=0.20, arm_length=0.04,
    mass=0.24, inertia=(0.0004, 0.0004, 0.0006), camera_pitch_deg=10.0,
    map_xml=MAP_XML, pad=None, marker=None, target_visible=False,
    platform_mesh=os.path.join(ASSETS, "impact_drone_lod.obj"),
    platform_mesh_hull=os.path.join(ASSETS, "impact_drone_hull.obj"),
    platform_mesh_scale=1.0)
scene_model = mujoco.MjModel.from_xml_string(xml)
# The drone hovers just above the map's white-H badge at (-10.15, -3.93,
# 1.775), nose yawed -5.6 deg toward the light 10.5 m to the east; the whole
# approach corridor runs along +x, descending to push altitude after it has
# cleared the badge.
START = (-10.15, -3.93, 1.775, -5.6)
MID = (-4.92, -4.44, 1.35)
scene_views = [
    ("04_scene_topdown_approach", (MID[0], MID[1], 0.0), 0.0, -89.0, 9.6),
    ("05_scene_side_from_west", (MID[0], MID[1], 1.0), 0.0, -10.0, 4.2),
    ("06_scene_3q_from_southeast", (MID[0], MID[1], 0.9), 135.0, -15.0, 4.0),
    ("07_scene_3q_from_southwest", (MID[0], MID[1], 0.9), 45.0, -12.0, 4.0),
    ("08_scene_green_light_closeup", (0.315, -4.958, 1.373),
     0.0, -3.0, 0.55),
    # Eye level from just above the badge, looking down the approach line.
    ("09_scene_view_from_h_badge", (START[0], START[1], START[2]),
     0.0, -4.0, 2.2),
    ("10_drone_model_closeup", (START[0], START[1], START[2]),
     135.0, -25.0, 0.35),
]
render_views(scene_model, scene_views, pose=START)

# Takeoff detail: the drone hovering over the black/red-ring/white-H badge
# on the central ROBOMASTER mount.
takeoff_views = [
    ("13_takeoff_on_h_badge_3q", (-10.15, -3.93, 1.76), 135.0, -25.0, 0.75),
    ("14_takeoff_on_h_badge_top", (-10.15, -3.93, 1.755), 90.0, -85.0, 0.55),
]
render_views(scene_model, takeoff_views, pose=START)

# Where the push loop leaves the drone: hull pressed against the light.
pressed_views = [
    ("11_scene_pressed_on_light", (0.23, -4.956, 1.35),
     35.0, -15.0, 0.85),
    ("12_scene_pressed_from_south", (0.23, -4.956, 1.35),
     90.0, -8.0, 0.9),
]
render_views(scene_model, pressed_views, pose=(0.23, -4.956, 1.34, 0.0))
