"""Vertex-cluster decimation of a binary STL into a mesh MuJoCo can load.

MuJoCo refuses meshes with more than 200000 faces. The impact-drone STL has
422462 triangles; clustering the vertices on a 0.15 mm grid keeps 153585 of
them, which is visually indistinguishable at the simulated 0.32 m wingspan.

The OBJ is written in metres, centred on its bounding-box centre, matching the
``platform_visual`` transform used by scene.py.

Usage:
  python3 tools/decimate_stl.py <impact_drone.stl> \
      assets/impact_drone_lod.obj [cell_mm]
"""
import struct
import sys

import numpy as np

src, dst = sys.argv[1], sys.argv[2]
cell = float(sys.argv[3]) if len(sys.argv) > 3 else 0.15

with open(src, "rb") as f:
    f.read(80)
    n = struct.unpack("<I", f.read(4))[0]
    raw = f.read(n * 50)
tris = np.frombuffer(raw, dtype=np.uint8).reshape(n, 50)
pts = tris[:, 12:48].copy().view("<f4").reshape(n * 3, 3).astype(np.float64)

mn = pts.min(0)
key = np.floor((pts - mn) / cell).astype(np.int64)
uniq, inv = np.unique(key, axis=0, return_inverse=True)
count = np.bincount(inv, minlength=len(uniq))
verts = np.zeros((len(uniq), 3))
np.add.at(verts, inv, pts)
verts /= count[:, None]

faces = inv.reshape(-1, 3)
good = ((faces[:, 0] != faces[:, 1]) & (faces[:, 1] != faces[:, 2]) &
        (faces[:, 0] != faces[:, 2]))
faces = faces[good]
faces = np.unique(np.sort(faces, axis=1), axis=0)

centre = (verts.min(0) + verts.max(0)) / 2.0
verts = (verts - centre) * 0.001  # mm -> m, centred
with open(dst, "w") as out:
    out.write("# decimated from %s, cell=%.3f mm\n" % (src, cell))
    for v in verts:
        out.write("v %.6f %.6f %.6f\n" % tuple(v))
    for face in faces:
        out.write("f %d %d %d\n" % (face[0] + 1, face[1] + 1, face[2] + 1))
print("in faces", n, "out verts", len(verts), "out faces", len(faces))
