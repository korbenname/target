#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "jikl_fc01_system__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__jikl_fc01_system__msg__VisionState() -> *const std::ffi::c_void;
}

#[link(name = "jikl_fc01_system__rosidl_generator_c")]
extern "C" {
    fn jikl_fc01_system__msg__VisionState__init(msg: *mut VisionState) -> bool;
    fn jikl_fc01_system__msg__VisionState__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<VisionState>, size: usize) -> bool;
    fn jikl_fc01_system__msg__VisionState__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<VisionState>);
    fn jikl_fc01_system__msg__VisionState__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<VisionState>, out_seq: *mut rosidl_runtime_rs::Sequence<VisionState>) -> bool;
}

// Corresponds to jikl_fc01_system__msg__VisionState
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Temporary FC01 internal contract V1; this is not a vendor camera interface.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct VisionState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub schema_version: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub sequence: u64,

    /// Measurement time in the explicitly agreed ROS/system domain; not callback time.
    pub stamp: builtin_interfaces::msg::rmw::Time,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reset_counter: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub frame_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub body_frame_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub source_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub angular_velocity_source: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub initialized: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub tracking: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub calibration_valid: bool,

    /// Default mask 0 means every default numeric payload is UNKNOWN.
    pub valid_fields: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub position: [f64; 3],


    // This member is not documented.
    #[allow(missing_docs)]
    pub velocity: [f64; 3],

    /// Hamilton w,x,y,z, rotating body FRD into fc01_vision_ned. Not ROS xyzw.
    pub attitude: [f64; 4],

    /// Body FRD, rad/s. Valid only with ANGULAR_VELOCITY and nonempty source.
    pub angular_velocity: [f64; 3],

    /// Row-major 6x6, linear xyz then fixed-axis angular xyz. Separate validity bits.
    #[cfg_attr(feature = "serde", serde(with = "serde_big_array::BigArray"))]
    pub pose_covariance: [f64; 36],


    // This member is not documented.
    #[allow(missing_docs)]
    #[cfg_attr(feature = "serde", serde(with = "serde_big_array::BigArray"))]
    pub twist_covariance: [f64; 36],

    /// Explicit normalized [0,1] internal quality; unknown unless QUALITY is set.
    pub quality: f64,

}

impl VisionState {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const POSITION: u16 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const VELOCITY: u16 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ATTITUDE: u16 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ANGULAR_VELOCITY: u16 = 8;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const POSE_COVARIANCE: u16 = 16;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const TWIST_COVARIANCE: u16 = 32;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const QUALITY: u16 = 64;

}


impl Default for VisionState {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !jikl_fc01_system__msg__VisionState__init(&mut msg as *mut _) {
        panic!("Call to jikl_fc01_system__msg__VisionState__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for VisionState {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { jikl_fc01_system__msg__VisionState__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { jikl_fc01_system__msg__VisionState__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { jikl_fc01_system__msg__VisionState__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for VisionState {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for VisionState where Self: Sized {
  const TYPE_NAME: &'static str = "jikl_fc01_system/msg/VisionState";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__jikl_fc01_system__msg__VisionState() }
  }
}


#[link(name = "jikl_fc01_system__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__jikl_fc01_system__msg__VisionHealth() -> *const std::ffi::c_void;
}

#[link(name = "jikl_fc01_system__rosidl_generator_c")]
extern "C" {
    fn jikl_fc01_system__msg__VisionHealth__init(msg: *mut VisionHealth) -> bool;
    fn jikl_fc01_system__msg__VisionHealth__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<VisionHealth>, size: usize) -> bool;
    fn jikl_fc01_system__msg__VisionHealth__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<VisionHealth>);
    fn jikl_fc01_system__msg__VisionHealth__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<VisionHealth>, out_seq: *mut rosidl_runtime_rs::Sequence<VisionHealth>) -> bool;
}

// Corresponds to jikl_fc01_system__msg__VisionHealth
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Explicit metadata for ONE raw Odometry measurement, joined by exact stamp.
/// All confirmations default false. A live topic does not imply tracking/quality.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct VisionHealth {

    // This member is not documented.
    #[allow(missing_docs)]
    pub schema_version: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,


    // This member is not documented.
    #[allow(missing_docs)]
    pub sequence: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub source_id: rosidl_runtime_rs::String,

    /// Exact raw Odometry header.frame_id and child_frame_id.
    pub frame_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub body_frame_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reset_counter: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reset_valid: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub initialized: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub tracking: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub calibration_valid: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub frame_alignment_valid: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub time_sync_valid: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub extrinsics_valid: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub metric_scale_valid: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub position_valid: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub velocity_valid: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub attitude_valid: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub angular_velocity_valid: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub angular_velocity_source: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub quality_valid: bool,

    /// Internal normalized [0,1], only valid when quality_valid; vendor scale needs adapter.
    pub quality: f64,

    /// Bind to immutable, explicitly configured calibration/alignment identifiers.
    pub extrinsics_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub alignment_id: rosidl_runtime_rs::String,

}



impl Default for VisionHealth {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !jikl_fc01_system__msg__VisionHealth__init(&mut msg as *mut _) {
        panic!("Call to jikl_fc01_system__msg__VisionHealth__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for VisionHealth {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { jikl_fc01_system__msg__VisionHealth__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { jikl_fc01_system__msg__VisionHealth__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { jikl_fc01_system__msg__VisionHealth__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for VisionHealth {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for VisionHealth where Self: Sized {
  const TYPE_NAME: &'static str = "jikl_fc01_system/msg/VisionHealth";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__jikl_fc01_system__msg__VisionHealth() }
  }
}


#[link(name = "jikl_fc01_system__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__jikl_fc01_system__msg__NavigationCommand() -> *const std::ffi::c_void;
}

#[link(name = "jikl_fc01_system__rosidl_generator_c")]
extern "C" {
    fn jikl_fc01_system__msg__NavigationCommand__init(msg: *mut NavigationCommand) -> bool;
    fn jikl_fc01_system__msg__NavigationCommand__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<NavigationCommand>, size: usize) -> bool;
    fn jikl_fc01_system__msg__NavigationCommand__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<NavigationCommand>);
    fn jikl_fc01_system__msg__NavigationCommand__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<NavigationCommand>, out_seq: *mut rosidl_runtime_rs::Sequence<NavigationCommand>) -> bool;
}

// Corresponds to jikl_fc01_system__msg__NavigationCommand
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Motion request only. This message cannot authorize ARM, Offboard, or any lease.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct NavigationCommand {

    // This member is not documented.
    #[allow(missing_docs)]
    pub schema_version: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub sequence: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reset_counter: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub source_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub frame_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mode: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub valid: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub position_valid: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub yaw_valid: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub sticks_valid: bool,

    /// Absolute point in fc01_vision_ned, metres; Cruise only when position_valid.
    pub position: [f64; 3],

    /// Absolute NED yaw, radians, when yaw_valid.
    pub yaw: f64,

    /// roll/pitch/yaw/throttle in [-1,1], valid only for Follow with sticks_valid.
    pub sticks: [f64; 4],

}

impl NavigationCommand {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const DISABLED: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const HOLD: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CRUISE: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const FOLLOW: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const LAND: u8 = 4;

}


impl Default for NavigationCommand {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !jikl_fc01_system__msg__NavigationCommand__init(&mut msg as *mut _) {
        panic!("Call to jikl_fc01_system__msg__NavigationCommand__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for NavigationCommand {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { jikl_fc01_system__msg__NavigationCommand__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { jikl_fc01_system__msg__NavigationCommand__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { jikl_fc01_system__msg__NavigationCommand__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for NavigationCommand {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for NavigationCommand where Self: Sized {
  const TYPE_NAME: &'static str = "jikl_fc01_system/msg/NavigationCommand";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__jikl_fc01_system__msg__NavigationCommand() }
  }
}


#[link(name = "jikl_fc01_system__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__jikl_fc01_system__msg__VelocityCommand() -> *const std::ffi::c_void;
}

#[link(name = "jikl_fc01_system__rosidl_generator_c")]
extern "C" {
    fn jikl_fc01_system__msg__VelocityCommand__init(msg: *mut VelocityCommand) -> bool;
    fn jikl_fc01_system__msg__VelocityCommand__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<VelocityCommand>, size: usize) -> bool;
    fn jikl_fc01_system__msg__VelocityCommand__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<VelocityCommand>);
    fn jikl_fc01_system__msg__VelocityCommand__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<VelocityCommand>, out_seq: *mut rosidl_runtime_rs::Sequence<VelocityCommand>) -> bool;
}

// Corresponds to jikl_fc01_system__msg__VelocityCommand
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 上位机（视觉/制导程序）发给飞控的速度指令。
/// 用于让飞机按期望速度飞行并撞向目标。

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct VelocityCommand {

    // This member is not documented.
    #[allow(missing_docs)]
    pub schema_version: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub sequence: u64,

    /// 指令计算时刻，使用双方约定好的 ROS/系统时钟。
    pub stamp: builtin_interfaces::msg::rmw::Time,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reset_counter: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub source_id: rosidl_runtime_rs::String,

    /// vx/vy/vz 所在坐标系。默认 "body_frd"（机体系：x 前、y 右、z 下）。
    pub frame_id: rosidl_runtime_rs::String,

    /// false 表示本帧无效，接收端应保持上一状态或忽略。
    pub valid: bool,

    /// 期望速度，单位 m/s。默认机体系 FRD：
    ///   vx > 0 向前，vx < 0 向后
    ///   vy > 0 向右，vy < 0 向左
    ///   vz > 0 向下，vz < 0 向上
    pub vx: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub vy: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub vz: f64,

    /// 期望偏航角速度，单位 rad/s，坐标系与 vx/vy/vz 相同（默认 body_frd：
    /// 绕机体 z 轴、向下为正，即俯视顺时针）。作为偏航速率前馈使用；
    /// 0 表示不提供速率前馈，接收端仍按航向角目标跟踪。
    pub wz: f64,

}



impl Default for VelocityCommand {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !jikl_fc01_system__msg__VelocityCommand__init(&mut msg as *mut _) {
        panic!("Call to jikl_fc01_system__msg__VelocityCommand__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for VelocityCommand {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { jikl_fc01_system__msg__VelocityCommand__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { jikl_fc01_system__msg__VelocityCommand__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { jikl_fc01_system__msg__VelocityCommand__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for VelocityCommand {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for VelocityCommand where Self: Sized {
  const TYPE_NAME: &'static str = "jikl_fc01_system/msg/VelocityCommand";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__jikl_fc01_system__msg__VelocityCommand() }
  }
}


