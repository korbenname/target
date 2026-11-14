#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to jikl_fc01_system__msg__VisionState
/// Temporary FC01 internal contract V1; this is not a vendor camera interface.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct VisionState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub schema_version: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub sequence: u64,

    /// Measurement time in the explicitly agreed ROS/system domain; not callback time.
    pub stamp: builtin_interfaces::msg::Time,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reset_counter: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub frame_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub body_frame_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub source_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub angular_velocity_source: std::string::String,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::VisionState::default())
  }
}

impl rosidl_runtime_rs::Message for VisionState {
  type RmwMsg = super::msg::rmw::VisionState;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        schema_version: msg.schema_version,
        sequence: msg.sequence,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
        reset_counter: msg.reset_counter,
        frame_id: msg.frame_id.as_str().into(),
        body_frame_id: msg.body_frame_id.as_str().into(),
        source_id: msg.source_id.as_str().into(),
        angular_velocity_source: msg.angular_velocity_source.as_str().into(),
        initialized: msg.initialized,
        tracking: msg.tracking,
        calibration_valid: msg.calibration_valid,
        valid_fields: msg.valid_fields,
        position: msg.position,
        velocity: msg.velocity,
        attitude: msg.attitude,
        angular_velocity: msg.angular_velocity,
        pose_covariance: msg.pose_covariance,
        twist_covariance: msg.twist_covariance,
        quality: msg.quality,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      schema_version: msg.schema_version,
      sequence: msg.sequence,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
      reset_counter: msg.reset_counter,
        frame_id: msg.frame_id.as_str().into(),
        body_frame_id: msg.body_frame_id.as_str().into(),
        source_id: msg.source_id.as_str().into(),
        angular_velocity_source: msg.angular_velocity_source.as_str().into(),
      initialized: msg.initialized,
      tracking: msg.tracking,
      calibration_valid: msg.calibration_valid,
      valid_fields: msg.valid_fields,
        position: msg.position,
        velocity: msg.velocity,
        attitude: msg.attitude,
        angular_velocity: msg.angular_velocity,
        pose_covariance: msg.pose_covariance,
        twist_covariance: msg.twist_covariance,
      quality: msg.quality,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      schema_version: msg.schema_version,
      sequence: msg.sequence,
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
      reset_counter: msg.reset_counter,
      frame_id: msg.frame_id.to_string(),
      body_frame_id: msg.body_frame_id.to_string(),
      source_id: msg.source_id.to_string(),
      angular_velocity_source: msg.angular_velocity_source.to_string(),
      initialized: msg.initialized,
      tracking: msg.tracking,
      calibration_valid: msg.calibration_valid,
      valid_fields: msg.valid_fields,
      position: msg.position,
      velocity: msg.velocity,
      attitude: msg.attitude,
      angular_velocity: msg.angular_velocity,
      pose_covariance: msg.pose_covariance,
      twist_covariance: msg.twist_covariance,
      quality: msg.quality,
    }
  }
}


// Corresponds to jikl_fc01_system__msg__VisionHealth
/// Explicit metadata for ONE raw Odometry measurement, joined by exact stamp.
/// All confirmations default false. A live topic does not imply tracking/quality.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct VisionHealth {

    // This member is not documented.
    #[allow(missing_docs)]
    pub schema_version: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::Time,


    // This member is not documented.
    #[allow(missing_docs)]
    pub sequence: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub source_id: std::string::String,

    /// Exact raw Odometry header.frame_id and child_frame_id.
    pub frame_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub body_frame_id: std::string::String,


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
    pub angular_velocity_source: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub quality_valid: bool,

    /// Internal normalized [0,1], only valid when quality_valid; vendor scale needs adapter.
    pub quality: f64,

    /// Bind to immutable, explicitly configured calibration/alignment identifiers.
    pub extrinsics_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub alignment_id: std::string::String,

}



impl Default for VisionHealth {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::VisionHealth::default())
  }
}

impl rosidl_runtime_rs::Message for VisionHealth {
  type RmwMsg = super::msg::rmw::VisionHealth;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        schema_version: msg.schema_version,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
        sequence: msg.sequence,
        source_id: msg.source_id.as_str().into(),
        frame_id: msg.frame_id.as_str().into(),
        body_frame_id: msg.body_frame_id.as_str().into(),
        reset_counter: msg.reset_counter,
        reset_valid: msg.reset_valid,
        initialized: msg.initialized,
        tracking: msg.tracking,
        calibration_valid: msg.calibration_valid,
        frame_alignment_valid: msg.frame_alignment_valid,
        time_sync_valid: msg.time_sync_valid,
        extrinsics_valid: msg.extrinsics_valid,
        metric_scale_valid: msg.metric_scale_valid,
        position_valid: msg.position_valid,
        velocity_valid: msg.velocity_valid,
        attitude_valid: msg.attitude_valid,
        angular_velocity_valid: msg.angular_velocity_valid,
        angular_velocity_source: msg.angular_velocity_source.as_str().into(),
        quality_valid: msg.quality_valid,
        quality: msg.quality,
        extrinsics_id: msg.extrinsics_id.as_str().into(),
        alignment_id: msg.alignment_id.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      schema_version: msg.schema_version,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
      sequence: msg.sequence,
        source_id: msg.source_id.as_str().into(),
        frame_id: msg.frame_id.as_str().into(),
        body_frame_id: msg.body_frame_id.as_str().into(),
      reset_counter: msg.reset_counter,
      reset_valid: msg.reset_valid,
      initialized: msg.initialized,
      tracking: msg.tracking,
      calibration_valid: msg.calibration_valid,
      frame_alignment_valid: msg.frame_alignment_valid,
      time_sync_valid: msg.time_sync_valid,
      extrinsics_valid: msg.extrinsics_valid,
      metric_scale_valid: msg.metric_scale_valid,
      position_valid: msg.position_valid,
      velocity_valid: msg.velocity_valid,
      attitude_valid: msg.attitude_valid,
      angular_velocity_valid: msg.angular_velocity_valid,
        angular_velocity_source: msg.angular_velocity_source.as_str().into(),
      quality_valid: msg.quality_valid,
      quality: msg.quality,
        extrinsics_id: msg.extrinsics_id.as_str().into(),
        alignment_id: msg.alignment_id.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      schema_version: msg.schema_version,
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
      sequence: msg.sequence,
      source_id: msg.source_id.to_string(),
      frame_id: msg.frame_id.to_string(),
      body_frame_id: msg.body_frame_id.to_string(),
      reset_counter: msg.reset_counter,
      reset_valid: msg.reset_valid,
      initialized: msg.initialized,
      tracking: msg.tracking,
      calibration_valid: msg.calibration_valid,
      frame_alignment_valid: msg.frame_alignment_valid,
      time_sync_valid: msg.time_sync_valid,
      extrinsics_valid: msg.extrinsics_valid,
      metric_scale_valid: msg.metric_scale_valid,
      position_valid: msg.position_valid,
      velocity_valid: msg.velocity_valid,
      attitude_valid: msg.attitude_valid,
      angular_velocity_valid: msg.angular_velocity_valid,
      angular_velocity_source: msg.angular_velocity_source.to_string(),
      quality_valid: msg.quality_valid,
      quality: msg.quality,
      extrinsics_id: msg.extrinsics_id.to_string(),
      alignment_id: msg.alignment_id.to_string(),
    }
  }
}


// Corresponds to jikl_fc01_system__msg__NavigationCommand
/// Motion request only. This message cannot authorize ARM, Offboard, or any lease.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub stamp: builtin_interfaces::msg::Time,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reset_counter: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub source_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub frame_id: std::string::String,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::NavigationCommand::default())
  }
}

impl rosidl_runtime_rs::Message for NavigationCommand {
  type RmwMsg = super::msg::rmw::NavigationCommand;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        schema_version: msg.schema_version,
        sequence: msg.sequence,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
        reset_counter: msg.reset_counter,
        source_id: msg.source_id.as_str().into(),
        frame_id: msg.frame_id.as_str().into(),
        mode: msg.mode,
        valid: msg.valid,
        position_valid: msg.position_valid,
        yaw_valid: msg.yaw_valid,
        sticks_valid: msg.sticks_valid,
        position: msg.position,
        yaw: msg.yaw,
        sticks: msg.sticks,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      schema_version: msg.schema_version,
      sequence: msg.sequence,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
      reset_counter: msg.reset_counter,
        source_id: msg.source_id.as_str().into(),
        frame_id: msg.frame_id.as_str().into(),
      mode: msg.mode,
      valid: msg.valid,
      position_valid: msg.position_valid,
      yaw_valid: msg.yaw_valid,
      sticks_valid: msg.sticks_valid,
        position: msg.position,
      yaw: msg.yaw,
        sticks: msg.sticks,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      schema_version: msg.schema_version,
      sequence: msg.sequence,
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
      reset_counter: msg.reset_counter,
      source_id: msg.source_id.to_string(),
      frame_id: msg.frame_id.to_string(),
      mode: msg.mode,
      valid: msg.valid,
      position_valid: msg.position_valid,
      yaw_valid: msg.yaw_valid,
      sticks_valid: msg.sticks_valid,
      position: msg.position,
      yaw: msg.yaw,
      sticks: msg.sticks,
    }
  }
}


// Corresponds to jikl_fc01_system__msg__VelocityCommand
/// 上位机（视觉/制导程序）发给飞控的速度指令。
/// 用于让飞机按期望速度飞行并撞向目标。

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct VelocityCommand {

    // This member is not documented.
    #[allow(missing_docs)]
    pub schema_version: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub sequence: u64,

    /// 指令计算时刻，使用双方约定好的 ROS/系统时钟。
    pub stamp: builtin_interfaces::msg::Time,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reset_counter: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub source_id: std::string::String,

    /// vx/vy/vz 所在坐标系。默认 "body_frd"（机体系：x 前、y 右、z 下）。
    pub frame_id: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::VelocityCommand::default())
  }
}

impl rosidl_runtime_rs::Message for VelocityCommand {
  type RmwMsg = super::msg::rmw::VelocityCommand;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        schema_version: msg.schema_version,
        sequence: msg.sequence,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
        reset_counter: msg.reset_counter,
        source_id: msg.source_id.as_str().into(),
        frame_id: msg.frame_id.as_str().into(),
        valid: msg.valid,
        vx: msg.vx,
        vy: msg.vy,
        vz: msg.vz,
        wz: msg.wz,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      schema_version: msg.schema_version,
      sequence: msg.sequence,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
      reset_counter: msg.reset_counter,
        source_id: msg.source_id.as_str().into(),
        frame_id: msg.frame_id.as_str().into(),
      valid: msg.valid,
      vx: msg.vx,
      vy: msg.vy,
      vz: msg.vz,
      wz: msg.wz,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      schema_version: msg.schema_version,
      sequence: msg.sequence,
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
      reset_counter: msg.reset_counter,
      source_id: msg.source_id.to_string(),
      frame_id: msg.frame_id.to_string(),
      valid: msg.valid,
      vx: msg.vx,
      vy: msg.vy,
      vz: msg.vz,
      wz: msg.wz,
    }
  }
}


