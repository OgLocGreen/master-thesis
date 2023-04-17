// Generated by gencpp from file irobot_inspection_pckg/getPartialPanoramaGoal.msg
// DO NOT EDIT!


#ifndef IROBOT_INSPECTION_PCKG_MESSAGE_GETPARTIALPANORAMAGOAL_H
#define IROBOT_INSPECTION_PCKG_MESSAGE_GETPARTIALPANORAMAGOAL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/String.h>
#include <std_msgs/String.h>
#include <std_msgs/String.h>

namespace irobot_inspection_pckg
{
template <class ContainerAllocator>
struct getPartialPanoramaGoal_
{
  typedef getPartialPanoramaGoal_<ContainerAllocator> Type;

  getPartialPanoramaGoal_()
    : folder_path()
    , folder_pano_path()
    , direction()  {
    }
  getPartialPanoramaGoal_(const ContainerAllocator& _alloc)
    : folder_path(_alloc)
    , folder_pano_path(_alloc)
    , direction(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::String_<ContainerAllocator>  _folder_path_type;
  _folder_path_type folder_path;

   typedef  ::std_msgs::String_<ContainerAllocator>  _folder_pano_path_type;
  _folder_pano_path_type folder_pano_path;

   typedef  ::std_msgs::String_<ContainerAllocator>  _direction_type;
  _direction_type direction;





  typedef boost::shared_ptr< ::irobot_inspection_pckg::getPartialPanoramaGoal_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::irobot_inspection_pckg::getPartialPanoramaGoal_<ContainerAllocator> const> ConstPtr;

}; // struct getPartialPanoramaGoal_

typedef ::irobot_inspection_pckg::getPartialPanoramaGoal_<std::allocator<void> > getPartialPanoramaGoal;

typedef boost::shared_ptr< ::irobot_inspection_pckg::getPartialPanoramaGoal > getPartialPanoramaGoalPtr;
typedef boost::shared_ptr< ::irobot_inspection_pckg::getPartialPanoramaGoal const> getPartialPanoramaGoalConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::irobot_inspection_pckg::getPartialPanoramaGoal_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::irobot_inspection_pckg::getPartialPanoramaGoal_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace irobot_inspection_pckg

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg', '/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg'], 'irobot_inspection_pckg': ['/home/irobot/nav_insp_ws/src/inspection/irobot_inspection_pckg/msg', '/home/irobot/nav_insp_ws/devel/share/irobot_inspection_pckg/msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::irobot_inspection_pckg::getPartialPanoramaGoal_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::irobot_inspection_pckg::getPartialPanoramaGoal_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::irobot_inspection_pckg::getPartialPanoramaGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::irobot_inspection_pckg::getPartialPanoramaGoal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::irobot_inspection_pckg::getPartialPanoramaGoal_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::irobot_inspection_pckg::getPartialPanoramaGoal_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::irobot_inspection_pckg::getPartialPanoramaGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ad9bb4e7b347078ce10042b22b1fa765";
  }

  static const char* value(const ::irobot_inspection_pckg::getPartialPanoramaGoal_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xad9bb4e7b347078cULL;
  static const uint64_t static_value2 = 0xe10042b22b1fa765ULL;
};

template<class ContainerAllocator>
struct DataType< ::irobot_inspection_pckg::getPartialPanoramaGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "irobot_inspection_pckg/getPartialPanoramaGoal";
  }

  static const char* value(const ::irobot_inspection_pckg::getPartialPanoramaGoal_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::irobot_inspection_pckg::getPartialPanoramaGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
#goal definition\n\
std_msgs/String folder_path\n\
std_msgs/String folder_pano_path\n\
std_msgs/String direction\n\
\n\
\n\
================================================================================\n\
MSG: std_msgs/String\n\
string data\n\
";
  }

  static const char* value(const ::irobot_inspection_pckg::getPartialPanoramaGoal_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::irobot_inspection_pckg::getPartialPanoramaGoal_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.folder_path);
      stream.next(m.folder_pano_path);
      stream.next(m.direction);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct getPartialPanoramaGoal_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::irobot_inspection_pckg::getPartialPanoramaGoal_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::irobot_inspection_pckg::getPartialPanoramaGoal_<ContainerAllocator>& v)
  {
    s << indent << "folder_path: ";
    s << std::endl;
    Printer< ::std_msgs::String_<ContainerAllocator> >::stream(s, indent + "  ", v.folder_path);
    s << indent << "folder_pano_path: ";
    s << std::endl;
    Printer< ::std_msgs::String_<ContainerAllocator> >::stream(s, indent + "  ", v.folder_pano_path);
    s << indent << "direction: ";
    s << std::endl;
    Printer< ::std_msgs::String_<ContainerAllocator> >::stream(s, indent + "  ", v.direction);
  }
};

} // namespace message_operations
} // namespace ros

#endif // IROBOT_INSPECTION_PCKG_MESSAGE_GETPARTIALPANORAMAGOAL_H
