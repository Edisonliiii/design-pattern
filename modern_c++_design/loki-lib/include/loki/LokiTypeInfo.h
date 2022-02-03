#ifndef LOKI_LOKITYPEINFO_INC_
#define LOKI_LOKITYPEINFO_INC_

#include <typeinfo>
#include <cassert>
#include <loki/Typelist.h>

namespace Loki
{
  // comparable wrapper over std::type_info
  class TypeInfo
  {
  private:
    const std::type_info* pInfo_;
  public:
    // c'tor needed for containers
    TypeInfo();
    // non-explicit
    TypeInfo(const std::type_info&);

    // Access for the wrapped std::type_info
    const std::type_info& Get() const;
    // Compatibility functions
    // useful when we want them sorted in a list of object accoridnt to its type
    bool before(const TypeInfo& rhs) const;
    const char* name() const;
  }; //TypeInfo

  // Implementation
  inline TypeInfo::TypeInfo()
  {
    class Nil {};
    pInfo_ = &typeid(Nil);
    assert(pInfo_);
  }

  inline TypeInfo::TypeInfo(const std::type_info& ti) : pInfo_(&ti) { assert(pInfo_); }

  inline bool TypeInfo::before(const TypeInfo& rhs) const
  {
    assert(pInfo_);
    return pInfo_->before(*rhs.pInfo_) != 0;
  }

  inline const std::type_info& TypeInfo::Get() const
  {
    assert(pInfo_);
    return *pInfo_;
  }

  inline const char* TypeInfo::name() const
  {
    assert(pInfo_);
    return pInfo_->name();
  }

  // comparison operators
  inline bool operator==(const TypeInfo& lhs, const TypeInfo& rhs) { return (lhs.Get() == rhs.Get()) != 0; }

  inline bool operator<(const TypeInfo& lhs, const TypeInfo& rhs)
  {
    return lhs.before(rhs);
  }

  inline bool operator!=(const TypeInfo& lhs, const TypeInfo& rhs)
  {
    return !(lhs == rhs);
  }

  inline bool operator>(const TypeInfo& lhs, const TypeInfo& rhs)
  {
    return rhs < lhs;
  }

  inline bool operator<=(const TypeInfo& lhs, const TypeInfo& rhs)
  {
    return !(lhs > rhs);
  }

  inline bool operator>=(const TypeInfo& lhs, const TypeInfo& rhs)
  {
    return !(lhs < rhs);
  }

}; // Loki

#endif