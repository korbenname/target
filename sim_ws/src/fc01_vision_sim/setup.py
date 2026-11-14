import glob
import os

from setuptools import setup

package_name = "fc01_vision_sim"

setup(
    name=package_name,
    version="0.1.0",
    packages=[package_name],
    data_files=[
        ("share/ament_index/resource_index/packages",
         ["resource/" + package_name]),
        ("share/" + package_name, ["package.xml"]),
        (os.path.join("share", package_name, "launch"),
         glob.glob("launch/*.launch.py")),
        (os.path.join("share", package_name, "config"),
         glob.glob("config/*.yaml")),
        # Impact-drone STL (visual) and its convex hull (collision).
        (os.path.join("share", package_name, "assets"),
         glob.glob("assets/*")),
    ],
    install_requires=["setuptools"],
    zip_safe=True,
    maintainer="han",
    maintainer_email="han@example.com",
    description="MuJoCo simulation for the fc01 vision pipeline",
    license="Apache-2.0",
    tests_require=["pytest"],
    entry_points={
        "console_scripts": [
            "vision_sim = fc01_vision_sim.sim_node:main",
        ],
    },
)
