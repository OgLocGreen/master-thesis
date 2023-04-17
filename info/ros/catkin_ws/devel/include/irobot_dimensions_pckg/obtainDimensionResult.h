// Generated by gencpp from file irobot_dimensions_pckg/obtainDimensionResult.msg
// DO NOT EDIT!


#ifndef IROBOT_DIMENSIONS_PCKG_MESSAGE_OBTAINDIMENSIONRESULT_H
#define IROBOT_DIMENSIONS_PCKG_MESSAGE_OBTAINDIMENSIONRESULT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace irobot_dimensions_pckg
{
template <class ContainerAllocator>
struct obtainDimensionResult_
{
  typedef obtainDimensionResult_<ContainerAllocator> Type;

  obtainDimensionResult_()
    : large(0.0)
    , width(0.0)  {
    }
  obtainDimensionResult_(const ContainerAllocator& _alloc)
    : large(0.0)
    , width(0.0)  {
  (void)_alloc;
    }



   typedef float _large_type;
  _large_type large;

   typedef float _width_type;
  _width_type width;





  typedef boost::shared_ptr< ::irobot_dimensions_pckg::obtainDimensionResult_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::irobot_dimensions_pckg::obtainDimensionResult_<ContainerAllocator> const> ConstPtr;

}; // struct obtainDimensionResult_

typedef ::irobot_dimensions_pckg::obtainDimensionResult_<std::allocator<void> > obtainDimensionResult;

typedef boost::shared_ptr< ::irobot_dimensions_pckg::obtainDimensionResult > obtainDimensionResultPtr;
typedef boost::shared_ptr< ::irobot_dimensions_pckg::obtainDimensionResult const> obtainDimensionResultConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::irobot_dimensions_pckg::obtainDimensionResult_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::irobot_dimensions_pckg::obtainDimensionResult_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace irobot_dimensions_pckg

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg'], 'irobot_dimensions_pckg': ['/home/irobot/catkin_ws/src/irobot_dimensions_pckg/msg', '/home/irobot/catkin_ws/devel/share/irobot_dimensions_pckg/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg', '/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::irobot_dimensions_pckg::obtainDimensionResult_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::irobot_dimensions_pckg::obtainDimensionResult_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::irobot_dimensions_pckg::obtainDimensionResult_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::irobot_dimensions_pckg::obtainDimensionResult_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::irobot_dimensions_pckg::obtainDimensionResult_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::irobot_dimensions_pckg::obtainDimensionResult_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::irobot_dimensions_pckg::obtainDimensionResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "082de46657ae10e0c1a812e48a6d32ba";
  }

  static const char* value(const ::irobot_dimensions_pckg::obtainDimensionResult_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x082de46657ae10e0ULL;
  static const uint64_t static_value2 = 0xc1a812e48a6d32baULL;
};

template<class ContainerAllocator>
struct DataType< ::irobot_dimensions_pckg::obtainDimensionResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "irobot_dimensions_pckg/obtainDimensionResult";
  }

  static const char* value(const ::irobot_dimensions_pckg::obtainDimensionResult_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::irobot_dimensions_pckg::obtainDimensionResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
#result definition\n\
#bool finished\n\
float32 large\n\
float32 width\n\
";
  }

  static const char* value(const ::irobot_dimensions_pckg::obtainDimensionResult_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::irobot_dimensions_pckg::obtainDimensionResult_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.large);
      stream.next(m.width);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct obtainDimensionResult_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::irobot_dimensions_pckg::obtainDimensionResult_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::irobot_dimensions_pckg::obtainDimensionResult_<ContainerAllocator>& v)
  {
    s << indent << "large: ";
    Printer<float>::stream(s, indent + "  ", v.large);
    s << indent << "width: ";
    Printer<float>::stream(s, indent + "  ", v.width);
  }
};

} // namespace message_operations
} // namespace ros

#endif // IROBOT_DIMENSIONS_PCKG_MESSAGE_OBTAINDIMENSIONRESULT_H