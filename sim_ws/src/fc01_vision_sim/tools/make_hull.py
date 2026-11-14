"""Build a small convex-hull OBJ from the impact-drone STL.

MuJoCo would otherwise have to hull ~420k triangles when loading the model.
The hull is written in metres, centred on its bounding-box centre, so the
``impact_hull`` geom sits on the body origin.

Usage:
  python3 tools/make_hull.py <impact_drone.stl> assets/impact_drone_hull.obj
"""
import struct
import sys

import numpy as np
from scipy.spatial import ConvexHull

src, dst = sys.argv[1], sys.argv[2]

with open(src, "rb") as f:
    f.read(80)
    n = struct.unpack("<I", f.read(4))[0]
    raw = f.read(n * 50)
tris = np.frombuffer(raw, dtype=np.uint8).reshape(n, 50)
pts = tris[:, 12:48].copy().view("<f4").reshape(n * 3, 3).astype(np.float64)
pts = np.unique(np.round(pts, 4), axis=0)
print("unique vertices", len(pts))

hull = ConvexHull(pts)
hp = pts[hull.vertices]
centre = (hp.min(0) + hp.max(0)) / 2.0
scale = 0.001  # STL is millimetres
verts = (hp - centre) * scale

# Weld the hull points back into the simplices (indices refer to pts).
index = {tuple(v): i for i, v in enumerate(hp)}
with open(dst, "w") as out:
    for v in verts:
        out.write("v %.9f %.9f %.9f\n" % tuple(v))
    for simplex in hull.simplices:
        out.write("f %d %d %d\n" % tuple(index[tuple(pts[i])] + 1
                                         for i in simplex))
print("hull verts", len(verts), "faces", len(hull.simplices))
print("bbox size m", (hp.max(0) - hp.min(0)) * scale)
print("volume m^3", hull.volume * scale**3)
