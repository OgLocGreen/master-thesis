// Generated by gencpp from file action_server_package/CompleteRectangleCoverageActionGoal.msg
// DO NOT EDIT!


#ifndef ACTION_SERVER_PACKAGE_MESSAGE_COMPLETERECTANGLECOVERAGEACTIONGOAL_H
#define ACTION_SERVER_PACKAGE_MESSAGE_COMPLETERECTANGLECOVERAGEACTIONGOAL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <actionlib_msgs/GoalID.h>
#include <action_server_package/CompleteRectangleCoverageGoal.h>

namespace action_server_package
{
template <class ContainerAllocator>
struct CompleteRectangleCoverageActionGoal_
{
  typedef CompleteRectangleCoverageActionGoal_<ContainerAllocator> Type;

  CompleteRectangleCoverageActionGoal_()
    : header()
    , goal_id()
    , goal()  {
    }
  CompleteRectangleCoverageActionGoal_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , goal_id(_alloc)
    , goal(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef  ::actionlib_msgs::GoalID_<ContainerAllocator>  _goal_id_type;
  _goal_id_type goal_id;

   typedef  ::action_server_package::CompleteRectangleCoverageGoal_<ContainerAllocator>  _goal_type;
  _goal_type goal;





  typedef boost::shared_ptr< ::action_server_package::CompleteRectangleCoverageActionGoal_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::action_server_package::CompleteRectangleCoverageActionGoal_<ContainerAllocator> const> ConstPtr;

}; // struct CompleteRectangleCoverageActionGoal_

typedef ::action_server_package::CompleteRectangleCoverageActionGoal_<std::allocator<void> > CompleteRectangleCoverageActionGoal;

typedef boost::shared_ptr< ::action_server_package::CompleteRectangleCoverageActionGoal > CompleteRectangleCoverageActionGoalPtr;
typedef boost::shared_ptr< ::action_server_package::CompleteRectangleCoverageActionGoal const> CompleteRectangleCoverageActionGoalConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::action_server_package::CompleteRectangleCoverageActionGoal_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::action_server_package::CompleteRectangleCoverageActionGoal_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace action_server_package

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'action_server_package': ['/home/irobot/catkin_ws/devel/share/action_server_package/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::action_server_package::CompleteRectangleCoverageActionGoal_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::action_server_package::CompleteRectangleCoverageActionGoal_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::action_server_package::CompleteRectangleCoverageActionGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::action_server_package::CompleteRectangleCoverageActionGoal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::action_server_package::CompleteRectangleCoverageActionGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::action_server_package::CompleteRectangleCoverageActionGoal_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::action_server_package::CompleteRectangleCoverageActionGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "76331fd4dc627fb5ab53c2743223a28a";
  }

  static const char* value(const ::action_server_package::CompleteRectangleCoverageActionGoal_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x76331fd4dc627fb5ULL;
  static const uint64_t static_value2 = 0xab53c2743223a28aULL;
};

template<class ContainerAllocator>
struct DataType< ::action_server_package::CompleteRectangleCoverageActionGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "action_server_package/CompleteRectangleCoverageActionGoal";
  }

  static const char* value(const ::action_server_package::CompleteRectangleCoverageActionGoal_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::action_server_package::CompleteRectangleCoverageActionGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
\n\
Header header\n\
actionlib_msgs/GoalID goal_id\n\
CompleteRectangleCoverageGoal goal\n\
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
MSG: action_server_package/CompleteRectangleCoverageGoal\n\
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
# Define the goal\n\
float32 rect_long\n\
float32 rect_width\n\
float32 step\n\
float32 dist_lr\n\
float32 laser_width\n\
\n\
float32 vel\n\
";
  }

  static const char* value(const ::action_server_package::CompleteRectangleCoverageActionGoal_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::action_server_package::CompleteRectangleCoverageActionGoal_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.goal_id);
      stream.next(m.goal);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct CompleteRectangleCoverageActionGoal_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::action_server_package::CompleteRectangleCoverageActionGoal_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::action_server_package::CompleteRectangleCoverageActionGoal_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "goal_id: ";
    s << std::endl;
    Printer< ::actionlib_msgs::GoalID_<ContainerAllocator> >::stream(s, indent + "  ", v.goal_id);
    s << indent << "goal: ";
    s << std::endl;
    Printer< ::action_server_package::CompleteRectangleCoverageGoal_<ContainerAllocator> >::stream(s, indent + "  ", v.goal);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ACTION_SERVER_PACKAGE_MESSAGE_COMPLETERECTANGLECOVERAGEACTIONGOAL_H
