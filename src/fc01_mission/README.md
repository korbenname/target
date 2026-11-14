# fc01_mission

巡航/制导任务包。把原来写在 `fc01_vision_sim` 里的
「起飞 → 盲飞巡航 → 视觉锁定 → 前脸冲撞 → 顶住 → 撤出 → 悬停」状态机拆了出来。
节点不依赖 MuJoCo、不读目标真值，只消费 `/sim/platform_*` 这样的平台状态和视觉
相对位置，输出真实飞控能接的 `jikl_fc01_system/VelocityCommand`。

视觉和平台由部署层提供，本包只管制导：

| 包 | 职责 |
| --- | --- |
| `fc01_vision` | C++ 视觉：`fc01_vision_node`（USB 相机）和 `vision_image_node`（ROS 图像话题） |
| **`fc01_mission`** | 本包：`mission` 制导节点 + `mission.yaml`；`mission.launch.py` 只启动这一个节点 |
| `fc01_bringup` | **实机部署**：启动 `fc01_vision_node` + `mission` |
| `fc01_vision_sim` | **仿真部署**（独立工作区 `sim_ws/`）：MuJoCo 场景、FPV 相机、四旋翼刚体，启动 `vision_image_node` + `mission` |

换到真机时，只需要让飞控发布 `/sim/platform_pose`、
`/sim/platform_velocity`、`/sim/platform_angular_velocity`、
`/sim/target_contact_force` 等话题；制导节点不用改。

## 包结构

```
fc01_mission/
├── config/
│   └── mission.yaml          # 制导/状态机参数
├── fc01_mission/
│   └── mission_node.py       # 制导节点（可执行名 mission）
├── launch/
│   └── mission.launch.py     # 只启动 mission 节点（部署无关）
├── package.xml
└── setup.py
```

## 数据流

```
/fc01/vision/target_relative  ─┐
/fc01/vision/state (可选)      │
/sim/platform_pose            ─┤
/sim/platform_velocity         ├─→ fc01_mission ─→ /visioncontrol       (机体系 FRD, 50 Hz)
/sim/platform_angular_velocity │                  /navigation_command  (锁定前航点, 10 Hz)
                               │                  /mission/state       (状态机阶段, 10 Hz)
/sim/target_contact_force      │
/sim/impact                    │
/sim/reset_event              ─┘
```

`mission` 以 `control_hz`（默认 100 Hz）跑状态机，以 `vision_control_hz`
（默认 50 Hz）发布指令。指令按收讯时刻的姿态换算成世界系速度交给飞控，飞控保持到
下一条命令；超过 `command_timeout_s`（飞控侧）没有新命令就悬停。

任务节点自己也有超时保护：平台状态超过 `pose_timeout_s` 没更新就**停止发指令**
（而不是拿旧姿态继续算），飞控随后悬停。

## 状态机

```
takeoff ──→ seek ──(视觉锁定, ≤ strike_trigger_m)──→ strike ──(0.10 m)──→ push
   ▲          │                                          │                 │
   │          └──(目标丢失/超时)──────────────────────────┘                 │
   │                                                                        │
   └──────────────── reset_event ──────────────────────────── retreat ←── push_hold_s
                                                                 │
                                                                 ▼
                                                                hold
```

- **`takeoff`**：原地竖直爬升到 `takeoff_altitude_m`（2.78 m，从 H 牌上方
  1.775 m 起，即先升 1 m），水平速度恒为 0；到高度后原地悬停
  `takeoff_hover_s`（0.8 s）再进入巡航。悬停是为了避免把 4 m/s 的巡航指令
  突然丢给静止的飞机。
- **`seek`**：视觉还没锁定时按地图先验盲飞（`search_speed` 4 m/s，速度剖面
  `v = max(d − 1.4, 0)` 的 smoothstep 渐入，同时把高度从 2.78 m 降到
  `push_altitude_m`）。一旦检测到目标，切到视觉闭环：位置误差 ×
  `controller_gain` 得到速度，机头对准目标。锁定距离内进入 `strike`。
- **`strike`**：冻结目标的地图精确坐标（RMUC 的灯是静止的），机头固定朝
  `target_face_yaw_deg`（0°，正对灯面），以恒定 `strike_speed`（2.0 m/s）
  直线冲过去。这一段不依赖视觉持续可见。距目标 `strike_engage_m`（0.10 m）
  时交给 `push`，先做 `strike_settle_s`（0.25 s）反向阻尼吸收冲量，避免持续
  往接触里泵能量。
- **`push`**：以 `push_speed`（0.3 m/s）朝冻结瞄准点顶住并保持高度
  `push_altitude_m`（1.35 m）。稳态接触力约 `m·v/velocity_tau ≈ 0.6 N`；
  接触力超过 `push_max_force_n` 时按比例缩小速度指令。被弹开超过
  `push_release_m` 退回 `seek`。
- **`retreat`**：从撞上开始计时，顶住 `push_hold_s`（3.0 s）后沿来时的方向
  倒飞，速度 `retreat_speed`（0.8 m/s）smoothstep 渐入，最后 25 cm 线性刹车。
- **`hold`**：退到离灯 `retreat_distance_m`（1.0 m）处稳定悬停，机头仍朝灯，
  速度指令为 0，不再重复冲撞。
- **`track`**（`engage_mode:=track`）：保持在目标前方 `standoff_m` 处跟踪，
  不撞击。
- **`impact`**（`engage_mode:=impact`）：接近到 `terminal_trigger_m` 内以
  `impact_speed` 末制导冲撞；接触后由飞控收油。

任何阶段收到 `/sim/reset_event` 都会清空视觉估计、冻结瞄准点和计时器，回到
`takeoff`。

## 输出

### `/visioncontrol` — `jikl_fc01_system/VelocityCommand`

| 字段 | 含义 |
| --- | --- |
| `schema_version` | `1` |
| `sequence` | 每帧加一 |
| `stamp` | 指令计算时刻（ROS 时钟） |
| `reset_counter` | 每次复位加一，接收端据此清空积分/滤波状态 |
| `source_id` | `vision_control_source_id`，默认 `fc01_mission` |
| `frame_id` | `body_frd`（x 前、y 右、z 下） |
| `valid` | `false` 表示本帧不可用（已撞击结束、末制导超时等）；任务未使能或暂停时仍发零速度且 `valid=true` |
| `vx/vy/vz` | 期望速度（m/s），机体系 FRD |
| `wz` | 期望偏航角速度（rad/s），机体系 FRD（z 向下为正）。任务节点用平台姿态闭环航向：`wz = yaw_rate_gain × 航向误差 + 设定值导数前馈`，限幅 ±2 rad/s。不再单独发绝对航向角 |

`valid=false` 时仍按频率发帧，接收端可以选择保持或忽略。平台状态超时
（`pose_timeout_s`）时节点直接停止发布，由飞控的 `command_timeout_s` 接管悬停。

`max_vx/vy/vz_mps`（非 0 时）在发布前按机体系 FRD 逐轴裁剪，所有阶段都生效；
调试日志里的 `v_cmd` 仍是未裁剪的制导需求。

### 航向

接口里没有绝对航向角。任务节点自己用 `/sim/platform_pose` 的姿态算当前航向，
与内部航向目标比较后输出角速度 `wz`：巡航时对准目标，冲撞/顶住时正对灯面。
飞控只需要按 `wz` 跟踪偏航角速度；`yaw_rate_gain`（默认 3.0）决定收敛快慢。

### `/navigation_command` — `jikl_fc01_system/NavigationCommand`

视觉锁定前的航点指令，单独话题发给飞控：

- `takeoff` / `seek` 且还没有有效视觉时：`valid=true`、`mode=CRUISE`、
  `position_valid=true`，航点是绿灯的地图先验，高度为 `push_altitude_m`；
- 一出现有效视觉（或离开这两个阶段）：`valid=false`、`mode=HOLD`，飞控应切回
  `/visioncontrol`；
- `position` 按消息约定是 `fc01_vision_ned`（北/东/地，m），任务内部 ENU 会做
  转换；`yaw` 是 NED 航向（从北顺时针）。

飞控判断规则：**`NavigationCommand.valid` 且消息新鲜时按航点飞，否则执行
`/visioncontrol`**。

### `/mission/state` — `std_msgs/String`

状态机当前阶段（`takeoff` / `seek` / `strike` / `push` / `retreat` / `hold`），
`state_publish_hz`（10 Hz）。

## 输入

| 话题 | 类型 | 说明 |
| --- | --- | --- |
| `/fc01/vision/target_relative` | `geometry_msgs/PointStamped` | 目标相对**相机光心**的位置，机体系 FRD，m；无效时 NaN |
| `/fc01/vision/state` | `jikl_fc01_system/VisionState` | `use_vision_state:=true` 时优先使用，只认 `valid_fields` 的 `POSITION` 位 |
| `/sim/platform_pose` | `geometry_msgs/PoseStamped` | 世界系位置 + 机体 FLU 姿态（四元数 wxyz） |
| `/sim/platform_velocity` | `geometry_msgs/Vector3Stamped` | 世界系线速度，m/s |
| `/sim/platform_angular_velocity` | `geometry_msgs/Vector3Stamped` | 机体系 FLU 角速度，rad/s |
| `/sim/target_contact_force` | `std_msgs/Float32` | 与目标灯板的接触力大小，N |
| `/sim/impact` | `std_msgs/Bool` | 飞控报告的接触结束（`impact` 模式） |
| `/sim/reset_event` | `std_msgs/Empty` | 平台已复位 |

视觉/接触类话题用 best-effort、depth 5；平台状态和指令都是设定值，用 depth 1
keep-last——队列一深，外环就会执行几百毫秒前的数据。

## 相机安装偏移与时延补偿

视觉发布的是相对**相机光心**的位置，而制导需要的是相对**机体中心**的世界坐标。
节点按 `camera_pos_x/y/z`（机体 FLU）加上安装偏移，再把 FRD 换算成 FLU
（`[p0, -p1, -p2]`）并旋转到世界系。

测量值还带有网络/处理时延。节点用平台状态里的角速度和线速度做一阶补偿：
用估计的消息年龄（上限 0.15 s）把相对位置从“测到的那一刻”外推到“现在”。
姿态用的是**收到测量那一刻**的机体旋转，而不是当前旋转——外推的是目标相对
位置，不能把姿态变化重复算两次。

`camera_pos_*` 必须和仿真场景里的相机安装位置一致；换机架时两边一起改。

## 构建与运行

```bash
source /opt/ros/humble/setup.bash
cd /home/han/target
colcon build --symlink-install --packages-select jikl_fc01_system fc01_vision fc01_mission fc01_bringup
source install/setup.bash
```

实机部署（USB 相机视觉 + 制导）：

```bash
ros2 launch fc01_bringup robot.launch.py
```

完整仿真在独立工作区 `sim_ws`（先以部署工作区为 underlay 构建）：

```bash
cd /home/han/target/sim_ws
colcon build --symlink-install
source install/setup.bash
ros2 launch fc01_vision_sim vision_sim.launch.py
```

只启动制导（视觉和平台状态由外部提供）：

```bash
ros2 launch fc01_mission mission.launch.py use_vision_state:=true
```

常用参数（实机和仿真的 bringup 都支持；仿真命令需先 source
`/home/han/target/sim_ws/install/setup.bash`）：

```bash
# 持续顶住（默认）
ros2 launch fc01_vision_sim vision_sim.launch.py engage_mode:=push
# 一次撞击
ros2 launch fc01_vision_sim vision_sim.launch.py engage_mode:=impact
# 保持 3 m 跟踪
ros2 launch fc01_vision_sim vision_sim.launch.py engage_mode:=track
# 改用 VisionState 闭环
ros2 launch fc01_vision_sim vision_sim.launch.py use_vision_state:=true
# 只看视觉，不飞
ros2 launch fc01_vision_sim vision_sim.launch.py control_enabled:=false
# 20 Hz 打印控制量/视觉估计
ros2 launch fc01_vision_sim vision_sim.launch.py control_debug_hz:=20.0
```

## 参数

全部在 `config/mission.yaml`（仿真场景/飞控侧参数在
`sim_ws/src/fc01_vision_sim/config/sim.yaml`）：

### 频率与话题

| 参数 | 默认 | 说明 |
| --- | --- | --- |
| `control_hz` | `100.0` | 状态机/控制回路频率 |
| `vision_control_hz` | `50.0` | `/visioncontrol` 发布频率 |
| `publish_vision_control` | `true` | 是否发布 `/visioncontrol` |
| `vision_control_topic` | `/visioncontrol` | 输出话题 |
| `vision_control_source_id` | `fc01_mission` | 消息里的 `source_id` |
| `publish_navigation_command` | `true` | 是否发布视觉锁定前的航点指令 |
| `navigation_command_topic` | `/navigation_command` | 航点指令话题 |
| `navigation_command_hz` | `10.0` | 航点指令发布频率 |
| `yaw_rate_gain` | `3.0` | 航向误差 → 偏航角速度增益（1/s）；0 = 不主动转机头 |
| `max_vx_mps` | `0.0` | 机体系前向速度硬上限（m/s），发布前裁剪；0 = 不限制 |
| `max_vy_mps` | `0.0` | 机体系侧向速度硬上限（m/s）；0 = 不限制 |
| `max_vz_mps` | `0.0` | 机体系垂直速度硬上限（m/s）；0 = 不限制 |
| `relative_topic` | `/fc01/vision/target_relative` | 视觉兼容输出输入 |
| `vision_state_topic` | `/fc01/vision/state` | `VisionState` 输入 |
| `use_vision_state` | `false` | `true` = 优先用 `VisionState` |
| `platform_pose_topic` | `/sim/platform_pose` | 平台位姿输入 |
| `platform_velocity_topic` | `/sim/platform_velocity` | 平台线速度输入 |
| `platform_angular_velocity_topic` | `/sim/platform_angular_velocity` | 机体角速度输入 |
| `contact_force_topic` | `/sim/target_contact_force` | 接触力输入 |
| `impact_topic` | `/sim/impact` | 接触结束标志输入 |
| `reset_event_topic` | `/sim/reset_event` | 复位事件输入 |
| `state_topic` | `/mission/state` | 状态机遥测输出 |
| `state_publish_hz` | `10.0` | 遥测频率 |

### 几何与目标先验

| 参数 | 默认 | 说明 |
| --- | --- | --- |
| `camera_pos_x/y/z` | `0.08/0.0/0.015` | 相机光心在机体 FLU 下的位置（m），必须和场景一致 |
| `target_x/y` | `0.315/-4.958` | 绿灯地图坐标（m），盲飞和静态冲撞用 |
| `target_base_z` | `1.373` | 绿灯中心高度（m） |
| `target_face_yaw_deg` | `0.0` | 冲撞/顶住时的机头航向（°）；灯面朝 -x，0° = 机头朝 +x |
| `target_motion` | `static` | `static` 用地图精确坐标；其他值改用视觉估计做瞄准点 |

### 起飞 / 巡航

| 参数 | 默认 | 说明 |
| --- | --- | --- |
| `takeoff_altitude_m` | `2.78` | 起飞目标高度（m）：从 1.775 m 起竖直爬升 1 m |
| `takeoff_climb_mps` | `0.7` | 起飞阶段最大垂直速度（m/s） |
| `takeoff_hover_s` | `0.8` | 到高度后原地悬停多久再前飞（s） |
| `seek_ramp_s` | `1.2` | 盲飞巡航速度 smoothstep 渐入时间（s） |
| `cruise_descent_mps` | `1.4` | 巡航段最大下降率（m/s），从 2.78 m 降到 1.35 m |

### 闭环与超时

| 参数 | 默认 | 说明 |
| --- | --- | --- |
| `control_enabled` | `true` | 是否运行任务并下发指令 |
| `engage_mode` | `push` | `push` 持续顶；`impact` 一次撞；`track` 保持距离 |
| `standoff_m` | `3.0` | `track` 模式保持的前向距离（m） |
| `controller_gain` | `2.0` | 位置误差 → 速度增益（1/s），需满足 `gain·velocity_tau < 1` |
| `max_speed` | `1.5` | `impact`/`push` 接近段速度限幅（m/s） |
| `search_speed` | `4.0` | 未锁定时按地图先验盲飞的速度（m/s） |
| `track_max_speed` | `2.0` | `track` 模式速度限幅（m/s） |
| `command_timeout_s` | `0.5` | 视觉超过这么久没更新视为丢失 |
| `pose_timeout_s` | `0.5` | 平台状态超时，停止发指令 |
| `contact_timeout_s` | `0.2` | 接触力超时视为未接触（s） |

### 冲撞

| 参数 | 默认 | 说明 |
| --- | --- | --- |
| `strike_speed` | `2.0` | 锁定后直冲速度（m/s）；`<= 0` 关闭冲撞 |
| `strike_trigger_m` | `2.6` | 视觉锁定时距目标多近进入冲撞段（m） |
| `strike_engage_m` | `0.10` | 冲到机头距目标多近交给 `push`（m） |
| `strike_timeout_s` | `3.0` | 冲撞超时（s），超时退回 `seek` |
| `strike_settle_s` | `0.25` | 撞上后反向阻尼吸收冲量的时间（s） |
| `strike_settle_brake_mps` | `0.4` | 吸收段反向速度上限（m/s） |

### 持续冲击

| 参数 | 默认 | 说明 |
| --- | --- | --- |
| `push_engage_m` | `1.2` | 关闭冲撞时，距目标多近切换到 `push`（m） |
| `push_release_m` | `1.8` | 相对冻结瞄准点被弹开多远退回 `seek`（m） |
| `push_speed` | `0.3` | 顶住时的速度指令（m/s），稳态接触力约 0.6 N |
| `push_max_force_n` | `20.0` | 接触力上限（N），超过后按比例缩小指令 |
| `push_altitude_m` | `1.35` | 顶住时保持的机体高度（m） |
| `push_altitude_offset_m` | `0.05` | `push_altitude_m=0` 时相对灯心的偏移（m） |

### 撤出与保护

| 参数 | 默认 | 说明 |
| --- | --- | --- |
| `push_hold_s` | `3.0` | 从撞上开始顶住多久后撤出（s）；`<= 0` 一直顶住 |
| `retreat_speed` | `0.8` | 后退速度（m/s） |
| `retreat_distance_m` | `1.0` | 退到离灯多远切 `hold`（m） |
| `retreat_ramp_s` | `0.5` | 撤出速度 smoothstep 渐入（s） |
| `min_altitude_m` | `0.20` | 世界系高度下限（m），低于它不再向下给指令 |

### impact 模式与调试

| 参数 | 默认 | 说明 |
| --- | --- | --- |
| `impact_speed` | `5.0` | 末制导冲撞速度（m/s） |
| `terminal_trigger_m` | `2.2` | 进入末制导的距离（m） |
| `terminal_timeout_s` | `1.0` | 末制导超时（s） |
| `control_debug_hz` | `0.0` | 控制调试日志频率（0 = 关闭） |

## 调试

- `ros2 topic echo /mission/state` 看状态机走到哪一步。
- `control_debug_hz:=10` 会按频率打印状态、指令速度、平台速度/位置/姿态、
  视觉消息年龄、接触力和顶住距离。
- `ros2 topic echo /visioncontrol --once` 检查帧号、时间戳和 `frame_id`。

## 注意

- `/visioncontrol` 是设定值，订阅端必须用 **depth 1 keep-last**。默认 depth 10
  加上每轮只处理一条回调，会让飞控执行约 200 ms 前的命令，外环会振荡。
- `mission.yaml` 里的 `target_x/y/z` 必须和 `sim.yaml` 的一致；两处都是先验，
  不是反馈。
- `camera_pos_*` 和 `camera_pitch_deg` 必须和场景/视觉节点一致，否则测量会有
  固定偏差。
- `controller_gain · velocity_tau < 1` 是位置环稳定的必要条件（飞控侧
  `velocity_tau` 默认 0.12 s）。
