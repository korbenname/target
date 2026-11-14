# 上位机（视觉/制导程序）发给飞控的速度指令。
# 用于让飞机按期望速度飞行并撞向目标。
uint16 schema_version 1
uint64 sequence
# 指令计算时刻，使用双方约定好的 ROS/系统时钟。
builtin_interfaces/Time stamp
uint32 reset_counter
string source_id
# vx/vy/vz 所在坐标系。默认 "body_frd"（机体系：x 前、y 右、z 下）。
string frame_id
# false 表示本帧无效，接收端应保持上一状态或忽略。
bool valid
# 期望速度，单位 m/s。默认机体系 FRD：
#   vx > 0 向前，vx < 0 向后
#   vy > 0 向右，vy < 0 向左
#   vz > 0 向下，vz < 0 向上
float64 vx
float64 vy
float64 vz
float64 vw
