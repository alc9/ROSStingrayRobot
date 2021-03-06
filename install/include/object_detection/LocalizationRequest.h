// Generated by gencpp from file object_detection/LocalizationRequest.msg
// DO NOT EDIT!


#ifndef OBJECT_DETECTION_MESSAGE_LOCALIZATIONREQUEST_H
#define OBJECT_DETECTION_MESSAGE_LOCALIZATIONREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace object_detection
{
template <class ContainerAllocator>
struct LocalizationRequest_
{
  typedef LocalizationRequest_<ContainerAllocator> Type;

  LocalizationRequest_()
    {
    }
  LocalizationRequest_(const ContainerAllocator& _alloc)
    {
  (void)_alloc;
    }







  typedef boost::shared_ptr< ::object_detection::LocalizationRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::object_detection::LocalizationRequest_<ContainerAllocator> const> ConstPtr;

}; // struct LocalizationRequest_

typedef ::object_detection::LocalizationRequest_<std::allocator<void> > LocalizationRequest;

typedef boost::shared_ptr< ::object_detection::LocalizationRequest > LocalizationRequestPtr;
typedef boost::shared_ptr< ::object_detection::LocalizationRequest const> LocalizationRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::object_detection::LocalizationRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::object_detection::LocalizationRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


} // namespace object_detection

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::object_detection::LocalizationRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::object_detection::LocalizationRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::object_detection::LocalizationRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::object_detection::LocalizationRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::object_detection::LocalizationRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::object_detection::LocalizationRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::object_detection::LocalizationRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d41d8cd98f00b204e9800998ecf8427e";
  }

  static const char* value(const ::object_detection::LocalizationRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd41d8cd98f00b204ULL;
  static const uint64_t static_value2 = 0xe9800998ecf8427eULL;
};

template<class ContainerAllocator>
struct DataType< ::object_detection::LocalizationRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "object_detection/LocalizationRequest";
  }

  static const char* value(const ::object_detection::LocalizationRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::object_detection::LocalizationRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n"
;
  }

  static const char* value(const ::object_detection::LocalizationRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::object_detection::LocalizationRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream&, T)
    {}

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct LocalizationRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::object_detection::LocalizationRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream&, const std::string&, const ::object_detection::LocalizationRequest_<ContainerAllocator>&)
  {}
};

} // namespace message_operations
} // namespace ros

#endif // OBJECT_DETECTION_MESSAGE_LOCALIZATIONREQUEST_H
