# fc01_vision_sim

MuJoCo 视觉闭环仿真（飞控 + 场景侧）：在 RMUC2027 场地上放一架「撞击无人机」，
飞机从地图中心 ROBOMASTER 装置上那块「黑底、红圈、白色 H」的标牌上方起飞，
用机载 FPV 相机识别东侧 ROBOMASTER 基地头部的绿色指示灯 (0.315, -4.958, 1.373)，
然后**用机头前脸**持续顶住它（不是撞一下就跑）。

本包是**仿真部署层**：物理、相机、平台状态，外加仿真专用的视觉参数
（`config/vision_image.yaml`）。制导/巡航状态机在 **`fc01_mission`** 里，
视觉识别代码在 **`fc01_vision`** 里。`fc01_mission` 发布的
`jikl_fc01_system/VelocityCommand`（机体系 FRD）通过 `/visioncontrol` 回到本包，
本包像真实飞控一样执行它（速度环 → 姿态环 → 四旋翼混控）。一次启动仍然只需
`ros2 launch fc01_vision_sim vision_sim.launch.py`——本包的 launch 会启动
MuJoCo + `vision_image_node`，并 include `fc01_mission` 的 launch。
实机部署走另一套：`ros2 launch fc01_bringup robot.launch.py`。

**不再放球**：目标就是地图自带的绿灯（约 5.7 × 5.5 cm）。灯是 CAD 视觉网格、不能
碰撞，所以同位置放了一块**隐形**碰撞灯板（`target_visible: false`，完全透明但仍参与
碰撞）作为接触代理，接触力仍是真实的 `mj_contactForce`。灯板是竖直薄板，法向水平，
冲撞时不会给机身带来抬头/低头力矩。

三种模式（`engage_mode`，由 `fc01_mission` 实现）：

- **`push`（默认）**：视觉锁定后先以 `strike_speed`（2.0 m/s）**直冲**灯板，撞上的
  瞬间由反向阻尼吸收冲量，随后以 0.3 m/s 的恒定低速顶住并悬停：速度环被
  固定目标挡住，指令速度全部变成**持续的接触力**（约 0.6 N），机身只前倾约 10°，
  整个机头前脸平贴在灯上；顶住 3 s（`push_hold_s`）后自动倒飞撤出 1 m，切到
  `hold` 稳态悬停，不再重复冲撞。`/sim/impact` 在整个顶住期间保持 `true`。
- **`impact`**：一次撞击。接近到 2.2 m 内进入末制导，以 5 m/s 冲撞；接触后电机停转、
  飞机坠落。
- **`track`**：保持在目标前方 `standoff_m` 处跟踪。

飞机外观和碰撞都使用 `撞击无人机.STL`：外观是压缩到 15 万面的 OBJ，碰撞是凸包
（MuJoCo 单个 mesh 上限 20 万面，原始 42 万面加载会直接报错），按真机 1:1
（约 11.9 × 11.9 × 7.3 cm、240 g）使用。

## 数据流

三个包分工：`fc01_vision` 只做识别，`fc01_mission` 只做制导/巡航，
`fc01_vision_sim` 只做物理与相机。

```
MuJoCo 场景（RMUC2027 地图 + 四旋翼刚体 + 绿灯处的隐形碰撞灯板）
        │  离屏渲染 FPV 相机
        ▼
/sim/camera/image_raw (sensor_msgs/Image, rgb8, BEST_EFFORT)
/sim/camera/camera_info
        │
        ▼
fc01_vision 的 vision_image_node
        │  检测 + 单目测距 + alpha-beta 滤波
        ▼
/fc01/vision/state          (jikl_fc01_system/VisionState, 主输出)
/fc01/vision/target_relative (geometry_msgs/PointStamped, FRD, m，兼容输出)
/fc01/vision/target_valid    (std_msgs/Bool)
        │
        ▼
fc01_mission 的 mission_node（起飞 → 巡航 → 冲击 → 顶住 → 撤出 → 悬停）
        │  平台状态从 /sim/platform_pose、/sim/platform_velocity、
        │  /sim/platform_angular_velocity 读入，按相机安装偏移做时延补偿
        │  接触力从 /sim/target_contact_force 读入
        ▼
/visioncontrol   (jikl_fc01_system/VelocityCommand, 机体系 FRD, 50 Hz)
               （vx/vy/vz 速度 + wz 偏航角速度；没有独立的航向角话题）
/navigation_command (jikl_fc01_system/NavigationCommand, 10 Hz, 锁定前航点)
/mission/state   (std_msgs/String, 10 Hz, 状态机当前阶段)
        │
        ▼
fc01_vision_sim 的 vision_sim（飞控侧）
   收到 /visioncontrol 后按收讯时刻姿态把机体系 FRD 换算成世界系速度并冻结，
   直到下一条命令；速度环 → 姿态 PD → 四旋翼推力混控
        │
        ▼
MuJoCo 刚体积分（重力、接触、坠落），闭环
```

`vision_image_node` 同时发布 `jikl_fc01_system/VisionState`（主输出）和
`target_relative`（兼容输出）。默认任务用 `target_relative` 闭环；加
`use_vision_state:=true` 改为消费 `/fc01/vision/state`，且只认
`valid_fields` 中的 `POSITION` 位。

`/visioncontrol` 是制导节点对飞控的唯一控制输出：把制导算出的世界系速度转到机体系
FRD（x 前、y 右、z 下）后按 `vision_control_hz` 发布，带序号、时间戳、复位计数和
`valid` 位。仿真订阅它，**不再自己跑制导**——和真机接法一致。命令按收讯时刻的
姿态换算一次世界系速度并保持到下一条命令（避免用命令之后才变化的姿态去反解，
那会和外环形成耦合）；`command_timeout_s` 内没有新命令就悬停（零速度）。

航向只通过 `VelocityCommand.wz` 下发：任务节点用平台姿态自己闭环航向误差，
输出机体偏航角速度；仿真姿态环把 `wz`（FRD，z 向下）取反后作为 FLU 目标角速度，
偏航阻尼作用在 `omega - omega_cmd` 上，推力方向对应的目标姿态不约束航向。

同一台机器上 `/visioncontrol` 的订阅用 **depth 1 keep-last**：它是设定值而不是
数据流，队列一深（如默认 10）就会让飞控执行几百毫秒前的命令，曾在外环上激起
±40° 的俯仰振荡。

## 依赖

- ROS 2 Humble（`rclpy`、`sensor_msgs`、`geometry_msgs`、`std_msgs`、`launch_ros`）
- Python 3 `numpy`
- MuJoCo（pip 安装）：

```bash
python3 -m pip install --user mujoco
```

- 已构建的 `fc01_vision`（提供 `vision_image_node`）、`fc01_mission`（制导节点）和
  `jikl_fc01_system`（消息包）——这些在部署工作区 `/home/han/target` 里，作为本
  仿真工作区的 underlay。

## 构建与运行

仿真单独放在 `/home/han/target/sim_ws`，部署工作区 `src/` 里不再包含仿真包。
先构建并 source 部署工作区，再构建本工作区：

```bash
source /opt/ros/humble/setup.bash
cd /home/han/target
colcon build --symlink-install --packages-select \
  jikl_fc01_system fc01_vision fc01_mission fc01_bringup
source install/setup.bash

cd /home/han/target/sim_ws
colcon build --symlink-install
source install/setup.bash
```

地图资源 `RMUC2027/` 也放在 `sim_ws/` 根目录，`map_xml` 的相对路径按本工作区
根目录解析。

```bash
# Viewer 窗口 + 持续顶绿灯（默认 push），同时弹出 OpenCV 调参滑条窗口
ros2 launch fc01_vision_sim vision_sim.launch.py

# 无窗口，适合远程/CI
ros2 launch fc01_vision_sim vision_sim.launch.py headless:=true

# 不要滑条窗口
ros2 launch fc01_vision_sim vision_sim.launch.py show_tuning_window:=false

# 一次撞击（接触后收油坠落）
ros2 launch fc01_vision_sim vision_sim.launch.py engage_mode:=impact

# 不撞，保持 3 m 跟踪
ros2 launch fc01_vision_sim vision_sim.launch.py engage_mode:=track

# 改用 /fc01/vision/state（VisionState）作为闭环输入
ros2 launch fc01_vision_sim vision_sim.launch.py use_vision_state:=true

# 第三人称视角看平台和绿灯（不显示相机画面）
ros2 launch fc01_vision_sim vision_sim.launch.py viewer_camera:=free

# 额外弹出一个窗口显示带检测框的图像
ros2 launch fc01_vision_sim vision_sim.launch.py show_debug:=true

# 调参时按 20 Hz 打印控制量/视觉估计/估计误差
ros2 launch fc01_vision_sim vision_sim.launch.py control_debug_hz:=20.0

# 只看视觉、不闭环
ros2 launch fc01_vision_sim vision_sim.launch.py headless:=true control_enabled:=false
```

另开终端检查：

```bash
ros2 topic hz /sim/camera/image_raw
ros2 topic hz /visioncontrol
ros2 topic echo /visioncontrol --once
ros2 topic echo /sim/impact --once
ros2 run rqt_image_view rqt_image_view /fc01/vision/debug_image
```

正常现象（默认 `push`）：日志先出现

```
takeoff complete: z=2.75 m, hover 0.80 s before the chase
takeoff hover done: seeking at up to 4.00 m/s
target locked: range=2.60 m -> strike at 2.00 m/s
strike contact: range=0.09 m, speed=2.00 m/s -> hold/push at 0.30 m/s
push hold done: 3.0 s pressed -> retreat 1.00 m at 0.80 m/s
retreat complete: holding 0.98 m off the light at (-0.67, -4.91, 1.36) m
```

按 4 m/s 巡航时，从起飞到顶住只要约 6 s（旧版 0.9 m/s 要 13 s 以上）。随后飞机
以 0.3 m/s 顶住绿灯 3 s，日志稳定在

```
frames=330 state=push platform=(0.23, -4.96, 1.39) rpy=(0, 9, 0)deg vel=(0.00, 0.00, 0.00) thrust=2.4N ...
ctrl state=push v_cmd=(0.30, 0.00, 0.00) ... push_range=0.08m force=0.6N
```

即：位置不再变化、速度为零、姿态稳定（只剩前倾），`force` 是持续的接触力，
`/sim/impact` 为 `true`。3 s 后自动倒飞撤出并悬停：

```
frames=388 state=hold platform=(-0.67, -4.91, 1.35) rpy=(0, 0, 0)deg vel=(0.00, 0.00, 0.00) thrust=2.3N ...
```

接触后灯已经贴到镜头（机头相机比机壳还靠前 8 cm），视觉节点会报
`detected=0 ... stale`——这是正常的，`push` 此时用交接时冻结的瞄准点，不再依赖
近距测量。

## 场景

- 地图：`<include file="RMUC2027/scene_rmuc.xml"/>`，包含场地地形、矮墙和装饰。
  场地范围约 `x∈[-25, 3]`、`y∈[-13, 3]`。
- 起飞点：地图中心 ROBOMASTER 装置上那块**黑底、一圈红线、正中白色 H** 的标牌，
  牌面朝上，位于 `(-10.15, -3.93)`、高 1.731 m。这是整张地图上唯一真正的字母 H
  （其余白色标记只有 ROBOMASTER 2027 字样、扳手/禁止通行图标和标线）。飞机悬停在
  牌面上方 `platform_start_z: 1.775`（牌面 + 机壳半高 + 约 1 cm 余隙），机头朝东
  偏南 `platform_yaw_deg: -5.6`，正对 10.5 m 外的绿灯。标牌本身是 CAD 视觉网格
  （不参与碰撞），所以离牌 0.4 m 内保持起飞高度、再平滑降到巡航高度，不会从
  牌面中间穿下去。`landing_pad: false`——不再额外画假的 H 标。
- 起飞是**两段式**的，而且竖直、水平严格分开（起飞/巡航参数在
  `fc01_mission/config/mission.yaml`）：先以 `takeoff_climb_mps` 原地
  竖直爬升 **1 m**（`takeoff_altitude_m: 2.78`，牌面 1.731 + 机体 1.775 起算），
  这一段水平速度指令恒为 0、x/y 一格不动；到高度后原地悬停 `takeoff_hover_s`
  （默认 0.8 s），最后才进入巡航、边前飞边下降到 `push_altitude_m`。
  悬停这一步是为了“丝滑”：以前一到高度就把 4 m/s 的巡航指令丢给还停在
  0.1 m/s 的飞机，速度环一个控制周期就要求 35° 满倾角，机头猛地压下、高度
  先掉 0.25 m、航向左右摆，看起来像被甩出去。
- 进入巡航后，水平速度用 `seek_ramp_s`（默认 1.2 s）的 smoothstep 从 0 渐入到
  `search_speed`：峰值加速度 `1.5·V/T ≈ 5 m/s²`（约 27° 倾角），两端加速度
  都是零，没有“一条指令跳到满倾角”的顿挫。实测速度 0 → 0.45 → 1.24 → 2.34 →
  3.32 → 4.15 m/s，不再出现过冲和侧向摆动。
- 从 2.78 m 飞向 1.35 m 的冲撞高度时，巡航段允许 `cruise_descent_mps`
  （默认 1.4 m/s）的下降率，高度环增益 2.5（时间常数 0.4 s）、速度剖面在
  `d − (0.3…0.8)` 区间收平：飞机在视觉锁定前就已经**平飞**在冲撞高度上。
  以前下降率 0.9、增益 1.5，1.4 m 的下降在最后 20 cm 变成指数尾巴，锁定瞬间
  还高 0.2 m，冲撞是从高处斜着砸下来的——机头的下前棱角正好挂在基地头部
  顶边的上沿，看起来就是“用角顶”，随后被挑得仰起 18°。
- 从 H 牌到灯约 10.5 m，5.7 cm 的灯在 10 m 外不到 1 px，视觉要到约 2 m 才能
  锁定。锁定前 `seek` 按灯的地图坐标**盲飞巡航**（`search_speed: 4.0 m/s`），
  速度剖面 `v = 1.0·(d − 1.4)`：4 m/s 从 d≈5.4 m 开始收速，2.6 m 处约 1.2 m/s，
  正好接上视觉接近段的 1.5 m/s。减速时 `dv/dt = −v`（4 m/s 时约 4 m/s²、22°
  机头上仰），灯仍在 35° 半视场内，不会因为急刹丢目标。一出现检测立即切回
  视觉闭环。这条航线上没有任何高于 0.5 m 的结构，巡航高度 1.35 m 全程无遮挡
  （用射线扫过整条航线确认）。
- 目标：地图自带的绿色指示灯，位于东侧 ROBOMASTER 基地头部
  `(0.315, -4.958, 1.373)`，灯面朝 -x（西），约 5.7 × 5.5 cm。它是 CAD 视觉网格
  （`contype=0`），本身不能碰撞，因此用一块**隐形竖直面板**（24 cm 宽 × 40 cm 高
  × 8 cm 厚，`target_visible: false`，rgba 全 0）做接触代理，`target_motion:
  static`。接触参数做了软化（`solref="0.05 1"`, `solimp="0.9 0.99 0.001"`），
  高速接触也会被柔和吸收。面板要 8 cm 厚：2 m/s 的冲撞会陷进软接触约 1 cm，
  1 cm 薄板会被机头“跨”过去甚至整个穿过去（实测飞机卡在板后面）。
  - 为什么是平板不是球：3 cm 的球在机身高度附近只是一小团，飞机贴上去时腹部会
    骑到球的上半部，接触法向朝上，于是机身慢慢爬高、俯仰角从 10° 一路涨到 34°，
    最后翻掉。平板模仿灯实际所在的竖直墙面，法向始终水平。
  - 为什么面板比灯大得多：面板比 12 cm 宽的机身宽，冲撞偏几厘米也还在正面上，
    不会擦到侧边；面板顶边（1.573 m）比撞后可能弹起的高度还高，飞机不会爬上去
    停住。面板完全不可见，只参与碰撞。
- 机头另有一块**隐形碰撞垫**（6 × 6 cm，比凸包前缘再凸出 8.6 mm，`rgba=0`）：
  机身凸包是 157 面的不规则形状，直接顶灯时接触点会落在任意一点上，产生的力矩
  会让 240 g 的机身左右摇摆；平整的机头垫让灯板的接触力水平地穿过质心。它同样
  只参与碰撞，查看器和相机里都看不到。
- **机头垫与灯板单独用一个接触组**（`contype=conaffinity=4`），只和灯板碰撞、
  不和地图碰撞。原因是地图的碰撞体和可见模型对不上：灯附近是一堵近垂直的碰撞
  坡面，西沿在 `x≈0.309 m`，只比灯板前沿靠后几毫米。机头垫若同时和地图碰撞，
  冲撞时下前棱就会啃到这堵坡的上沿，被 ~100 N 的力往上掀（法向几乎竖直），
  弹起后挂在头顶边缘、俯仰 18°——这就是之前看到的“用角顶”。机壳凸包仍是
  1/1，撞到地图时照常参与碰撞；只有机头这块隐形垫改走 4/4。
- 四旋翼：`platform` 刚体 + `freejoint`，质量 0.24 kg，转动惯量
  `diag(4e-4, 4e-4, 6e-4) kg·m²`；X 型四旋翼，臂长 0.04 m，旋翼位置
  `(±0.04, ±0.04, 0.01)`。按真机 1:1 建模：2.5 寸穿越机，约 11.9 × 11.9 ×
  7.3 cm，机壳半高 3.65 cm。
  - 外观 `impact_drone_lod.obj`（15 万面），碰撞 `impact_drone_hull.obj`
    （310 面凸包），两者都由 `tools/make_hull.py` / `tools/decimate_stl.py` 从
    `撞击无人机.STL` 生成，可复现。
  - 动力学：制导给出期望加速度 → 期望推力方向（倾角按 `max_tilt_deg` 限制）→
    期望姿态（偏航对准目标）→ 姿态 PD 力矩 → 混控矩阵分配到四个旋翼 →
    一阶电机滞后（`motor_tau`）→ `mj_applyFT`。
  - 旋翼推力上限 2.5 N/个（整机推重比约 4.2）；`velocity_tau` 是速度环时间常数，
    必须明显慢于姿态环（默认 0.12 s 对 16.1 rad/s，约 4 倍分离）。姿态环
    `attitude_gain=260` / `attitude_damping=22`，2.6 Hz、阻尼比 0.68，倾斜和
    改平都在 0.2 s 内完成，这是“一压机头就走”的手感来源。
- 相机：机头 `(0.08, 0, 0.015)` 处安装（机壳体 +x 面附近），**上仰 10°**（`camera_pitch_deg=10`，
  视觉节点必须用同一个值），`fovy=70°`（4:3 下水平约 86°），ROS 图像 320×240；
  `CameraInfo` 由仿真直接给出。上仰让飞机顶灯前倾时灯仍落在垂直半视场 35° 内。
  - 灯只有 5.7 cm，2 m 外只有约 5 px（320×240），10 m 外不到 1 px（所以先盲飞），
    因此 `morph_kernel` 用 3、
    `min_area_ratio` 0.0001、`min_width/height_px` 3；OpenCV 滑条可以直接再调。
  - 视觉估计带时延补偿：测量值是**成像时刻**机体系下的向量，收到消息时飞机已经
    又转/移了一段。仿真用消息时间戳算延迟（上限 0.15 s），按 `-ω·age` 做小角度
    旋转、相机原点按 `-v·age` 后移，再变换到世界系。

> 320×240 是刻意选择：640×480 的单帧约 0.9 MB，本机默认 Fast DDS UDP 缓冲下
> best-effort 图像会大量丢帧（实测降到 2~4 Hz）；320×240（约 230 kB）可稳定 30 Hz。
> MuJoCo Viewer 窗口本身仍是全分辨率渲染，不受影响。

## 视觉锁定后的冲撞（strike）

`seek` 巡航到约 2.6 m 时视觉锁定绿灯，此时不再按“速度 ∝ 距离”慢慢蹭，而是进入
`strike`：锁定瞬间把瞄准点冻结为灯的**地图精确坐标**（5.7 cm 的灯在 2.6 m 处只有
几像素，冲撞时机头前倾又容易把它甩出画面，所以这一段不依赖视觉持续可见），机头
固定朝 `target_face_yaw_deg`（0°，正对灯面），以恒定 `strike_speed`（2.0 m/s）直线
冲过去。距离 0.10 m 时交接给 `push`，并进入 `strike_settle_s`（0.25 s）的吸收段：
这 0.25 s 里不朝目标顶，而是按 `-2·v` 反向阻尼（上限 `strike_settle_brake_mps`）把
冲量和回弹吃掉；之后才以 0.3 m/s 顶住并悬停。撞完的姿态收敛到约 (0, 8, 0)°。

三个关键点，缺一个都会翻：

- **机头正对灯面**：冲撞段若按“飞机到灯的方位角”转机头，距离只剩 0.1 m 时最后
  几厘米的横向偏差会把航向带偏 7–10°，斜着撞平板会产生侧向/偏航冲量，足以把
  240 g 机身转翻。
- **吸收段主动反向阻尼**：撞上的瞬间若还继续给前进推力，电机会持续往接触里泵
  能量，2 m/s 的冲撞会反弹 1–2 m，接着从侧面二次接近而跑偏或翻掉。
- **平板够大够厚**：24 cm 宽、40 cm 高、8 cm 厚（见场景一节），撞偏几厘米也还在
  正面；面板顶边足够高，撞后不会被弹到板顶上停住；厚度保证 2 m/s 的机头不会
  穿过去。
- **机头垫只撞灯板**：机头垫用独立接触组（4/4），不再和地图的隐形碰撞坡面接触，
  避免下前棱被坡沿挑起来（详见场景一节）。

2.0 m/s 连续 5 次都稳稳顶住；2.5 m/s 偶尔还是会反弹 1.8 m 后跑偏。
`strike_speed: 0` 可关闭冲撞，回到位置环接近。

### 顶 3 s → 稳定撤出 → 悬停

顶住不是永久的：从撞上（进入 `push`）开始计时，`push_hold_s`（默认 3.0 s）后进入
`retreat`，沿**飞来的方向**直线后退（机头仍朝灯，像四旋翼的“倒飞”），退到离灯
`retreat_distance_m`（1.0 m）处切到 `hold`，稳态悬停，不再重复冲撞。

撤退速度 `retreat_speed`（0.8 m/s）用 smoothstep 渐入（`retreat_ramp_s` 0.5 s），
最后 25 cm 线性刹车：速度环约 0.15 m 的滞后被这段刹车吃掉，不会冲过停止点。
速度指令 0 → 0.84 → 0.81 → 0.42 → 0，实测停在离灯 0.98 m 处，姿态归零
（rpy 0°），速度 0。`push_hold_s <= 0` 关闭撤出，一直顶住。

## 持续冲击（push）是怎么实现的

1. **接近**：`seek` 阶段按位置误差飞向灯，并把高度保持在 `push_altitude_m`
   （1.35 m）。灯心在 1.373 m，但灯上方约 2 cm 就是基地头部顶面（1.394 m）；
   按 1.373 m 顶过（2026-11-13 复测）：机壳顶面 1.4095 m 高过头部顶面，冲撞时
   被挑到顶面上——飞机升到 1.44 m、俯仰 18°，是拿底下的棱角骑在头部边缘上。
   1.35 m 时机壳顶面 1.3865 m，整个机身都在头部顶面以下；配合巡航段提前降到
   这个高度（见“起飞”一节），冲撞是平飞贴上去的，不会从高处掉下来用下前角
   挂住头部上边缘。接触发生时高度环会把机体托在 1.36–1.37 m，正好是灯心，
   前脸中心对着灯。
2. **交接**：冲撞段在 0.10 m 处切到 `push`（关闭冲撞时则在 1.2 m 处切入），并
   **冻结**瞄准点。静止目标（RMUC 的绿灯）直接用灯在地图上的精确坐标；视觉在
   1.2 m 处的估计误差有 5–8 cm，冻结这个估计会让飞机停在灯前 6 cm 处，然后朝
   残余横向误差方向滑出去（实测偏航从 -6° 甩到 -90°，飞机侧翻）。只有移动目标
   才用视觉估计做瞄准点。
3. **顶住**：朝瞄准点以恒定 `push_speed`（0.3 m/s）给速度指令，高度环保持
   `push_altitude_m`，**机头方向保持交接时刻的朝向**（不再每步重新瞄准：距离
   只剩 0.1 m 时 2 cm 的横向偏差会变成 15–20° 的偏航指令，机身会在灯上缓缓自转）。
   速度环时间常数 0.12 s，稳态接触力约 `m·v_cmd/velocity_tau ≈ 0.6 N`，机身
   前倾约 10°，整个机头前脸还是贴在灯上（面撞面，不是机头尖角先触）；
   接触力超过 `push_max_force_n` 时按比例缩小速度指令，防止把机身顶翻。
4. **退出**：顶住 `push_hold_s`（3 s）后转 `retreat` 主动倒飞撤出 1 m，再切 `hold`
   稳态悬停。只有还没到撤出时间、飞机相对冻结瞄准点被弹开超过 `push_release_m`
   （1.8 m）时，才退回 `seek`。误判释放后，如果视觉也丢了，会回到工作高度并慢慢
   扫视重新捕获。

## 调参窗口（OpenCV 滑条）

`show_tuning_window:=true`（默认）时，`vision_image_node` 打开一个
`fc01 vision tuning` 窗口：上半部分是 2 倍放大的检测图像，下半部分是滑条。
拖动滑条立即重新检测（每帧轮询，无回调），不需要重启：

| 滑条 | 对应参数 |
| --- | --- |
| `H min/max`、`S min/max`、`V min/max` | `hsv_ranges`（H 0–180，OpenCV 标度） |
| `blur (odd)`、`morph (odd)` | `blur_kernel`、`morph_kernel` |
| `min area/1000`、`max area %` | `min_area_ratio`、`max_area_ratio` |
| `min width px`、`min height px` | `min_width_px`、`min_height_px` |
| `circle min %` | `circle_min_circularity` |
| `target dia cm` | `target_diameter_m`（单目测距用） |
| `reject border` | `reject_border_touch` |
| `shape 0auto 1rect 2circle` | `target_shape` |

滑条只在本次运行有效，不会写回 yaml；调好后把数值抄进
`config/vision_image.yaml`。窗口需要桌面环境（`DISPLAY`）；launch 会自动清掉
snap 版 VS Code 泄漏的 GTK/GIO 环境变量，否则 GTK 窗口会因
`libpthread ... GLIBC_PRIVATE` 直接崩溃。

## 话题

| 话题 | 类型 | 方向 / QoS | 说明 |
| --- | --- | --- | --- |
| `/sim/camera/image_raw` | `sensor_msgs/Image` | 发布, BEST_EFFORT, VOLATILE, 5 | 仿真 FPV 图像（rgb8） |
| `/sim/camera/camera_info` | `sensor_msgs/CameraInfo` | 发布, BEST_EFFORT, VOLATILE, 5 | 内参，无畸变 |
| `/fc01/vision/target_relative` | `geometry_msgs/PointStamped` | 发布（`fc01_vision`）, BEST_EFFORT, VOLATILE, 5 | 兼容输出 / 默认闭环输入：目标 FRD 相对位置，无效时 NaN |
| `/fc01/vision/target_valid` | `std_msgs/Bool` | 发布（`fc01_vision`）, BEST_EFFORT, VOLATILE, 5 | 兼容输出：有效性 |
| `/fc01/vision/state` | `jikl_fc01_system/VisionState` | 发布（`fc01_vision`）, BEST_EFFORT, VOLATILE, 5 | 主输出；`use_vision_state=true` 时任务节点用它闭环 |
| `/fc01/vision/debug_image` | `sensor_msgs/Image` | 发布（`fc01_vision`）, RELIABLE, VOLATILE, 5 | 带检测框/中心的图像（bgr8） |
| `/visioncontrol` | `jikl_fc01_system/VelocityCommand` | 发布（`fc01_mission`）→ 订阅（本包）, depth 1 keep-last | 机体系 FRD 速度指令，`valid` 表示本帧可用，50 Hz |
| `/navigation_command` | `jikl_fc01_system/NavigationCommand` | 发布（`fc01_mission`）, 默认 | 视觉锁定前的航点指令（`CRUISE`），锁定后 `valid=false`；本仿真不消费（飞控侧接口） |
| `/mission/state` | `std_msgs/String` | 发布（`fc01_mission`）, 默认 | 状态机当前阶段（`takeoff`/`seek`/`strike`/`push`/`retreat`/`hold`），10 Hz |
| `/sim/platform_pose` | `geometry_msgs/PoseStamped` | 发布, 默认 | 平台真值（世界系，四元数 wxyz，机体系 FLU） |
| `/sim/platform_velocity` | `geometry_msgs/Vector3Stamped` | 发布, 默认 | 平台线速度（世界系 m/s） |
| `/sim/platform_angular_velocity` | `geometry_msgs/Vector3Stamped` | 发布, 默认 | 平台角速度（机体系 FLU rad/s） |
| `/sim/target_contact_force` | `std_msgs/Float32` | 发布, 默认 | 目标灯板上的接触力大小（N） |
| `/sim/impact` | `std_msgs/Bool` | 发布, 默认 | `push` 模式顶住期间为 `true`；`impact` 模式命中后为 `true` |
| `/sim/reset_event` | `std_msgs/Empty` | 发布, 默认 | 每次复位后发一次；`fc01_mission` 收到后清空滤波器/状态机 |
| `/sim/reset` | `std_msgs/Empty` | 订阅, 默认 | 发送一次即复位（无 Viewer 时使用） |
| `/sim/target_pose` | `geometry_msgs/PoseStamped` | 发布, 默认 | 目标真值（世界系） |
| `/sim/target_relative_gt` | `geometry_msgs/PointStamped` | 发布, 默认 | 目标相对位置真值（FRD） |

`/sim/platform_*`、`/sim/target_contact_force`、`/sim/impact`、`/sim/reset_event`
由本包按 `state_publish_hz`（100 Hz）发布，是 `fc01_mission` 的输入；换成真机时
只需让飞控发布同名/同类型的状态话题即可。

## 复位

复位会：平台回到地图 H 标牌上方的 `platform_start_*`、速度清零、解除撞击/顶住状态、
目标复位，并在 `/sim/reset_event` 上发一条空消息；`fc01_mission` 收到后清空视觉
估计、冻结瞄准点、把状态机退回起飞段，重新执行一次完整任务。视觉节点自己的
滤波状态由任务节点复位时一并清空。

三种方式：

- MuJoCo Viewer 左侧的 **Reset** 按钮：仿真每步都会检测 `data.time` 回退和
  目标 mocap 被改写，检测到后同步复位内部状态；
- 键盘 **R**；
- 无 Viewer 时发布空消息：

```bash
ros2 topic pub --once /sim/reset std_msgs/msg/Empty "{}"
```

另外：

- `reset_after_impact_s>0` 会在命中后自动复位；
- `reset_out_of_bounds: true`（默认）在飞机飞出场地（`|x|>30`、`|y|>20`、
  `z<-2` 或 `z>5`）时自动复位，避免调试时飞机掉进地形底部后一直下坠。

## 视角切换

Viewer 窗口（标题 `MuJoCo : fc01_vision_sim`）默认 `headless: false`，启动就有。
默认显示的是 **FPV 相机画面**（和发给视觉节点的图像一致）。Viewer 窗口获得焦点时：

| 按键 | 作用 |
| --- | --- |
| **V** | 在 `fpv`（相机画面）和 `free`（第三人称轨道视角）之间切换，日志输出 `viewer camera: fpv/free` |
| **Esc** | 切到 MuJoCo 自由相机（第三人称） |
| **`[`** / **`]`** | 循环场景中的固定相机；本场景只有一个 `fpv` 相机，所以按一下即回到相机画面 |

第三人称视角用**跟踪相机**锁定飞机：相机在机尾斜后方 2.6 m、俯角 30°，飞机飞到哪
镜头跟到哪，鼠标仍然可以拖拽环绕和滚轮缩放。直接用
`viewer_camera:=free` 启动可以一上来就是第三人称。

也可以直接用 Viewer 左侧面板的 **Camera** 下拉框选择 `Free camera` 或 `fpv`。

## 参数

参数按包分开，**制导/任务参数不再在 `sim.yaml` 里**：

- `config/sim.yaml`：场景、四旋翼模型、飞控侧控制律、平台状态接口（下表）；
- `fc01_mission/config/mission.yaml`：起飞/巡航/冲击/顶住/撤出状态机和
  `/visioncontrol` 发布参数，完整列表见
  [`fc01_mission/README.md`](../../../src/fc01_mission/README.md)；
- `config/vision_image.yaml`：`vision_image_node` 的仿真视觉参数（本包所有）；
- `fc01_vision/config/vision.yaml`：直连相机的视觉参数，与仿真那套相互独立。

`sim.yaml`（本包）：

| 参数 | 默认 | 说明 |
| --- | --- | --- |
| `headless` | `false` | 是否关闭 Viewer |
| `render_width/height` | `320/240` | ROS 图像分辨率 |
| `render_fps` | `30.0` | ROS 图像发布帧率 |
| `physics_hz` | `200.0` | 主循环频率（刚体积分） |
| `camera_fovy_deg` | `70.0` | 垂直视场角（广角 FPV 镜头） |
| `map_xml` | `RMUC2027/scene_rmuc.xml` | 地图 MJCF；相对路径按当前目录、工作区根目录查找 |
| `target_visible` | `false` | `false` = 目标灯板完全透明、只做碰撞代理（地图自带绿灯充当可见目标） |
| `target_radius` | `0.03` | 绿灯半径（m），用于日志/视觉先验；隐形碰撞面板的尺寸固定在 scene.py（24 × 40 × 8 cm） |
| `target_x/y` | `0.315/-4.958` | 绿灯位置（m）；必须与 `mission.yaml` 的同名先验一致 |
| `target_base_z` | `1.373` | 绿灯中心高度（m） |
| `target_motion` | `static` | `static` 固定；`random` 随机航点；`sinusoid` 正弦扫掠 |
| `target_amp_y/z` | `0.0/0.0` | `random` 航点相对基准的横向/垂向范围（m） |
| `target_segment_s` | `2.5` | `random` 航点切换周期（s） |
| `target_random_seed` | `0` | `0` 每次随机；非零固定航点序列 |
| `target_freq_hz` | `0.15` | `sinusoid` 扫掠频率（Hz） |
| `target_marker` | `false` | 是否在地面额外画绿色圆盘（绿灯本身已是绿色，默认关闭） |
| `platform_mesh` | `impact_drone_lod.obj` | 外观网格（assets 内，相对路径） |
| `platform_mesh_hull` | `impact_drone_hull.obj` | 碰撞凸包（assets 内） |
| `platform_mesh_scale` | `1.0` | 1.0 = 按真机 1:1 使用（OBJ 已经是米制）；0 = 按旋翼直径自动缩放（仅兜底） |
| `platform_mass` | `0.24` | 机体质量（kg），真机 240 g |
| `platform_ixx/iyy/izz` | `0.0004/0.0004/0.0006` | 转动惯量（kg·m²） |
| `arm_length` | `0.04` | 旋翼到机体中心的横向距离（m） |
| `rotor_max_thrust` | `2.5` | 单个旋翼最大推力（N），推重比约 4.2 |
| `rotor_drag_m` | `0.01` | 旋翼反扭矩系数（N·m/N） |
| `motor_tau` | `0.04` | 电机推力一阶滞后（s） |
| `attitude_gain` | `260.0` | 姿态误差 → 角加速度增益（自然频率 ≈ 16.1 rad/s） |
| `attitude_damping` | `22.0` | 角速度阻尼（阻尼比 ≈ 0.68） |
| `max_tilt_deg` | `35.0` | 推力方向最大倾角（°）≈ 6.9 m/s² 水平加速度；实际值按垂直推力动态计算 |
| `contact_max_tilt_deg` | `22.0` | 有接触力时的倾角上限（°）；持续顶住只需约 10°，收紧让机身和镜头更稳 |
| `velocity_tau` | `0.12` | 速度环一阶时间常数（s）：`a_des = (v_cmd − v)/tau` |
| `camera_pitch_deg` | `10.0` | 相机安装俯仰（正 = 上仰）；必须与视觉节点一致 |
| `camera_shake_deg` | `0.15` | 发布图像上叠加的镜头振动幅度（°），只影响画面、不影响物理和识别；0 关闭 |
| `camera_noise_lsb` | `1.5` | 发布图像上叠加的传感器噪点标准差（灰度级）；0 关闭 |
| `platform_start_x/y/z` | `-10.15/-3.93/1.775` | 平台初始位置（地图中心 ROBOMASTER 装置上黑底红圈白 H 标牌正上方；牌面 1.731 m + 机壳半高 0.0365 + 约 8 mm 余隙） |
| `platform_yaw_deg` | `-5.6` | 初始偏航：机头对准东侧绿灯 `atan2(-1.031, 10.462)` |
| `landing_pad` | `false` | 是否额外画 H 标志（仅外观）；地图自带的 H 标牌已足够，默认不画 |
| `apply_vision_control` | `true` | 执行 `/visioncontrol`（关掉则原地悬停，便于只测视觉） |
| `vision_control_topic` | `/visioncontrol` | 订阅的制导指令话题（depth 1 keep-last） |
| `command_timeout_s` | `0.5` | 这么久没有新指令就悬停，不再执行旧指令 |
| `engage_mode` | `push` | 飞控侧只决定“接触是否结束本回合”：`push` 继续执行指令；`impact`/`track` 第一次接触就切电机 |
| `reset_after_impact_s` | `0.0` | 命中后复位等待时间，0 表示不复位 |
| `reset_out_of_bounds` | `true` | 飞出场地范围时自动复位 |
| `reset_topic` | `/sim/reset` | 复位话题（`std_msgs/Empty`） |
| `platform_pose_topic` | `/sim/platform_pose` | 平台位姿输出（任务节点输入） |
| `platform_velocity_topic` | `/sim/platform_velocity` | 平台线速度输出 |
| `platform_angular_velocity_topic` | `/sim/platform_angular_velocity` | 平台角速度输出 |
| `contact_force_topic` | `/sim/target_contact_force` | 目标接触力输出 |
| `impact_topic` | `/sim/impact` | 接触/命中标志输出 |
| `reset_event_topic` | `/sim/reset_event` | 复位事件输出 |
| `state_publish_hz` | `100.0` | 上述平台状态话题的发布频率 |
| `publish_ground_truth` | `true` | 是否发布 `/sim/*` 真值 |
| `log_period_s` | `2.0` | 状态日志周期 |
| `image_topic` / `camera_info_topic` | `/sim/camera/image_raw` / `/sim/camera/camera_info` | 图像输出话题 |
| `viewer_camera` | `fpv` | Viewer 初始视角：`fpv` / `free`；运行中按 `V` 切换 |

制导侧的关键默认值（都在 `mission.yaml`，完整说明见
[`fc01_mission/README.md`](../../../src/fc01_mission/README.md)）：

| 参数 | 默认 | 说明 |
| --- | --- | --- |
| `takeoff_altitude_m` | `2.78` | 原地竖直爬升 1 m（从 1.775 m 起）后悬停 |
| `takeoff_climb_mps` | `0.7` | 起飞阶段最大垂直速度（m/s） |
| `takeoff_hover_s` | `0.8` | 到高度后悬停多久再前飞 |
| `seek_ramp_s` | `1.2` | 盲飞巡航速度 smoothstep 渐入时间（s） |
| `cruise_descent_mps` | `1.4` | 巡航段最大下降率（m/s），降到 1.35 m |
| `search_speed` | `4.0` | 未锁定目标时按地图先验盲飞的速度（m/s） |
| `controller_gain` | `2.0` | 位置误差 → 速度增益（1/s），需满足 `gain·velocity_tau < 1` |
| `strike_speed` | `2.0` | 视觉锁定后的直冲速度（m/s） |
| `strike_trigger_m` / `strike_engage_m` | `2.6` / `0.10` | 进入冲撞的距离 / 交给顶住的机头距离（m） |
| `push_speed` | `0.3` | 顶住时的速度指令（m/s），稳态接触力约 0.6 N |
| `push_altitude_m` | `1.35` | 顶住时保持的机体高度（m） |
| `push_hold_s` | `3.0` | 从撞上开始顶住多久后撤出（s） |
| `retreat_speed` / `retreat_distance_m` | `0.8` / `1.0` | 撤出速度（m/s）和撤到离灯多远（m） |
| `vision_control_hz` / `vision_control_source_id` | `50.0` / `fc01_mission` | `/visioncontrol` 发布频率和消息里的 `source_id` |

`config/vision_image.yaml` 是 `vision_image_node` 的仿真参数：绿灯 HSV 单区间
`35,60,60,255,60,255`（H 上限收到 80，避免把场地里色相约 90 的青色装饰条当成灯；
灯的绿色偏暗，S/V 下限放到 60）、`target_shape: circle`、`target_diameter_m: 0.056`，
以及为小目标放宽的 `morph_kernel: 3`、`min_area_ratio: 0.0001`、`min_width/height_px: 3`，
和 `fc01_vision` 的 `config/vision.yaml` 相互独立。这些值都可以在调参窗口里实时改。

`reject_border_touch`（默认 `true`）会丢弃贴到图像边缘的色块：被裁掉一部分的灯
质心偏移、视直径偏小，按直径测距会给出严重偏大的距离，控制会因此把飞机甩出去。
只有完整目标才用于测距，贴边帧按“未检测到”处理。

## 与真实消息的衔接

接口包在 `src/jikl_fc01_system/msg/`（`VisionState`、`VisionHealth`、
`NavigationCommand`、`VelocityCommand`）。字段映射只集中在
`fc01_vision/src/vision_state_adapter.cpp`，直连相机的 `fc01_vision_node` 和仿真用的
`vision_image_node` 共用它，因此两者输出的 `VisionState` 结构完全一致。

`VelocityCommand`（`/visioncontrol`）：

| 字段 | 含义 |
| --- | --- |
| `schema_version` | 目前为 1 |
| `sequence` | 每发一帧加一，接收端可用来发现丢帧 |
| `stamp` | 指令计算时刻（ROS 时钟） |
| `reset_counter` | 每次仿真复位加一，接收端据此清空积分/滤波状态 |
| `source_id` | 默认为发布方的节点名；制导节点发的是 `fc01_mission` |
| `frame_id` | `body_frd`（机体系：x 前、y 右、z 下） |
| `valid` | `false` 表示本帧无效（例如撞击后收油），接收端应保持或忽略 |
| `vx/vy/vz` | 期望速度（m/s），机体系 FRD |
| `wz` | 期望偏航角速度（rad/s），机体系 FRD（z 向下为正）；姿态环把它取反成 FLU 目标角速度，偏航阻尼跟踪它。0 = 不转 |

`VisionState.position` 与 `/fc01/vision/target_relative` 语义一致：目标在机体系
FRD 下的相对位置，单位 m；`frame_id` 同为 `body_frd`。区别是
`VisionState` 带 `valid_fields` 位掩码、序号、时间戳和协方差，消费方必须先看
`POSITION` 位再读数组。

`VisionHealth` 与 `NavigationCommand` 目前只建模，仿真链路还没有发布它们；
任务状态走简单的 `/mission/state`（`std_msgs/String`）。

## 资源工具

`assets/` 里的两个网格都是从项目根目录的 `撞击无人机.STL` 生成的：

```bash
cd /home/han/target/sim_ws/src/fc01_vision_sim
# 碰撞凸包（约 310 面）
python3 tools/make_hull.py /home/han/target/撞击无人机.STL assets/impact_drone_hull.obj
# 外观网格（顶点聚类到 0.15 mm，约 15 万面）
python3 tools/decimate_stl.py /home/han/target/撞击无人机.STL assets/impact_drone_lod.obj 0.15
```

替换模型后重新运行这两条命令并重新构建即可（`setup.py` 会把 `assets/*` 安装到
share 目录）。

## 限制

- 四旋翼是刚体 + 四个推力点，没有桨叶气动、地面效应和空气阻力；姿态环、电机
  滞后、倾角限制和接触响应是真实的，但参数（质量、惯量、推力上限）是典型小
  型机架的估计值，不是某个具体机型的辨识结果。发布的图像上叠加了 0.15° 的
  镜头振动和 1.5 灰度级的噪点，只为让 FPV 画面不像纯 CG；物理、制导和识别
  用的几何量都不受影响。
- 灯本身是视觉网格，碰撞用的是同位置的隐形灯板（mocap 固定体，无限质量），所以是
  “飞机持续顶住不动的灯”，不是把灯推走；接触力来自 MuJoCo 接触求解，是真实的反
  作用力。灯板（24 × 40 cm）和机头碰撞垫都比可见几何大，而且完全透明，只影响
  碰撞，不影响查看器和相机画面。
- 命中/接触判定完全来自 MuJoCo 接触（`mj_contactForce`）；视觉估计误差只写日志
  做结果统计，不参与控制（`push` 用冻结瞄准点）。
- 贴到灯面前时机头相机（比机壳前缘还前 8 cm）会伸进头部结构，画面变黑、检测失效；
  `push` 依赖交接时冻结的瞄准点，`impact` 保持最后一条指令，因此极端情况下可能
  擦过（`hit=no`）。
- 相机是固定安装（无云台）；靠机头偏航对准目标来保持目标在视野内。
- 单目尺寸测距依赖已知灯直径；真机需标定内参并确认目标尺寸。
- 世界系无风、无运动模糊、无传感器噪声；真机需重新调 HSV 和滤波参数。
- Wayland 下打开 Viewer 可能打印 `GLFWError: The platform does not provide the
  window position`，不影响运行。
- 若把 `render_width/height` 改回 640×480，需同时解决 DDS 大消息丢帧问题
  （压缩传输或增大 UDP 缓冲）。
