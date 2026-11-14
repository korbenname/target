# fc01 撞击无人机

视觉制导的四旋翼演示：飞机从 RMUC2027 场地中心 ROBOMASTER 装置上方那块
「黑底、红圈、白色 H」的标牌起飞，用机载相机识别东侧基地头部的绿色指示灯，
用机头前脸冲撞并持续顶住 3 s，然后稳定撤出、悬停。

仓库分成**实机部署**和**仿真**两个独立工作区。

## 目录结构

```
target/                      # 部署工作区（实机）
├── src/
│   ├── jikl_fc01_system/    消息：VelocityCommand / NavigationCommand / VisionState …
│   ├── fc01_vision/         视觉：USB 相机节点 + 图像话题节点（C++）
│   ├── fc01_mission/        制导状态机（Python）
│   └── fc01_bringup/        实机启动 launch
├── build/ install/ log/     colcon 产物（不跟踪）
└── sim_ws/                  仿真工作区（被 .gitignore 忽略，单独管理）
    ├── src/fc01_vision_sim/ MuJoCo 场景、飞控模型、仿真相机
    └── RMUC2027/            地图资源
```

仿真不拷到实机板子上；实机只需要部署工作区的 4 个包。

## 构建与运行

### 实机 / 部署工作区

```bash
source /opt/ros/humble/setup.bash
cd /home/han/target
colcon build --symlink-install --packages-select \
  jikl_fc01_system fc01_vision fc01_mission fc01_bringup
source install/setup.bash

ros2 launch fc01_bringup robot.launch.py
```

可视化默认关闭；需要 OpenCV 预览/滑条窗口时，在
`fc01_vision/config/vision.yaml` 里设 `visualization: true`。

ARM 板（如香橙派 Zero 3W）的依赖、帧率配置、飞控桥接和标定注意事项见
[`src/fc01_bringup/README.md`](src/fc01_bringup/README.md)。

### 仿真工作区

仿真以部署工作区为 underlay：

```bash
source /opt/ros/humble/setup.bash
source /home/han/target/install/setup.bash

cd /home/han/target/sim_ws
colcon build --symlink-install
source install/setup.bash

ros2 launch fc01_vision_sim vision_sim.launch.py
```

`sim_ws/` 在 `.gitignore` 里；如果仿真代码需要版本管理，可以在 `sim_ws/` 里
单独 `git init`，或去掉忽略规则后与部署代码放在同一个仓库。

## 接口速览

| 话题 | 类型 | 方向 |
| --- | --- | --- |
| `/fc01/vision/state` | `jikl_fc01_system/VisionState` | 视觉 → 制导 |
| `/visioncontrol` | `jikl_fc01_system/VelocityCommand` | 制导 → 飞控（机体系 FRD：`vx/vy/vz` + `wz`） |
| `/navigation_command` | `jikl_fc01_system/NavigationCommand` | 制导 → 飞控（视觉锁定前的航点，NED） |
| `/mission/state` | `std_msgs/String` | 状态机阶段遥测 |
| `/sim/platform_pose` 等 | `PoseStamped` / `Vector3Stamped` / `Float32` … | 飞控 → 制导（位姿、速度、角速度、接触力） |

坐标约定：

- 世界系为 ENU（x 东、y 北、z 上）；
- `VelocityCommand` 是机体系 FRD（x 前、y 右、z 下）；
- `NavigationCommand.position` 是 NED，制导内部会自动转换。

## Git 忽略规则

`.gitignore` 排除了：

- `build/`、`install/`、`log/` 等 colcon 产物；
- `sim_ws/`（仿真工作区，单独管理）；
- `scene_images/`、`撞击无人机.STL`（生成图 / 21 MB 源网格）；
- 根目录过期的 `VelocityCommand.msg` 副本；
- `__pycache__/`、`*.pyc`、`*.egg-info`、`.pytest_cache`。

各包的详细说明：

- [fc01_vision](src/fc01_vision/README.md)
- [fc01_mission](src/fc01_mission/README.md)
- [fc01_bringup](src/fc01_bringup/README.md)
- [fc01_vision_sim](sim_ws/src/fc01_vision_sim/README.md)
