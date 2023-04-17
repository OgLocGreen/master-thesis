// Generated by gencpp from file inspection_realsense/findInitialPoseFeedback.msg
// DO NOT EDIT!


#ifndef INSPECTION_REALSENSE_MESSAGE_FINDINITIALPOSEFEEDBACK_H
#define INSPECTION_REALSENSE_MESSAGE_FINDINITIALPOSEFEEDBACK_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace inspection_realsense
{
template <class ContainerAllocator>
struct findInitialPoseFeedback_
{
  typedef findInitialPoseFeedback_<ContainerAllocator> Type;

  findInitialPoseFeedback_()
    : sequence()  {
    }
  findInitialPoseFeedback_(const ContainerAllocator& _alloc)
    : sequence(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector<int32_t, typename ContainerAllocator::template rebind<int32_t>::other >  _sequence_type;
  _sequence_type sequence;





  typedef boost::shared_ptr< ::inspection_realsense::findInitialPoseFeedback_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::inspection_realsense::findInitialPoseFeedback_<ContainerAllocator> const> ConstPtr;

}; // struct findInitialPoseFeedback_

typedef ::inspection_realsense::findInitialPoseFeedback_<std::allocator<void> > findInitialPoseFeedback;

typedef boost::shared_ptr< ::inspection_realsense::findInitialPoseFeedback > findInitialPoseFeedbackPtr;
typedef boost::shared_ptr< ::inspection_realsense::findInitialPoseFeedback const> findInitialPoseFeedbackConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::inspection_realsense::findInitialPoseFeedback_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::inspection_realsense::findInitialPoseFeedback_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace inspection_realsense

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'inspection_realsense': ['/home/irobot/nav_insp_ws/devel/share/inspection_realsense/msg', '/home/irobot/nav_insp_ws/src/inspection_realsense/msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::inspection_realsense::findInitialPoseFeedback_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::inspection_realsense::findInitialPoseFeedback_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::inspection_realsense::findInitialPoseFeedback_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::inspection_realsense::findInitialPoseFeedback_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::inspection_realsense::findInitialPoseFeedback_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::inspection_realsense::findInitialPoseFeedback_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::inspection_realsense::findInitialPoseFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "b81e37d2a31925a0e8ae261a8699cb79";
  }

  static const char* value(const ::inspection_realsense::findInitialPoseFeedback_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xb81e37d2a31925a0ULL;
  static const uint64_t static_value2 = 0xe8ae261a8699cb79ULL;
};

template<class ContainerAllocator>
struct DataType< ::inspection_realsense::findInitialPoseFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "inspection_realsense/findInitialPoseFeedback";
  }

  static const char* value(const ::inspection_realsense::findInitialPoseFeedback_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::inspection_realsense::findInitialPoseFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
#feedback\n\
int32[] sequence\n\
\n\
\n\
";
  }

  static const char* value(const ::inspection_realsense::findInitialPoseFeedback_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::inspection_realsense::findInitialPoseFeedback_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.sequence);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct findInitialPoseFeedback_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::inspection_realsense::findInitialPoseFeedback_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::inspection_realsense::findInitialPoseFeedback_<ContainerAllocator>& v)
  {
    s << indent << "sequence[]" << std::endl;
    for (size_t i = 0; i < v.sequence.size(); ++i)
    {
      s << indent << "  sequence[" << i << "]: ";
      Printer<int32_t>::stream(s, indent + "  ", v.sequence[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // INSPECTION_REALSENSE_MESSAGE_FINDINITIALPOSEFEEDBACK_H
