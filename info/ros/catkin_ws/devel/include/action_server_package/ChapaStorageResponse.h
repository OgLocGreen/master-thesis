// Generated by gencpp from file action_server_package/ChapaStorageResponse.msg
// DO NOT EDIT!


#ifndef ACTION_SERVER_PACKAGE_MESSAGE_CHAPASTORAGERESPONSE_H
#define ACTION_SERVER_PACKAGE_MESSAGE_CHAPASTORAGERESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <geometry_msgs/Point.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Point.h>

namespace action_server_package
{
template <class ContainerAllocator>
struct ChapaStorageResponse_
{
  typedef ChapaStorageResponse_<ContainerAllocator> Type;

  ChapaStorageResponse_()
    : long_chapa(0.0)
    , width_chapa(0.0)
    , coordA()
    , coordB()
    , coordC()
    , coordD()
    , number_of_chapas(0)  {
    }
  ChapaStorageResponse_(const ContainerAllocator& _alloc)
    : long_chapa(0.0)
    , width_chapa(0.0)
    , coordA(_alloc)
    , coordB(_alloc)
    , coordC(_alloc)
    , coordD(_alloc)
    , number_of_chapas(0)  {
  (void)_alloc;
    }



   typedef float _long_chapa_type;
  _long_chapa_type long_chapa;

   typedef float _width_chapa_type;
  _width_chapa_type width_chapa;

   typedef  ::geometry_msgs::Point_<ContainerAllocator>  _coordA_type;
  _coordA_type coordA;

   typedef  ::geometry_msgs::Point_<ContainerAllocator>  _coordB_type;
  _coordB_type coordB;

   typedef  ::geometry_msgs::Point_<ContainerAllocator>  _coordC_type;
  _coordC_type coordC;

   typedef  ::geometry_msgs::Point_<ContainerAllocator>  _coordD_type;
  _coordD_type coordD;

   typedef int32_t _number_of_chapas_type;
  _number_of_chapas_type number_of_chapas;





  typedef boost::shared_ptr< ::action_server_package::ChapaStorageResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::action_server_package::ChapaStorageResponse_<ContainerAllocator> const> ConstPtr;

}; // struct ChapaStorageResponse_

typedef ::action_server_package::ChapaStorageResponse_<std::allocator<void> > ChapaStorageResponse;

typedef boost::shared_ptr< ::action_server_package::ChapaStorageResponse > ChapaStorageResponsePtr;
typedef boost::shared_ptr< ::action_server_package::ChapaStorageResponse const> ChapaStorageResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::action_server_package::ChapaStorageResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::action_server_package::ChapaStorageResponse_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::action_server_package::ChapaStorageResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::action_server_package::ChapaStorageResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::action_server_package::ChapaStorageResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::action_server_package::ChapaStorageResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::action_server_package::ChapaStorageResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::action_server_package::ChapaStorageResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::action_server_package::ChapaStorageResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "5aae4cddd2d81a64c074397519c7dd87";
  }

  static const char* value(const ::action_server_package::ChapaStorageResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x5aae4cddd2d81a64ULL;
  static const uint64_t static_value2 = 0xc074397519c7dd87ULL;
};

template<class ContainerAllocator>
struct DataType< ::action_server_package::ChapaStorageResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "action_server_package/ChapaStorageResponse";
  }

  static const char* value(const ::action_server_package::ChapaStorageResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::action_server_package::ChapaStorageResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float32 long_chapa\n\
float32 width_chapa\n\
\n\
geometry_msgs/Point coordA\n\
geometry_msgs/Point coordB\n\
geometry_msgs/Point coordC\n\
geometry_msgs/Point coordD\n\
\n\
int32 number_of_chapas\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
";
  }

  static const char* value(const ::action_server_package::ChapaStorageResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::action_server_package::ChapaStorageResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.long_chapa);
      stream.next(m.width_chapa);
      stream.next(m.coordA);
      stream.next(m.coordB);
      stream.next(m.coordC);
      stream.next(m.coordD);
      stream.next(m.number_of_chapas);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ChapaStorageResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::action_server_package::ChapaStorageResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::action_server_package::ChapaStorageResponse_<ContainerAllocator>& v)
  {
    s << indent << "long_chapa: ";
    Printer<float>::stream(s, indent + "  ", v.long_chapa);
    s << indent << "width_chapa: ";
    Printer<float>::stream(s, indent + "  ", v.width_chapa);
    s << indent << "coordA: ";
    s << std::endl;
    Printer< ::geometry_msgs::Point_<ContainerAllocator> >::stream(s, indent + "  ", v.coordA);
    s << indent << "coordB: ";
    s << std::endl;
    Printer< ::geometry_msgs::Point_<ContainerAllocator> >::stream(s, indent + "  ", v.coordB);
    s << indent << "coordC: ";
    s << std::endl;
    Printer< ::geometry_msgs::Point_<ContainerAllocator> >::stream(s, indent + "  ", v.coordC);
    s << indent << "coordD: ";
    s << std::endl;
    Printer< ::geometry_msgs::Point_<ContainerAllocator> >::stream(s, indent + "  ", v.coordD);
    s << indent << "number_of_chapas: ";
    Printer<int32_t>::stream(s, indent + "  ", v.number_of_chapas);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ACTION_SERVER_PACKAGE_MESSAGE_CHAPASTORAGERESPONSE_H
