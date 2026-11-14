# fc01_vision

USB 摄像头取图 → 传统 CV 颜色/形状目标检测 → 目标相对位置/速度估计 → 发布 `/fc01/vision/state`（`jikl_fc01_system/msg/VisionState`）。

`VisionState` 由 `src/jikl_fc01_system` 接口包提供（`VisionState` / `VisionHealth` /
`NavigationCommand`）。QoS 为 **BEST_EFFORT / VOLATILE / Depth 5**。

本节点只填它能估计的量：目标相对位置/速度（机体系 FRD）。姿态、角速度、质量
这几项没有估计，对应的 `valid_fields` 位保持清零；详见[字段映射](#字段映射)。

## 数据流

```
/dev/videoN ──V4L2/MJPG──► CameraSource（取流线程，只保留最新帧）
                                │
                                ▼
                        ColorDetector（HSV 阈值 + 轮廓 + 形状分类）
                                │
                                ▼
                     TargetEstimator（平面 PnP / 视直径测距）
                                │
                                ▼
                 VisionPipeline（alpha-beta 滤波、丢失滑行、协方差）
                                │
                                ▼
                 VisionStateAdapter（字段映射，唯一依赖 .msg 的文件）
                                │
                                ▼
                /fc01/vision/state  (BEST_EFFORT, VOLATILE, Depth 5)
```

`vision_core`（取流、检测、测距、滤波、调试绘制）本身不依赖 ROS，可单独构建和自测；
两个 ROS 节点都发布 `VisionState`，字段映射集中在
`vision_state_adapter.cpp` 一处。

## 目录

```
src/fc01_vision/
├── include/fc01_vision/       # types / camera_source / detector / estimator / pipeline / adapter / node
├── src/                       # 对应实现
├── tools/vision_demo.cpp      # 不依赖 ROS 的实时 demo
├── tools/vision_selftest.cpp  # 合成图像自测（检测 + PnP + 测距 + 丢失逻辑）
├── config/vision.yaml         # 节点参数
├── launch/vision.launch.py
└── package.xml, CMakeLists.txt
```

## 构建

```bash
source /opt/ros/humble/setup.bash
cd /home/han/target
colcon build --packages-select fc01_vision --cmake-args -DCMAKE_BUILD_TYPE=Release
source install/setup.bash
```

`jikl_fc01_system` 必须一起构建（`colcon build` 会自动按依赖顺序处理）：

```bash
colcon build --packages-select jikl_fc01_system fc01_vision fc01_mission fc01_bringup
```

仿真包 `fc01_vision_sim` 不在部署工作区，位于 `sim_ws/src/`，单独构建（先 source
上面的 `install/setup.bash` 作为 underlay）：

```bash
cd /home/han/target/sim_ws && colcon build --symlink-install
```

`fc01_vision_node` 从 USB 相机取图，`vision_image_node` 从 ROS 图像话题取图
（供 MuJoCo 仿真使用），两者都输出 `/fc01/vision/state`。

制导状态机在 `fc01_mission`（发布 `/visioncontrol`）。部署入口按场景分开：

- 实机：`ros2 launch fc01_bringup robot.launch.py`（本包的 `fc01_vision_node` + 制导）
- 仿真：先 source `/home/han/target/sim_ws/install/setup.bash`，
  再 `ros2 launch fc01_vision_sim vision_sim.launch.py`（MuJoCo + `vision_image_node` + 制导）

## 先跑自测（无需相机 / 无需消息包）

```bash
./build/fc01_vision/vision_core_selftest
```

覆盖：红色矩形检测、平面 PnP（1.5 m、右偏 0.2 m、下偏 0.15 m）、蓝色圆形视直径测距、
无物理尺寸时退化为方位角、目标丢失后的有效性超时。

## 实时 demo（无需消息包，便于调 HSV）

```bash
# 可视化
./build/fc01_vision/vision_demo --device 0 --target-width-m 0.20 --target-height-m 0.15

# 无界面跑 100 帧
./build/fc01_vision/vision_demo --headless --frames 100 \
  --target-width-m 0.20 --target-height-m 0.15

# 红色目标，自定义阈值（可重复 --hsv）
./build/fc01_vision/vision_demo --hsv 0,10,120,255,80,255 --hsv 170,180,120,255,80,255
```

输出示例：

```
[  120] seq=120 found=1 valid=1 range= 1.52 pos_frd=(  1.50,  0.20,  0.15) vel=( 0.03,-0.01, 0.00) pix=(  400,  300) planar PnP
```

`--save frame.png` 可保存第一帧带标注的图像，便于现场排查。

## 运行 ROS 节点

```bash
ros2 launch fc01_vision vision.launch.py
# 或指定参数文件
ros2 launch fc01_vision vision.launch.py config:=/home/han/my_vision.yaml

# 另外弹出一个窗口显示检测结果（轮廓/框/中心/距离/FRD 位置速度）
ros2 launch fc01_vision vision.launch.py show_debug:=true
```

`show_debug:=true` 等价于 `publish_debug_image:=true` 加
`ros2 run rqt_image_view rqt_image_view /fc01/vision/debug_image`；
该图像以 RELIABLE QoS 发布，rqt_image_view 和 rviz2 都能直接订阅。

可视化总开关在配置里：

```yaml
visualization: true   # OpenCV 实时标注/滑条窗口 + 发布 debug 图像
```

节点把它和 `show_tuning_window`、`publish_debug_image` 取“或”，所以单独用
launch 参数覆盖也行。无桌面的 ARM 板保持 `false`。

检查：

```bash
ros2 topic info /fc01/vision/state -v
ros2 topic echo /fc01/vision/state
ros2 topic hz /fc01/vision/state
```

`ros2 topic info -v` 中应看到 Reliability: BEST_EFFORT、Durability: VOLATILE、Depth: 5。

## 字段映射

消息定义在 `src/jikl_fc01_system/msg/VisionState.msg`，映射**只集中在**
`src/fc01_vision/src/vision_state_adapter.cpp` 的 `fillVisionState()`。
两个节点共用同一个 adapter，输出不会各写一套。

| 字段 | 本节点写入 |
|---|---|
| `schema_version` | `1` |
| `sequence` | 管线帧序号 |
| `stamp` | 图像采集时刻（不是发布时刻） |
| `frame_id` | `body_frd`（position/velocity 所在坐标系） |
| `body_frame_id` | `body_frd` |
| `source_id` | `fc01_vision`（直连相机）/ `fc01_vision_image`（ROS 图像） |
| `initialized` | 收到过至少一帧 |
| `tracking` | `detected && position_valid` |
| `calibration_valid` | 内参有效 |
| `valid_fields` | 有效时置 `POSITION \| VELOCITY \| POSE_COVARIANCE \| TWIST_COVARIANCE`（=51） |
| `position[3]` | 目标相对位置，机体系 FRD，m |
| `velocity[3]` | alpha-beta 滤波速度，FRD，m/s |
| `attitude[4]` | 单位四元数 `[w=1,x=0,y=0,z=0]`，**ATTITUDE 位不置位** |
| `angular_velocity[3]` | 0，**ANGULAR_VELOCITY 位不置位** |
| `pose_covariance[36]` | 行主序 6×6，只填线性位置对角块 |
| `twist_covariance[36]` | 行主序 6×6，只填线性速度对角块 |
| `quality` | 0，**QUALITY 位不置位**（没有标定过的质量指标） |

有意不置位的字段表示“未知”，而不是“值为 0 且可信”。消费方必须先检查
`valid_fields` 再使用对应数组。

## 坐标系与字段语义

- **position / velocity：机体系 FRD**（x 前、y 右、z 下），单位 m、m/s。
  相机光学系到 FRD 的转换为 `(x_frd, y_frd, z_frd) = (z_opt, x_opt, y_opt)`。
- **attitude**：本节点不做姿态估计。消息契约里的姿态是“机体 FRD → NED”的
  Hamilton `[w,x,y,z]`，需要机体姿态的消费方应结合飞控姿态使用。
- **角度**：`TargetState::yaw` 为目标方位角 `atan2(y_frd, x_frd)`，右偏为正，单位 rad。
- **有效位**：仅当「当前帧检测到目标」且「三维位置有效」且「图像时间戳不超过
  `stale_timeout_s`」时 `POSITION`/`VELOCITY` 置位。相机断流后节点仍按
  `publish_rate_hz` 发布，但 `valid_fields=0`，避免控制器继续使用陈旧目标。
- **协方差**：只填 6×6 的线性对角块 `[x, y, z, ·, ·, ·]`；无效时用
  `invalid_position_std_m` / `invalid_velocity_std_mps` 填大值，但对应的
  covariance 位不置位。

## 参数说明

| 参数 | 默认 | 说明 |
|---|---|---|
| `device_index` | 0 | `/dev/videoN`（本机外接相机为 2） |
| `frame_width/height/fps` | 640/480/120 | 采集请求值；本机外接相机在 640x480 下支持 30/60/120 fps |
| `use_mjpg` | true | USB 摄像头高帧率通常需要 MJPG |
| `buffer_size` | 4 | V4L2 缓冲数；buffer=1 时该相机 120 fps 会掉到 60 fps |
| `flip_horizontal` | false | 镜头倒装/镜像时置 true |
| `camera_fx/fy/cx/cy` | 466.7/320/240 | 内参（2.8 mm 镜头 + 1/4" 30 万像素模组）；fx=0 时用 `camera_hfov_deg` 估算 |
| `hsv_ranges` | 红色两段 | `h0,h1,s0,s1,v0,v1`，可多条 |
| `blur_kernel` / `morph_kernel` | 5 / 5 | 偶数自动 +1，<3 关闭 |
| `min_area_ratio` / `max_area_ratio` | 0.002 / 0.5 | 占全图面积比例 |
| `target_shape` | auto | `auto` / `rect` / `circle` |
| `circle_min_circularity` | 0.85 | 判为圆形所需的最小圆度 |
| `reject_border_touch` | true | 丢弃贴边（被画面裁掉）的色块，避免测距严重偏大 |
| `border_margin_px` | 2 | 贴边判定的像素余量 |
| `target_width_m` / `target_height_m` | 0 / 0 | 矩形物理尺寸，用于 PnP |
| `target_diameter_m` | 0 | 圆形物理直径 |
| `use_pnp` | true | false 时只用视宽测距 |
| `position_alpha` / `velocity_beta` | 0.5 / 0.1 | alpha-beta 滤波系数 |
| `stale_timeout_s` | 0.5 | 丢失/断流后保持 valid 的时间 |
| `publish_rate_hz` | 120 | 固定频率发布，与检测帧率解耦；低帧率时相应调低 |
| `detect_every_n` | 1 | 每 N 帧检测一次，降低板端负载 |
| `state_topic` | `/fc01/vision/state` | VisionState 输出话题 |
| `frame_id` | `body_frd` | position/velocity 所在坐标系 |
| `source_id` | `fc01_vision` | VisionState 来源标识 |
| `body_frame_id` | `body_frd` | VisionState 机体坐标系名 |
| `visualization` | false | 总开关：打开预览/滑条窗口并发布标注图像（与下面两项取“或”） |
| `show_tuning_window` | false | 打开 OpenCV 预览 + 滑条窗口 |
| `publish_debug_image` | false | 发布带标注图像 |

## 标定与调参

### 1. 相机内参

单目方案下位置精度高度依赖内参。本机相机是 2.8 mm 镜头、30 万像素
（640×480）。`config/vision.yaml` 按最常见的 1/4 英寸、6 µm 像元模组
（OV7725 一类）给出 `fx=fy≈466.7`（水平视场约 68.9°）。若实际模组的像元
尺寸不同，`fx` 会按比例变化；快速核对办法：

1. 把目标球放在量好的距离 `D_true`（例如 2.00 m）正前方；
2. `ros2 topic echo /fc01/vision/state` 看 `position[0]` 给出的 `D_est`；
3. 按 `camera_fx_new = camera_fx × D_true / D_est` 修正后重启节点
   （测距与 `fx` 成正比：报远了说明 `fx` 配大了）。

正式飞行前仍建议用 ROS 标定板标定：

```bash
ros2 run camera_calibration cameracalibrator \
  --size 8x6 --square 0.025 image:=/image_raw camera:=/camera
```

把得到的 `fx, fy, cx, cy` 填入 `camera_fx/fy/cx/cy`。

### 2. HSV 阈值

```bash
./build/fc01_vision/vision_demo --headless --save /tmp/frame.png
```

用 GIMP/画图取目标像素的 HSV，或直接运行带界面的 demo 观察右下角 mask 缩略图。
红色跨 0° 需要两段（`0-10` 和 `170-180`）。现场光照变化大时优先调 `s_min`/`v_min`。

### 3. 目标尺寸

`target_width_m/target_height_m`（矩形）或 `target_diameter_m`（圆）必须与实际目标一致。
尺寸填 0 时节点仍会检测并给出方位角，但 `position_valid=false`，不会输出可用位置。

## 已知限制与飞行安全

- 单目测距依赖目标物理尺寸和朝向；目标倾斜、遮挡、反光会带来明显误差。
- 传统颜色检测对光照、背景同色物体敏感，仅适合作为第一版链路验证和
  受控场景；后续可将 `ColorDetector` 替换为 YOLO/ONNX 检测器，
  保持 `Detection` 接口不变即可。
- 未做相机-机体外参标定，默认假设相机光轴与机体 FRD 的 x 轴重合。
  实际安装有俯仰/偏航偏差时，需在 `TargetEstimator::opticalToFrd()` 前加旋转矩阵。
- 未融合飞控姿态，输出不是 NED 绝对位置；控制器侧需自行完成机体系到 NED 的转换。
- 速度由位置差分 + alpha-beta 得到，不是直接测量量；首次检测时速度为 0。
