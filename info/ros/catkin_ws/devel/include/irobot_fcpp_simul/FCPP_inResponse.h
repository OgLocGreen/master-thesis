// Generated by gencpp from file irobot_fcpp_simul/FCPP_inResponse.msg
// DO NOT EDIT!


#ifndef IROBOT_FCPP_SIMUL_MESSAGE_FCPP_INRESPONSE_H
#define IROBOT_FCPP_SIMUL_MESSAGE_FCPP_INRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/Polygon.h>

namespace irobot_fcpp_simul
{
template <class ContainerAllocator>
struct FCPP_inResponse_
{
  typedef FCPP_inResponse_<ContainerAllocator> Type;

  FCPP_inResponse_()
    : n_defects(0)
    , herr_lat(0.0)
    , herr_proa(0.0)
    , herr_popa(0.0)
    , long_robotx(0.0)
    , long_roboty(0.0)
    , tras_herrx(0.0)
    , tras_herry(0.0)
    , xmin_chapa(0.0)
    , xmax_chapa(0.0)
    , ymin_chapa(0.0)
    , ymax_chapa(0.0)
    , poly_i()
    , zone0()
    , zone90()
    , zone180()
    , zone270()
    , zone_rot()  {
    }
  FCPP_inResponse_(const ContainerAllocator& _alloc)
    : n_defects(0)
    , herr_lat(0.0)
    , herr_proa(0.0)
    , herr_popa(0.0)
    , long_robotx(0.0)
    , long_roboty(0.0)
    , tras_herrx(0.0)
    , tras_herry(0.0)
    , xmin_chapa(0.0)
    , xmax_chapa(0.0)
    , ymin_chapa(0.0)
    , ymax_chapa(0.0)
    , poly_i(_alloc)
    , zone0(_alloc)
    , zone90(_alloc)
    , zone180(_alloc)
    , zone270(_alloc)
    , zone_rot(_alloc)  {
  (void)_alloc;
    }



   typedef int32_t _n_defects_type;
  _n_defects_type n_defects;

   typedef float _herr_lat_type;
  _herr_lat_type herr_lat;

   typedef float _herr_proa_type;
  _herr_proa_type herr_proa;

   typedef float _herr_popa_type;
  _herr_popa_type herr_popa;

   typedef float _long_robotx_type;
  _long_robotx_type long_robotx;

   typedef float _long_roboty_type;
  _long_roboty_type long_roboty;

   typedef float _tras_herrx_type;
  _tras_herrx_type tras_herrx;

   typedef float _tras_herry_type;
  _tras_herry_type tras_herry;

   typedef float _xmin_chapa_type;
  _xmin_chapa_type xmin_chapa;

   typedef float _xmax_chapa_type;
  _xmax_chapa_type xmax_chapa;

   typedef float _ymin_chapa_type;
  _ymin_chapa_type ymin_chapa;

   typedef float _ymax_chapa_type;
  _ymax_chapa_type ymax_chapa;

   typedef  ::geometry_msgs::Polygon_<ContainerAllocator>  _poly_i_type;
  _poly_i_type poly_i;

   typedef  ::geometry_msgs::Polygon_<ContainerAllocator>  _zone0_type;
  _zone0_type zone0;

   typedef  ::geometry_msgs::Polygon_<ContainerAllocator>  _zone90_type;
  _zone90_type zone90;

   typedef  ::geometry_msgs::Polygon_<ContainerAllocator>  _zone180_type;
  _zone180_type zone180;

   typedef  ::geometry_msgs::Polygon_<ContainerAllocator>  _zone270_type;
  _zone270_type zone270;

   typedef  ::geometry_msgs::Polygon_<ContainerAllocator>  _zone_rot_type;
  _zone_rot_type zone_rot;





  typedef boost::shared_ptr< ::irobot_fcpp_simul::FCPP_inResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::irobot_fcpp_simul::FCPP_inResponse_<ContainerAllocator> const> ConstPtr;

}; // struct FCPP_inResponse_

typedef ::irobot_fcpp_simul::FCPP_inResponse_<std::allocator<void> > FCPP_inResponse;

typedef boost::shared_ptr< ::irobot_fcpp_simul::FCPP_inResponse > FCPP_inResponsePtr;
typedef boost::shared_ptr< ::irobot_fcpp_simul::FCPP_inResponse const> FCPP_inResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::irobot_fcpp_simul::FCPP_inResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::irobot_fcpp_simul::FCPP_inResponse_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::irobot_fcpp_simul::FCPP_inResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::irobot_fcpp_simul::FCPP_inResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::irobot_fcpp_simul::FCPP_inResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::irobot_fcpp_simul::FCPP_inResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::irobot_fcpp_simul::FCPP_inResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::irobot_fcpp_simul::FCPP_inResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::irobot_fcpp_simul::FCPP_inResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "4a6d5622fc972a91f6327482e4705f63";
  }

  static const char* value(const ::irobot_fcpp_simul::FCPP_inResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x4a6d5622fc972a91ULL;
  static const uint64_t static_value2 = 0xf6327482e4705f63ULL;
};

template<class ContainerAllocator>
struct DataType< ::irobot_fcpp_simul::FCPP_inResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "irobot_fcpp_simul/FCPP_inResponse";
  }

  static const char* value(const ::irobot_fcpp_simul::FCPP_inResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::irobot_fcpp_simul::FCPP_inResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n\
int32 n_defects\n\
\n\
\n\
float32 herr_lat\n\
float32 herr_proa\n\
float32 herr_popa\n\
\n\
\n\
float32 long_robotx\n\
float32 long_roboty\n\
float32 tras_herrx\n\
float32 tras_herry\n\
\n\
\n\
float32 xmin_chapa\n\
float32 xmax_chapa\n\
float32 ymin_chapa\n\
float32 ymax_chapa\n\
\n\
\n\
geometry_msgs/Polygon poly_i\n\
\n\
\n\
geometry_msgs/Polygon zone0\n\
geometry_msgs/Polygon zone90\n\
geometry_msgs/Polygon zone180\n\
geometry_msgs/Polygon zone270\n\
\n\
\n\
\n\
geometry_msgs/Polygon zone_rot\n\
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

  static const char* value(const ::irobot_fcpp_simul::FCPP_inResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::irobot_fcpp_simul::FCPP_inResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.n_defects);
      stream.next(m.herr_lat);
      stream.next(m.herr_proa);
      stream.next(m.herr_popa);
      stream.next(m.long_robotx);
      stream.next(m.long_roboty);
      stream.next(m.tras_herrx);
      stream.next(m.tras_herry);
      stream.next(m.xmin_chapa);
      stream.next(m.xmax_chapa);
      stream.next(m.ymin_chapa);
      stream.next(m.ymax_chapa);
      stream.next(m.poly_i);
      stream.next(m.zone0);
      stream.next(m.zone90);
      stream.next(m.zone180);
      stream.next(m.zone270);
      stream.next(m.zone_rot);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct FCPP_inResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::irobot_fcpp_simul::FCPP_inResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::irobot_fcpp_simul::FCPP_inResponse_<ContainerAllocator>& v)
  {
    s << indent << "n_defects: ";
    Printer<int32_t>::stream(s, indent + "  ", v.n_defects);
    s << indent << "herr_lat: ";
    Printer<float>::stream(s, indent + "  ", v.herr_lat);
    s << indent << "herr_proa: ";
    Printer<float>::stream(s, indent + "  ", v.herr_proa);
    s << indent << "herr_popa: ";
    Printer<float>::stream(s, indent + "  ", v.herr_popa);
    s << indent << "long_robotx: ";
    Printer<float>::stream(s, indent + "  ", v.long_robotx);
    s << indent << "long_roboty: ";
    Printer<float>::stream(s, indent + "  ", v.long_roboty);
    s << indent << "tras_herrx: ";
    Printer<float>::stream(s, indent + "  ", v.tras_herrx);
    s << indent << "tras_herry: ";
    Printer<float>::stream(s, indent + "  ", v.tras_herry);
    s << indent << "xmin_chapa: ";
    Printer<float>::stream(s, indent + "  ", v.xmin_chapa);
    s << indent << "xmax_chapa: ";
    Printer<float>::stream(s, indent + "  ", v.xmax_chapa);
    s << indent << "ymin_chapa: ";
    Printer<float>::stream(s, indent + "  ", v.ymin_chapa);
    s << indent << "ymax_chapa: ";
    Printer<float>::stream(s, indent + "  ", v.ymax_chapa);
    s << indent << "poly_i: ";
    s << std::endl;
    Printer< ::geometry_msgs::Polygon_<ContainerAllocator> >::stream(s, indent + "  ", v.poly_i);
    s << indent << "zone0: ";
    s << std::endl;
    Printer< ::geometry_msgs::Polygon_<ContainerAllocator> >::stream(s, indent + "  ", v.zone0);
    s << indent << "zone90: ";
    s << std::endl;
    Printer< ::geometry_msgs::Polygon_<ContainerAllocator> >::stream(s, indent + "  ", v.zone90);
    s << indent << "zone180: ";
    s << std::endl;
    Printer< ::geometry_msgs::Polygon_<ContainerAllocator> >::stream(s, indent + "  ", v.zone180);
    s << indent << "zone270: ";
    s << std::endl;
    Printer< ::geometry_msgs::Polygon_<ContainerAllocator> >::stream(s, indent + "  ", v.zone270);
    s << indent << "zone_rot: ";
    s << std::endl;
    Printer< ::geometry_msgs::Polygon_<ContainerAllocator> >::stream(s, indent + "  ", v.zone_rot);
  }
};

} // namespace message_operations
} // namespace ros

#endif // IROBOT_FCPP_SIMUL_MESSAGE_FCPP_INRESPONSE_H