// Generated by gencpp from file irobot_fcpp_simul/ExecuteRectangleFCPPResult.msg
// DO NOT EDIT!


#ifndef IROBOT_FCPP_SIMUL_MESSAGE_EXECUTERECTANGLEFCPPRESULT_H
#define IROBOT_FCPP_SIMUL_MESSAGE_EXECUTERECTANGLEFCPPRESULT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <geometry_msgs/Point.h>

namespace irobot_fcpp_simul
{
template <class ContainerAllocator>
struct ExecuteRectangleFCPPResult_
{
  typedef ExecuteRectangleFCPPResult_<ContainerAllocator> Type;

  ExecuteRectangleFCPPResult_()
    : recorrido(false)
    , path()  {
    }
  ExecuteRectangleFCPPResult_(const ContainerAllocator& _alloc)
    : recorrido(false)
    , path(_alloc)  {
  (void)_alloc;
    }



   typedef uint8_t _recorrido_type;
  _recorrido_type recorrido;

   typedef std::vector< ::geometry_msgs::Point_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::geometry_msgs::Point_<ContainerAllocator> >::other >  _path_type;
  _path_type path;





  typedef boost::shared_ptr< ::irobot_fcpp_simul::ExecuteRectangleFCPPResult_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::irobot_fcpp_simul::ExecuteRectangleFCPPResult_<ContainerAllocator> const> ConstPtr;

}; // struct ExecuteRectangleFCPPResult_

typedef ::irobot_fcpp_simul::ExecuteRectangleFCPPResult_<std::allocator<void> > ExecuteRectangleFCPPResult;

typedef boost::shared_ptr< ::irobot_fcpp_simul::ExecuteRectangleFCPPResult > ExecuteRectangleFCPPResultPtr;
typedef boost::shared_ptr< ::irobot_fcpp_simul::ExecuteRectangleFCPPResult const> ExecuteRectangleFCPPResultConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::irobot_fcpp_simul::ExecuteRectangleFCPPResult_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::irobot_fcpp_simul::ExecuteRectangleFCPPResult_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace irobot_fcpp_simul

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg', '/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'irobot_fcpp_simul': ['/home/irobot/nav_insp_ws/src/inspection/irobot_fcpp_simul/msg', '/home/irobot/nav_insp_ws/devel/share/irobot_fcpp_simul/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::irobot_fcpp_simul::ExecuteRectangleFCPPResult_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::irobot_fcpp_simul::ExecuteRectangleFCPPResult_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::irobot_fcpp_simul::ExecuteRectangleFCPPResult_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::irobot_fcpp_simul::ExecuteRectangleFCPPResult_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::irobot_fcpp_simul::ExecuteRectangleFCPPResult_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::irobot_fcpp_simul::ExecuteRectangleFCPPResult_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::irobot_fcpp_simul::ExecuteRectangleFCPPResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "5d269c950010827f1cca5ca79fa4c172";
  }

  static const char* value(const ::irobot_fcpp_simul::ExecuteRectangleFCPPResult_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x5d269c950010827fULL;
  static const uint64_t static_value2 = 0x1cca5ca79fa4c172ULL;
};

template<class ContainerAllocator>
struct DataType< ::irobot_fcpp_simul::ExecuteRectangleFCPPResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "irobot_fcpp_simul/ExecuteRectangleFCPPResult";
  }

  static const char* value(const ::irobot_fcpp_simul::ExecuteRectangleFCPPResult_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::irobot_fcpp_simul::ExecuteRectangleFCPPResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
# Define the result\n\
bool recorrido\n\
geometry_msgs/Point[] path\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
";
  }

  static const char* value(const ::irobot_fcpp_simul::ExecuteRectangleFCPPResult_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::irobot_fcpp_simul::ExecuteRectangleFCPPResult_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.recorrido);
      stream.next(m.path);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ExecuteRectangleFCPPResult_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::irobot_fcpp_simul::ExecuteRectangleFCPPResult_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::irobot_fcpp_simul::ExecuteRectangleFCPPResult_<ContainerAllocator>& v)
  {
    s << indent << "recorrido: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.recorrido);
    s << indent << "path[]" << std::endl;
    for (size_t i = 0; i < v.path.size(); ++i)
    {
      s << indent << "  path[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::geometry_msgs::Point_<ContainerAllocator> >::stream(s, indent + "    ", v.path[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // IROBOT_FCPP_SIMUL_MESSAGE_EXECUTERECTANGLEFCPPRESULT_H
