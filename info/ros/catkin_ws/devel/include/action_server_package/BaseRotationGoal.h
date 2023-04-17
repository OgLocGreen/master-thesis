// Generated by gencpp from file action_server_package/BaseRotationGoal.msg
// DO NOT EDIT!


#ifndef ACTION_SERVER_PACKAGE_MESSAGE_BASEROTATIONGOAL_H
#define ACTION_SERVER_PACKAGE_MESSAGE_BASEROTATIONGOAL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace action_server_package
{
template <class ContainerAllocator>
struct BaseRotationGoal_
{
  typedef BaseRotationGoal_<ContainerAllocator> Type;

  BaseRotationGoal_()
    : number_of_degrees(0.0)  {
    }
  BaseRotationGoal_(const ContainerAllocator& _alloc)
    : number_of_degrees(0.0)  {
  (void)_alloc;
    }



   typedef float _number_of_degrees_type;
  _number_of_degrees_type number_of_degrees;





  typedef boost::shared_ptr< ::action_server_package::BaseRotationGoal_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::action_server_package::BaseRotationGoal_<ContainerAllocator> const> ConstPtr;

}; // struct BaseRotationGoal_

typedef ::action_server_package::BaseRotationGoal_<std::allocator<void> > BaseRotationGoal;

typedef boost::shared_ptr< ::action_server_package::BaseRotationGoal > BaseRotationGoalPtr;
typedef boost::shared_ptr< ::action_server_package::BaseRotationGoal const> BaseRotationGoalConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::action_server_package::BaseRotationGoal_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::action_server_package::BaseRotationGoal_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace action_server_package

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'action_server_package': ['/home/irobot/catkin_ws/devel/share/action_server_package/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::action_server_package::BaseRotationGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::action_server_package::BaseRotationGoal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::action_server_package::BaseRotationGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::action_server_package::BaseRotationGoal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::action_server_package::BaseRotationGoal_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::action_server_package::BaseRotationGoal_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::action_server_package::BaseRotationGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "b76287a0341f327cec116af10e16f6d8";
  }

  static const char* value(const ::action_server_package::BaseRotationGoal_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xb76287a0341f327cULL;
  static const uint64_t static_value2 = 0xec116af10e16f6d8ULL;
};

template<class ContainerAllocator>
struct DataType< ::action_server_package::BaseRotationGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "action_server_package/BaseRotationGoal";
  }

  static const char* value(const ::action_server_package::BaseRotationGoal_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::action_server_package::BaseRotationGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
# Define the goal\n\
float32 number_of_degrees\n\
";
  }

  static const char* value(const ::action_server_package::BaseRotationGoal_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::action_server_package::BaseRotationGoal_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.number_of_degrees);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct BaseRotationGoal_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::action_server_package::BaseRotationGoal_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::action_server_package::BaseRotationGoal_<ContainerAllocator>& v)
  {
    s << indent << "number_of_degrees: ";
    Printer<float>::stream(s, indent + "  ", v.number_of_degrees);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ACTION_SERVER_PACKAGE_MESSAGE_BASEROTATIONGOAL_H
