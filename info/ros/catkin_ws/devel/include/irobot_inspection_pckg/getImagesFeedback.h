// Generated by gencpp from file irobot_inspection_pckg/getImagesFeedback.msg
// DO NOT EDIT!


#ifndef IROBOT_INSPECTION_PCKG_MESSAGE_GETIMAGESFEEDBACK_H
#define IROBOT_INSPECTION_PCKG_MESSAGE_GETIMAGESFEEDBACK_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace irobot_inspection_pckg
{
template <class ContainerAllocator>
struct getImagesFeedback_
{
  typedef getImagesFeedback_<ContainerAllocator> Type;

  getImagesFeedback_()
    : n_imgs(0)  {
    }
  getImagesFeedback_(const ContainerAllocator& _alloc)
    : n_imgs(0)  {
  (void)_alloc;
    }



   typedef int32_t _n_imgs_type;
  _n_imgs_type n_imgs;





  typedef boost::shared_ptr< ::irobot_inspection_pckg::getImagesFeedback_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::irobot_inspection_pckg::getImagesFeedback_<ContainerAllocator> const> ConstPtr;

}; // struct getImagesFeedback_

typedef ::irobot_inspection_pckg::getImagesFeedback_<std::allocator<void> > getImagesFeedback;

typedef boost::shared_ptr< ::irobot_inspection_pckg::getImagesFeedback > getImagesFeedbackPtr;
typedef boost::shared_ptr< ::irobot_inspection_pckg::getImagesFeedback const> getImagesFeedbackConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::irobot_inspection_pckg::getImagesFeedback_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::irobot_inspection_pckg::getImagesFeedback_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace irobot_inspection_pckg

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg', '/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg'], 'irobot_inspection_pckg': ['/home/irobot/catkin_ws/src/irobot_inspection_pckg/msg', '/home/irobot/catkin_ws/devel/share/irobot_inspection_pckg/msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::irobot_inspection_pckg::getImagesFeedback_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::irobot_inspection_pckg::getImagesFeedback_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::irobot_inspection_pckg::getImagesFeedback_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::irobot_inspection_pckg::getImagesFeedback_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::irobot_inspection_pckg::getImagesFeedback_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::irobot_inspection_pckg::getImagesFeedback_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::irobot_inspection_pckg::getImagesFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "42d742e201b01c82efbb9f90e7a251d7";
  }

  static const char* value(const ::irobot_inspection_pckg::getImagesFeedback_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x42d742e201b01c82ULL;
  static const uint64_t static_value2 = 0xefbb9f90e7a251d7ULL;
};

template<class ContainerAllocator>
struct DataType< ::irobot_inspection_pckg::getImagesFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "irobot_inspection_pckg/getImagesFeedback";
  }

  static const char* value(const ::irobot_inspection_pckg::getImagesFeedback_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::irobot_inspection_pckg::getImagesFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
#feedback\n\
int32 n_imgs\n\
\n\
\n\
";
  }

  static const char* value(const ::irobot_inspection_pckg::getImagesFeedback_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::irobot_inspection_pckg::getImagesFeedback_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.n_imgs);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct getImagesFeedback_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::irobot_inspection_pckg::getImagesFeedback_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::irobot_inspection_pckg::getImagesFeedback_<ContainerAllocator>& v)
  {
    s << indent << "n_imgs: ";
    Printer<int32_t>::stream(s, indent + "  ", v.n_imgs);
  }
};

} // namespace message_operations
} // namespace ros

#endif // IROBOT_INSPECTION_PCKG_MESSAGE_GETIMAGESFEEDBACK_H
