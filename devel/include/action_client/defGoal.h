// Generated by gencpp from file action_client/defGoal.msg
// DO NOT EDIT!


#ifndef ACTION_CLIENT_MESSAGE_DEFGOAL_H
#define ACTION_CLIENT_MESSAGE_DEFGOAL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace action_client
{
template <class ContainerAllocator>
struct defGoal_
{
  typedef defGoal_<ContainerAllocator> Type;

  defGoal_()
    : x(0.0)
    , y(0.0)
    , z(0.0)
    , id(0)  {
    }
  defGoal_(const ContainerAllocator& _alloc)
    : x(0.0)
    , y(0.0)
    , z(0.0)
    , id(0)  {
  (void)_alloc;
    }



   typedef double _x_type;
  _x_type x;

   typedef double _y_type;
  _y_type y;

   typedef double _z_type;
  _z_type z;

   typedef int8_t _id_type;
  _id_type id;





  typedef boost::shared_ptr< ::action_client::defGoal_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::action_client::defGoal_<ContainerAllocator> const> ConstPtr;

}; // struct defGoal_

typedef ::action_client::defGoal_<std::allocator<void> > defGoal;

typedef boost::shared_ptr< ::action_client::defGoal > defGoalPtr;
typedef boost::shared_ptr< ::action_client::defGoal const> defGoalConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::action_client::defGoal_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::action_client::defGoal_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::action_client::defGoal_<ContainerAllocator1> & lhs, const ::action_client::defGoal_<ContainerAllocator2> & rhs)
{
  return lhs.x == rhs.x &&
    lhs.y == rhs.y &&
    lhs.z == rhs.z &&
    lhs.id == rhs.id;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::action_client::defGoal_<ContainerAllocator1> & lhs, const ::action_client::defGoal_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace action_client

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::action_client::defGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::action_client::defGoal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::action_client::defGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::action_client::defGoal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::action_client::defGoal_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::action_client::defGoal_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::action_client::defGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "4e18d1f56409b7448d42973b1858ae79";
  }

  static const char* value(const ::action_client::defGoal_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x4e18d1f56409b744ULL;
  static const uint64_t static_value2 = 0x8d42973b1858ae79ULL;
};

template<class ContainerAllocator>
struct DataType< ::action_client::defGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "action_client/defGoal";
  }

  static const char* value(const ::action_client::defGoal_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::action_client::defGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"#goal\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"int8 id\n"
;
  }

  static const char* value(const ::action_client::defGoal_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::action_client::defGoal_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.x);
      stream.next(m.y);
      stream.next(m.z);
      stream.next(m.id);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct defGoal_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::action_client::defGoal_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::action_client::defGoal_<ContainerAllocator>& v)
  {
    s << indent << "x: ";
    Printer<double>::stream(s, indent + "  ", v.x);
    s << indent << "y: ";
    Printer<double>::stream(s, indent + "  ", v.y);
    s << indent << "z: ";
    Printer<double>::stream(s, indent + "  ", v.z);
    s << indent << "id: ";
    Printer<int8_t>::stream(s, indent + "  ", v.id);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ACTION_CLIENT_MESSAGE_DEFGOAL_H
