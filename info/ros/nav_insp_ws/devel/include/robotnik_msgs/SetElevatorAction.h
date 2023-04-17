// Generated by gencpp from file robotnik_msgs/SetElevatorAction.msg
// DO NOT EDIT!


#ifndef ROBOTNIK_MSGS_MESSAGE_SETELEVATORACTION_H
#define ROBOTNIK_MSGS_MESSAGE_SETELEVATORACTION_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <robotnik_msgs/SetElevatorActionGoal.h>
#include <robotnik_msgs/SetElevatorActionResult.h>
#include <robotnik_msgs/SetElevatorActionFeedback.h>

namespace robotnik_msgs
{
template <class ContainerAllocator>
struct SetElevatorAction_
{
  typedef SetElevatorAction_<ContainerAllocator> Type;

  SetElevatorAction_()
    : action_goal()
    , action_result()
    , action_feedback()  {
    }
  SetElevatorAction_(const ContainerAllocator& _alloc)
    : action_goal(_alloc)
    , action_result(_alloc)
    , action_feedback(_alloc)  {
  (void)_alloc;
    }



   typedef  ::robotnik_msgs::SetElevatorActionGoal_<ContainerAllocator>  _action_goal_type;
  _action_goal_type action_goal;

   typedef  ::robotnik_msgs::SetElevatorActionResult_<ContainerAllocator>  _action_result_type;
  _action_result_type action_result;

   typedef  ::robotnik_msgs::SetElevatorActionFeedback_<ContainerAllocator>  _action_feedback_type;
  _action_feedback_type action_feedback;





  typedef boost::shared_ptr< ::robotnik_msgs::SetElevatorAction_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::robotnik_msgs::SetElevatorAction_<ContainerAllocator> const> ConstPtr;

}; // struct SetElevatorAction_

typedef ::robotnik_msgs::SetElevatorAction_<std::allocator<void> > SetElevatorAction;

typedef boost::shared_ptr< ::robotnik_msgs::SetElevatorAction > SetElevatorActionPtr;
typedef boost::shared_ptr< ::robotnik_msgs::SetElevatorAction const> SetElevatorActionConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::robotnik_msgs::SetElevatorAction_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::robotnik_msgs::SetElevatorAction_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace robotnik_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'robotnik_msgs': ['/home/irobot/nav_insp_ws/src/simulation/robotnik_msgs/msg', '/home/irobot/nav_insp_ws/devel/share/robotnik_msgs/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::robotnik_msgs::SetElevatorAction_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::robotnik_msgs::SetElevatorAction_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::robotnik_msgs::SetElevatorAction_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::robotnik_msgs::SetElevatorAction_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robotnik_msgs::SetElevatorAction_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robotnik_msgs::SetElevatorAction_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::robotnik_msgs::SetElevatorAction_<ContainerAllocator> >
{
  static const char* value()
  {
    return "201432bcb5eaa69b9ce4956b570dda0a";
  }

  static const char* value(const ::robotnik_msgs::SetElevatorAction_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x201432bcb5eaa69bULL;
  static const uint64_t static_value2 = 0x9ce4956b570dda0aULL;
};

template<class ContainerAllocator>
struct DataType< ::robotnik_msgs::SetElevatorAction_<ContainerAllocator> >
{
  static const char* value()
  {
    return "robotnik_msgs/SetElevatorAction";
  }

  static const char* value(const ::robotnik_msgs::SetElevatorAction_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::robotnik_msgs::SetElevatorAction_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
\n\
SetElevatorActionGoal action_goal\n\
SetElevatorActionResult action_result\n\
SetElevatorActionFeedback action_feedback\n\
\n\
================================================================================\n\
MSG: robotnik_msgs/SetElevatorActionGoal\n\
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
\n\
Header header\n\
actionlib_msgs/GoalID goal_id\n\
SetElevatorGoal goal\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: actionlib_msgs/GoalID\n\
# The stamp should store the time at which this goal was requested.\n\
# It is used by an action server when it tries to preempt all\n\
# goals that were requested before a certain time\n\
time stamp\n\
\n\
# The id provides a way to associate feedback and\n\
# result message with specific goal requests. The id\n\
# specified must be unique.\n\
string id\n\
\n\
\n\
================================================================================\n\
MSG: robotnik_msgs/SetElevatorGoal\n\
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
robotnik_msgs/ElevatorAction action\n\
\n\
================================================================================\n\
MSG: robotnik_msgs/ElevatorAction\n\
int32 RAISE=1\n\
int32 LOWER=-1\n\
int32 STOP=0\n\
int32 NO_ACTION=1000\n\
\n\
int32 action\n\
# speed, height for future applications\n\
\n\
================================================================================\n\
MSG: robotnik_msgs/SetElevatorActionResult\n\
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
\n\
Header header\n\
actionlib_msgs/GoalStatus status\n\
SetElevatorResult result\n\
\n\
================================================================================\n\
MSG: actionlib_msgs/GoalStatus\n\
GoalID goal_id\n\
uint8 status\n\
uint8 PENDING         = 0   # The goal has yet to be processed by the action server\n\
uint8 ACTIVE          = 1   # The goal is currently being processed by the action server\n\
uint8 PREEMPTED       = 2   # The goal received a cancel request after it started executing\n\
                            #   and has since completed its execution (Terminal State)\n\
uint8 SUCCEEDED       = 3   # The goal was achieved successfully by the action server (Terminal State)\n\
uint8 ABORTED         = 4   # The goal was aborted during execution by the action server due\n\
                            #    to some failure (Terminal State)\n\
uint8 REJECTED        = 5   # The goal was rejected by the action server without being processed,\n\
                            #    because the goal was unattainable or invalid (Terminal State)\n\
uint8 PREEMPTING      = 6   # The goal received a cancel request after it started executing\n\
                            #    and has not yet completed execution\n\
uint8 RECALLING       = 7   # The goal received a cancel request before it started executing,\n\
                            #    but the action server has not yet confirmed that the goal is canceled\n\
uint8 RECALLED        = 8   # The goal received a cancel request before it started executing\n\
                            #    and was successfully cancelled (Terminal State)\n\
uint8 LOST            = 9   # An action client can determine that a goal is LOST. This should not be\n\
                            #    sent over the wire by an action server\n\
\n\
#Allow for the user to associate a string with GoalStatus for debugging\n\
string text\n\
\n\
\n\
================================================================================\n\
MSG: robotnik_msgs/SetElevatorResult\n\
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
bool result\n\
robotnik_msgs/ElevatorStatus status\n\
\n\
================================================================================\n\
MSG: robotnik_msgs/ElevatorStatus\n\
# state\n\
string RAISING=raising\n\
string LOWERING=lowering\n\
string IDLE=idle\n\
string ERROR_G_IO=error_getting_io\n\
string ERROR_S_IO=error_setting_io\n\
string ERROR_TIMEOUT=error_timeout_in_action\n\
# position\n\
string UP=up\n\
string DOWN=down\n\
string UNKNOWN=unknown\n\
# IDLE, RAISING, LOWERING\n\
string state\n\
# UP, DOWN, UNKNOWN\n\
string position\n\
float32 height\n\
\n\
================================================================================\n\
MSG: robotnik_msgs/SetElevatorActionFeedback\n\
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
\n\
Header header\n\
actionlib_msgs/GoalStatus status\n\
SetElevatorFeedback feedback\n\
\n\
================================================================================\n\
MSG: robotnik_msgs/SetElevatorFeedback\n\
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
robotnik_msgs/ElevatorStatus status\n\
\n\
";
  }

  static const char* value(const ::robotnik_msgs::SetElevatorAction_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::robotnik_msgs::SetElevatorAction_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.action_goal);
      stream.next(m.action_result);
      stream.next(m.action_feedback);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SetElevatorAction_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::robotnik_msgs::SetElevatorAction_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::robotnik_msgs::SetElevatorAction_<ContainerAllocator>& v)
  {
    s << indent << "action_goal: ";
    s << std::endl;
    Printer< ::robotnik_msgs::SetElevatorActionGoal_<ContainerAllocator> >::stream(s, indent + "  ", v.action_goal);
    s << indent << "action_result: ";
    s << std::endl;
    Printer< ::robotnik_msgs::SetElevatorActionResult_<ContainerAllocator> >::stream(s, indent + "  ", v.action_result);
    s << indent << "action_feedback: ";
    s << std::endl;
    Printer< ::robotnik_msgs::SetElevatorActionFeedback_<ContainerAllocator> >::stream(s, indent + "  ", v.action_feedback);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROBOTNIK_MSGS_MESSAGE_SETELEVATORACTION_H