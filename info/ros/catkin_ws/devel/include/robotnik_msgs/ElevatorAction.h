// Generated by gencpp from file robotnik_msgs/ElevatorAction.msg
// DO NOT EDIT!


#ifndef ROBOTNIK_MSGS_MESSAGE_ELEVATORACTION_H
#define ROBOTNIK_MSGS_MESSAGE_ELEVATORACTION_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace robotnik_msgs
{
template <class ContainerAllocator>
struct ElevatorAction_
{
  typedef ElevatorAction_<ContainerAllocator> Type;

  ElevatorAction_()
    : action(0)  {
    }
  ElevatorAction_(const ContainerAllocator& _alloc)
    : action(0)  {
  (void)_alloc;
    }



   typedef int32_t _action_type;
  _action_type action;



  enum {
    RAISE = 1,
    LOWER = -1,
    STOP = 0,
    NO_ACTION = 1000,
  };


  typedef boost::shared_ptr< ::robotnik_msgs::ElevatorAction_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::robotnik_msgs::ElevatorAction_<ContainerAllocator> const> ConstPtr;

}; // struct ElevatorAction_

typedef ::robotnik_msgs::ElevatorAction_<std::allocator<void> > ElevatorAction;

typedef boost::shared_ptr< ::robotnik_msgs::ElevatorAction > ElevatorActionPtr;
typedef boost::shared_ptr< ::robotnik_msgs::ElevatorAction const> ElevatorActionConstPtr;

// constants requiring out of line definition

   

   

   

   



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::robotnik_msgs::ElevatorAction_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::robotnik_msgs::ElevatorAction_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace robotnik_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'robotnik_msgs': ['/home/irobot/catkin_ws/src/simulacion/robotnik_msgs/msg', '/home/irobot/catkin_ws/devel/share/robotnik_msgs/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::robotnik_msgs::ElevatorAction_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::robotnik_msgs::ElevatorAction_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::robotnik_msgs::ElevatorAction_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::robotnik_msgs::ElevatorAction_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robotnik_msgs::ElevatorAction_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robotnik_msgs::ElevatorAction_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::robotnik_msgs::ElevatorAction_<ContainerAllocator> >
{
  static const char* value()
  {
    return "632c616886d6575f7d7145cd0384a359";
  }

  static const char* value(const ::robotnik_msgs::ElevatorAction_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x632c616886d6575fULL;
  static const uint64_t static_value2 = 0x7d7145cd0384a359ULL;
};

template<class ContainerAllocator>
struct DataType< ::robotnik_msgs::ElevatorAction_<ContainerAllocator> >
{
  static const char* value()
  {
    return "robotnik_msgs/ElevatorAction";
  }

  static const char* value(const ::robotnik_msgs::ElevatorAction_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::robotnik_msgs::ElevatorAction_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int32 RAISE=1\n\
int32 LOWER=-1\n\
int32 STOP=0\n\
int32 NO_ACTION=1000\n\
\n\
int32 action\n\
# speed, height for future applications\n\
";
  }

  static const char* value(const ::robotnik_msgs::ElevatorAction_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::robotnik_msgs::ElevatorAction_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.action);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ElevatorAction_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::robotnik_msgs::ElevatorAction_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::robotnik_msgs::ElevatorAction_<ContainerAllocator>& v)
  {
    s << indent << "action: ";
    Printer<int32_t>::stream(s, indent + "  ", v.action);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROBOTNIK_MSGS_MESSAGE_ELEVATORACTION_H
