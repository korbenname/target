# fc01_bringup

**实机部署**入口。只做一件事：把实机需要的节点按正确参数拉起来，和 MuJoCo
仿真（`fc01_vision_sim`）彻底分开。

| 场景 | 入口 |
| --- | --- |
| 实机 | `ros2 launch fc01_bringup robot.launch.py` |
| 仿真 | 在独立工作区 `sim_ws` 构建后：`ros2 launch fc01_vision_sim vision_sim.launch.py` |

## 启动内容

```
fc01_vision_node   USB/V4L2 相机 → /fc01/vision/state (VisionState)
fc01_mission       /fc01/vision/state + 平台状态 → /visioncontrol
```

- 视觉用 `fc01_vision/config/vision.yaml`（相机设备、内参、检测阈值）；
- 制导用 `fc01_mission/config/mission.yaml`（状态机、目标先验、速度剖面）；
- 实机视觉节点只发 `VisionState`，所以任务节点强制
  `use_vision_state:=true`（它不消费 `target_relative`）。

飞控需要做的事：

- 订阅 `/navigation_command`（`jikl_fc01_system/NavigationCommand`）：**视觉锁定
  前**的航点指令，`valid=true` 时按 `CRUISE` 航点飞；一旦 `valid=false`（视觉已
  锁定）就切回 `/visioncontrol`；
- 订阅 `/visioncontrol`（`jikl_fc01_system/VelocityCommand`，机体系 FRD，
  `vx/vy/vz` + `wz` 偏航角速度），**depth 1 keep-last**；
- 发布 `/sim/platform_pose`、`/sim/platform_velocity`、
  `/sim/platform_angular_velocity`、`/sim/target_contact_force` 等平台状态
  （话题名可在 `mission.yaml` 里改）。没有平台位姿时制导节点不会发指令。

`/navigation_command` 和 `/visioncontrol` 是两个独立话题，可以同时订阅。航点指令
只在 `takeoff`/`seek` 且没有有效视觉时有效，随后 `valid=false`；飞控以
`valid` + 消息新鲜度为准决定用哪个。

## 构建

```bash
source /opt/ros/humble/setup.bash
cd /home/han/target
colcon build --symlink-install --packages-select \
  jikl_fc01_system fc01_vision fc01_mission fc01_bringup
source install/setup.bash
```

仿真包不在这个工作区，位于 `/home/han/target/sim_ws/src/`，见
[`sim_ws/src/fc01_vision_sim/README.md`](../../sim_ws/src/fc01_vision_sim/README.md)。

## 运行

```bash
# 默认：持续顶住、不弹调试窗口
ros2 launch fc01_bringup robot.launch.py

# 可视化在配置里开（持久）：fc01_vision/config/vision.yaml
#   visualization: true
# 打开后：OpenCV 实时标注 + 滑条窗口，同时发布 debug 图
ros2 launch fc01_bringup robot.launch.py

# 也可以只在本次运行临时开滑条窗口（不开 debug 图发布）
ros2 launch fc01_bringup robot.launch.py show_tuning_window:=true

# 只看视觉、不发飞控指令
ros2 launch fc01_bringup robot.launch.py control_enabled:=false

# 一次撞击 / 保持距离
ros2 launch fc01_bringup robot.launch.py engage_mode:=impact
ros2 launch fc01_bringup robot.launch.py engage_mode:=track

# 20 Hz 打印制导状态、实测航向、wz、视觉消息年龄
ros2 launch fc01_bringup robot.launch.py control_debug_hz:=20.0

# 额外用 rqt_image_view 显示带检测框的图像
ros2 launch fc01_bringup robot.launch.py show_debug:=true
```

## 相机选择

`fc01_vision/config/vision.yaml` 里 `device_index` 直接传给
`cv::VideoCapture.open`，只能填整数：

```yaml
device_index: 2
frame_width: 640
frame_height: 480
frame_fps: 120
use_mjpg: true
buffer_size: 4
```

**注意设备号会变**：`/dev/videoN` 是按枚举顺序分配的。实测这台机器接外接
摄像头时是 `video2`；外接拔掉后，内置相机也会变成 `video2`（并且画面全黑）。
接线后先用下面命令确认再启动：

```bash
for d in /sys/class/video4linux/video*; do echo "$d: $(cat $d/name)"; done
ls -l /dev/v4l/by-id/
```

每台相机会占两个节点，只有 by-id 里 `-video-index0` 对应的那个能取图。
`buffer_size: 1` 时这块 UVC 相机 120 fps 会掉到 60 fps，高帧率要用 4；低光照下
相机自动曝光可能把帧率降到 30。

## ARM 板部署

板子上只需要部署工作区的 4 个包；`sim_ws/`、MuJoCo 和 `RMUC2027/` 地图都不要
拷过去。

```bash
sudo apt install ros-humble-cv-bridge libopencv-dev python3-numpy
cd ~/target
colcon build --symlink-install --packages-select \
  jikl_fc01_system fc01_vision fc01_mission fc01_bringup
source install/setup.bash
ros2 launch fc01_bringup robot.launch.py
```

- Ubuntu 22.04 arm64 + ROS 2 Humble：原生编译即可；
- Jetson JetPack 5（Ubuntu 20.04）：Humble 不在 20.04 的 apt 源里，用
  `ros:humble` 的 arm64 容器或从源码编译；
- 无桌面环境时保持 `show_tuning_window:=false`、`show_debug:=false`，节点在
  没有 GUI 时会自动跳过窗口。

**性能**：120 fps、640×480 的 MJPEG 解码 + 检测在桌面 CPU 上约占 1.3 个核，
ARM 板不一定扛得住。先实测，再在 `fc01_vision/config/vision.yaml` 里降：

- `frame_fps` / `publish_rate_hz` 一起降到 60；
- 或 `frame_width/height` 降到 320×240（这块相机支持 320×240@120）；
- `buffer_size: 4` 必须保留，否则 120 fps 会掉到 60；
- 若检测线程处理不过来，`/fc01/vision/state` 的时间戳会重复（同一帧被重复
  发布），用 `ros2 topic hz` 只能看到发布率，不能代表有效新帧率。

**香橙派 Zero 3W（Allwinner H618，4×Cortex-A53）** 的具体建议：

- H618 没有可用的硬件 MJPEG 解码通路，OpenCV 走软件解码，四核 A53 的单核
  性能大约只有桌面核的三分之一到四分之一，**640×480@120 不现实**；
- 起步配置用 **320×240 @ 60 fps**（`frame_fps: 60`、`publish_rate_hz: 60`、
  `buffer_size: 4`）；CPU 有余量再试 640×480@30，或 320×240@90；
- USB 是 2.0：320×240@120 的 MJPEG 带宽没问题，640×480@120 已接近
  USB 2.0 等时传输的上限；
- 加散热片/风扇，H618 满载会降频；检查
  `cat /sys/class/thermal/thermal_zone0/temp`；
- 用 `sudo cpupower frequency-set -g performance`（或直接写
  `scaling_governor`）固定性能模式，避免按需调频导致控制周期抖动；
- 视觉和制导都要留余量：`top -H -p $(pgrep fc01_vision_node)` 看单线程占用，
  持续超过 70% 就应该降帧率或降分辨率；
- 1–2 GB 内存的版本建议 `colcon build --parallel-workers 2`，并优先用
  eMMC 而不是慢速 SD 卡。

**飞控接口**：本套件发布 `/visioncontrol` 和 `/mission/state`，并订阅
`/sim/platform_*`。如果飞控是 Pixhawk/ArduPilot 这类串口 MAVLink 设备，需要
一个桥接节点：

- `/visioncontrol` → MAVROS `setpoint_raw/local`，`FRAME_BODY_NED`，
  type_mask 打开 `vx/vy/vz + yaw_rate`、忽略位置/加速度/yaw；
- 飞控位姿/速度 → `/sim/platform_pose`、`/sim/platform_velocity`
  （MAVROS `local_position` 是 ENU/FLU，可直接用）；
- IMU 角速度是 FRD，转成 `/sim/platform_angular_velocity` 的 FLU 时要
  `[wx, -wy, -wz]`；
- 没有接触力传感器时 `/sim/target_contact_force` 发 0（顶住限力失效，但不影响
  正常顶住）。

**校准**：实机镜头的 `camera_fx/fy/cx/cy`、HSV 阈值、目标物理尺寸、
`camera_pos_*`、`target_x/y/z` 和 `target_face_yaw_deg` 都要按实际机架和目标
重新标定，不能直接沿用仿真的 10° 俯仰和 320×240 内参。

**安全**：`robot.launch.py` 默认 `control_enabled:=true`，上机前建议先
`control_enabled:=false` 只验证识别和平台状态，确认飞控侧
`/visioncontrol` 订阅是 depth 1 keep-last 再解锁。

## 参数

| launch 参数 | 默认 | 说明 |
| --- | --- | --- |
| `control_enabled` | `true` | 是否运行任务并下发指令 |
| `engage_mode` | `push` | `push` 持续顶；`impact` 一次撞；`track` 保持距离 |
| `control_debug_hz` | `0.0` | 制导调试日志频率（0 = 关闭） |
| `show_debug` | `false` | 打开 rqt_image_view 显示 `/fc01/vision/debug_image` |
| `publish_debug_image` | 跟随 `show_debug` | 是否发布标注图像 |
| `show_tuning_window` | `false` | 本次运行临时打开 OpenCV 滑条窗口 |
| `publish_debug_image` | 跟随 `show_debug` | 本次运行临时发布 debug 图像 |

可视化总开关在 `fc01_vision/config/vision.yaml`：

```yaml
# true = 打开 OpenCV 实时标注/滑条窗口，并发布 /fc01/vision/debug_image
visualization: false
```

它和 `show_tuning_window` / `publish_debug_image` 取“或”，所以无桌面的 ARM 板
保持 `false` 即可；临时调试用 launch 参数覆盖。

其余参数在 `fc01_vision/config/vision.yaml` 和
`fc01_mission/config/mission.yaml`，完整说明见各自的 README。
