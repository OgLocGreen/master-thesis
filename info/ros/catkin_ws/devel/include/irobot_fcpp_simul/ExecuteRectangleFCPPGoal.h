// Generated by gencpp from file irobot_fcpp_simul/ExecuteRectangleFCPPGoal.msg
// DO NOT EDIT!


#ifndef IROBOT_FCPP_SIMUL_MESSAGE_EXECUTERECTANGLEFCPPGOAL_H
#define IROBOT_FCPP_SIMUL_MESSAGE_EXECUTERECTANGLEFCPPGOAL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <geometry_msgs/Polygon.h>

namespace irobot_fcpp_simul
{
template <class ContainerAllocator>
struct ExecuteRectangleFCPPGoal_
{
  typedef ExecuteRectangleFCPPGoal_<ContainerAllocator> Type;

  ExecuteRectangleFCPPGoal_()
    : rectangle_id(0)
    , operation_type(0)
    , rectangle()  {
    }
  ExecuteRectangleFCPPGoal_(const ContainerAllocator& _alloc)
    : rectangle_id(0)
    , operation_type(0)
    , rectangle(_alloc)  {
  (void)_alloc;
    }



   typedef int32_t _rectangle_id_type;
  _rectangle_id_type rectangle_id;

   typedef int32_t _operation_type_type;
  _operation_type_type operation_type;

   typedef  ::geometry_msgs::Polygon_<ContainerAllocator>  _rectangle_type;
  _rectangle_type rectangle;





  typedef boost::shared_ptr< ::irobot_fcpp_simul::ExecuteRectangleFCPPGoal_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::irobot_fcpp_simul::ExecuteRectangleFCPPGoal_<ContainerAllocator> const> ConstPtr;

}; // struct ExecuteRectangleFCPPGoal_

typedef ::irobot_fcpp_simul::ExecuteRectangleFCPPGoal_<std::allocator<void> > ExecuteRectangleFCPPGoal;

typedef boost::shared_ptr< ::irobot_fcpp_simul::ExecuteRectangleFCPPGoal > ExecuteRectangleFCPPGoalPtr;
typedef boost::shared_ptr< ::irobot_fcpp_simul::ExecuteRectangleFCPPGoal const> ExecuteRectangleFCPPGoalConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::irobot_fcpp_simul::ExecuteRectangleFCPPGoal_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::irobot_fcpp_simul::ExecuteRectangleFCPPGoal_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace irobot_fcpp_simul

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg', '/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'irobot_fcpp_simul': ['/home/irobot/catkin_ws/src/irobot_fcpp_simul/msg', '/home/irobot/catkin_ws/devel/share/irobot_fcpp_simul/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::irobot_fcpp_simul::ExecuteRectangleFCPPGoal_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::irobot_fcpp_simul::ExecuteRectangleFCPPGoal_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::irobot_fcpp_simul::ExecuteRectangleFCPPGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::irobot_fcpp_simul::ExecuteRectangleFCPPGoal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::irobot_fcpp_simul::ExecuteRectangleFCPPGoal_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::irobot_fcpp_simul::ExecuteRectangleFCPPGoal_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::irobot_fcpp_simul::ExecuteRectangleFCPPGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "93e42b79de0e56f88bd428b2bd59ee26";
  }

  static const char* value(const ::irobot_fcpp_simul::ExecuteRectangleFCPPGoal_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x93e42b79de0e56f8ULL;
  static const uint64_t static_value2 = 0x8bd428b2bd59ee26ULL;
};

template<class ContainerAllocator>
struct DataType< ::irobot_fcpp_simul::ExecuteRectangleFCPPGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "irobot_fcpp_simul/ExecuteRectangleFCPPGoal";
  }

  static const char* value(const ::irobot_fcpp_simul::ExecuteRectangleFCPPGoal_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::irobot_fcpp_simul::ExecuteRectangleFCPPGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
# Define the goal\n\
#int32 chapa_id\n\
int32 rectangle_id #0,90,180,270\n\
\n\
int32 operation_type\n\
\n\
geometry_msgs/Polygon rectangle\n\
\n\
\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Polygon\n\
#A specification of a polygon where the first and last points are assumed to be connected\n\
Point32[] points\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point32\n\
# This contains the position of a point in free space(with 32 bits of precision).\n\
# It is recommeded to use Point wherever possible instead of Point32.  \n\
# \n\
# This recommendation is to promote interoperability.  \n\
#\n\
# This message is designed to take up less space when sending\n\
# lots of points at once, as in the case of a PointCloud.  \n\
\n\
float32 x\n\
float32 y\n\
float32 z\n\
";
  }

  static const char* value(const ::irobot_fcpp_simul::ExecuteRectangleFCPPGoal_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::irobot_fcpp_simul::ExecuteRectangleFCPPGoal_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.rectangle_id);
      stream.next(m.operation_type);
      stream.next(m.rectangle);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ExecuteRectangleFCPPGoal_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::irobot_fcpp_simul::ExecuteRectangleFCPPGoal_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::irobot_fcpp_simul::ExecuteRectangleFCPPGoal_<ContainerAllocator>& v)
  {
    s << indent << "rectangle_id: ";
    Printer<int32_t>::stream(s, indent + "  ", v.rectangle_id);
    s << indent << "operation_type: ";
    Printer<int32_t>::stream(s, indent + "  ", v.operation_type);
    s << indent << "rectangle: ";
    s << std::endl;
    Printer< ::geometry_msgs::Polygon_<ContainerAllocator> >::stream(s, indent + "  ", v.rectangle);
  }
};

} // namespace message_operations
} // namespace ros

#endif // IROBOT_FCPP_SIMUL_MESSAGE_EXECUTERECTANGLEFCPPGOAL_H
