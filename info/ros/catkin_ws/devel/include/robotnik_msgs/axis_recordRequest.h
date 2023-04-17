// Generated by gencpp from file robotnik_msgs/axis_recordRequest.msg
// DO NOT EDIT!


#ifndef ROBOTNIK_MSGS_MESSAGE_AXIS_RECORDREQUEST_H
#define ROBOTNIK_MSGS_MESSAGE_AXIS_RECORDREQUEST_H


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
struct axis_recordRequest_
{
  typedef axis_recordRequest_<ContainerAllocator> Type;

  axis_recordRequest_()
    : action(0)
    , directory()
    , profile()
    , id()  {
    }
  axis_recordRequest_(const ContainerAllocator& _alloc)
    : action(0)
    , directory(_alloc)
    , profile(_alloc)
    , id(_alloc)  {
  (void)_alloc;
    }



   typedef int8_t _action_type;
  _action_type action;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _directory_type;
  _directory_type directory;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _profile_type;
  _profile_type profile;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _id_type;
  _id_type id;





  typedef boost::shared_ptr< ::robotnik_msgs::axis_recordRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::robotnik_msgs::axis_recordRequest_<ContainerAllocator> const> ConstPtr;

}; // struct axis_recordRequest_

typedef ::robotnik_msgs::axis_recordRequest_<std::allocator<void> > axis_recordRequest;

typedef boost::shared_ptr< ::robotnik_msgs::axis_recordRequest > axis_recordRequestPtr;
typedef boost::shared_ptr< ::robotnik_msgs::axis_recordRequest const> axis_recordRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::robotnik_msgs::axis_recordRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::robotnik_msgs::axis_recordRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace robotnik_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'robotnik_msgs': ['/home/irobot/catkin_ws/src/simulacion/robotnik_msgs/msg', '/home/irobot/catkin_ws/devel/share/robotnik_msgs/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::robotnik_msgs::axis_recordRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::robotnik_msgs::axis_recordRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::robotnik_msgs::axis_recordRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::robotnik_msgs::axis_recordRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robotnik_msgs::axis_recordRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robotnik_msgs::axis_recordRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::robotnik_msgs::axis_recordRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "39a90fb80eeb30fd1922ed05ed1384be";
  }

  static const char* value(const ::robotnik_msgs::axis_recordRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x39a90fb80eeb30fdULL;
  static const uint64_t static_value2 = 0x1922ed05ed1384beULL;
};

template<class ContainerAllocator>
struct DataType< ::robotnik_msgs::axis_recordRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "robotnik_msgs/axis_recordRequest";
  }

  static const char* value(const ::robotnik_msgs::axis_recordRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::robotnik_msgs::axis_recordRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n\
\n\
int8 action\n\
\n\
string directory\n\
\n\
string profile\n\
\n\
string id\n\
";
  }

  static const char* value(const ::robotnik_msgs::axis_recordRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::robotnik_msgs::axis_recordRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.action);
      stream.next(m.directory);
      stream.next(m.profile);
      stream.next(m.id);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct axis_recordRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::robotnik_msgs::axis_recordRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::robotnik_msgs::axis_recordRequest_<ContainerAllocator>& v)
  {
    s << indent << "action: ";
    Printer<int8_t>::stream(s, indent + "  ", v.action);
    s << indent << "directory: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.directory);
    s << indent << "profile: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.profile);
    s << indent << "id: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.id);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROBOTNIK_MSGS_MESSAGE_AXIS_RECORDREQUEST_H
