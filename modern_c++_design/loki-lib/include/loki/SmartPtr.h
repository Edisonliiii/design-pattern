#ifndef LOKI_SMARTPTR_INC_
#define LOKI_SMARTPTR_INC_

#include <functional>
#include <stdexcept>
#include <cassert>
#include <string>

#if !defined(_MSC_VER)
#  if defined(__sparc__)
#    include <inttypes.h>
#  else
#    include <stdint.h>
# endif
#endif

#if defined(_MSC_VER) || defined(__GNUC__)
#define LOKI_ENABLE_FRIEND_TEMPLATE_TEMPLATE_PARAMETER_WORKAROUND
#endif

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4355)
#endif

/* [设计理念]
1. only keep the following as member functions:
   a. c'tor
   b. d'tor
   c. operator =
   d. operator ->
   因为想防止出现指针所指的obj内部有和smart ptr本身member function重名的函数
   会容易出错 可读性降低
2. Essential Components
   a. ownership
      - deep copy
      - copy on write
      - reference counting
      - reference linking
      - destructive copy
   b. address-of operator
   c. implicit coversion to raw pointer
*/

namespace Loki
{
  ////////////////////////////////////////////////////////////////////////////////
  ///  \class HeapStorage
  ///
  ///  \ingroup  SmartPointerStorageGroup
  ///  Implementation of the StoragePolicy used by SmartPtr.  Uses explicit call
  ///   to T's destructor followed by call to free.
  ////////////////////////////////////////////////////////////////////////////////
  template <class T>
  class HeapStorage
  {
  public:
    typedef T* StoredType;       // the type of pointee_ obj
    typedef T* InitPointerType;  // declare OwnershipPolicy
    typedef T* PointerType;      // return by operator ->
    typedef T& ReferenceType;    // return by operator *
  protected:
    HeapStorage() : pointee_(Default()) {}

    HeapStorage(const HeapStorage&) : pointee_(nullptr) {}

    template <class U>
    HeapStorage(const HeapStorage<U>&) : pointee_(nullptr) {}

    explicit HeapStorage(const StoredType& p) : pointee_(p) {}

    PointerType operator->() const { return pointee_; }
    ReferenceType operator*() const { return *pointee_; }

    void Swap(HeapStorage& rhs) { std::swap(pointee_, rhs.pointee_); }

    //Accessors
    template<class F>
    friend typename HeapStorage<F>::PointerType GetImpl(const HeapStorage<F>& sp);

    template<class F>
    friend typename HeapStorage<F>::StoredType& GetImplRef(const HeapStorage<F>& sp);

    template<class F>
    friend typename HeapStorage<F>::StoredType& GetImplRef(HeapStorage<F>& sp);

    // Destroys the data stored
    // d'tor might be taken over by the OwnershipPolicy
    void Destory()
    {
      if (pointee_ != nullptr)
      {
        pointee_->~T();
        ::free(pointee_);
      }
    }

    // Default value to init the pointer
    static StoredType Default() { return nullptr; }

  private:
    // data member
    StoredType pointee_;
  };

  template<class F>
  inline typename HeapStorage<F>::PointerType GetImpl(const HeapStorage<F>& sp) { return sp.pointee_; }

  template<class F>
  inline const typename HeapStorage<F>::StoredType& GetImplRef(const HeapStorage<F>& sp) { return sp.pointee_; }

  template<class F>
  inline typename HeapStorage<F>::StoredType& GetImplRef(HeapStorage<F>& sp) { return sp.pointee_; }

  ////////////////////////////////////////////////////////////////////////////////
  ///  \class DefaultSPStorage (used for POD)
  ///
  ///  \ingroup  SmartPointerStorageGroup
  ///  Implementation of the StoragePolicy used by SmartPtr
  ////////////////////////////////////////////////////////////////////////////////
  template <class T>
  class DefaultSPStorage
  {
  public:
    typedef T* StoredType;    // the type of the pointee_ object
    typedef T* InitPointerType; /// type used to declare OwnershipPolicy type.
    typedef T* PointerType;   // type returned by operator->
    typedef T& ReferenceType; // type returned by operator*
  private:
    StoredType pointee_;
  protected:
    DefaultSPStorage() : pointee_(Default()) {}

    DefaultSPStorage(const DefaultSPStorage&) : pointee_(nullptr) {}

    template<class U>
    DefaultSPStorage(const DefaultSPStorage<U>) : pointee_(nullptr) {}

    explicit DefaultSPStorage(const StoredType& p) : pointee_(p) {}

    PointerType operator->() const { return pointee_; }

    ReferenceType operator*() const { return *pointee_; }

    void Swap(DefaultSPStorage& rhs)
    {
      std::swap(pointee_, rhs.pointee_);
    }

    // Accessors
    template <class F>
    friend typename DefaultSPStorage<F>::PointerType GetImpl(const DefaultSPStorage<F>& sp);

    template <class F>
    friend const typename DefaultSPStorage<F>::StoredType& GetImplRef(const DefaultSPStorage<F>& sp);

    template <class F>
    friend typename DefaultSPStorage<F>::StoredType& GetImplRef(DefaultSPStorage<F>& sp);

    void Destroy()
    {
      delete pointee_;
    }

    static StoredType Default() { return 0; }
  }; // DefaultSPStorage

  template <class T>
  inline typename DefaultSPStorage<T>::PointerType GetImpl(const DefaultSPStorage<T>& sp) { return sp.pointee_; }

  template <class T>
  inline const typename DefaultSPStorage<T>::StoredType& GetImplRef(const DefaultSPStorage<T>& sp) { return sp.pointee_; }

  template <class T>
  inline typename DefaultSPStorage<T>::StoredType& GetImplRef(DefaultSPStorage<T>& sp) { return sp.pointee_; }

  template<class T>
  class Locker
  {
  private: // disable some essencial functions
    Locker(void);
    Locker& operator = (const Locker&);
    T* pointee_;
  public:
    explicit Locker(const T* p) : pointee_(const_cast<T*>(p))
    {
      if (pointee_ != nullptr)
      {
        pointee_->Lock();
      }
    }
    ~Locker(void)
    {
      if (pointee_ != nullptr)
      {
        pointee_->Unlock();
      }
    }
    operator T* () { return pointee_; }
    T* operator->() { return pointee_; }
  }; // Locker

  template<class T>
  class LockedStorage
  {
  public:
    typedef T* StoredType;            // type of pointee obj
    typedef T* InitPointerType;       // type used to declare ownershippolicy type
    typedef Locker<T> PointerType;    // type returned by operator->
    typedef T& ReferenceType;
  protected:
    LockedStorage() : pointee_(Default()) {}
    ~LockedStorage(void) {}
    LockedStorage(const LockedStorage&) : pointee_(nullptr) {}
    explicit LockedStorage(const StoredType& p) : pointee_(p) {}

    PointerType operator->() const { return Locker<T>(pointee_); }
    void Swap(LockedStorage& rhs)
    {
      std::swap(pointee_, rhs.pointee_);
    }

    // Accessors
    template<class F>
    friend typename LockedStorage<F>::InitPointerType GetImpl(const LockedStorage<F>& sp);

    template<class F>
    friend typename LockedStorage<F>::StoredType& GetImplRef(const LockedStorage<F>& sp);

    template<class F>
    friend typename LockedStorage<F>::StoredType& GetImplRef(LockedStorage<F>& sp);

    void Destroy()
    {
      delete pointee_;
    }
    // default val to init the obj
    static StoredType Default()
    {
      return nullptr;
    }
  private:
    ReferenceType operator*(); // disable
    StoredType pointee_;
  }; // LockedStorage

  template<class T>
  inline typename LockedStorage<T>::InitPointerType GetImpl(const LockedStorage<T>& sp)
  {
    return sp.pointee_;
  }

  template<class T>
  inline typename LockedStorage<T>::StoredType& GetImplRef(const LockedStorage<T>& sp)
  {
    return sp.pointee_;
  }

  template<class T>
  inline typename LockedStorage<T>::StoredType& GetImplRef(LockedStorage<T>& sp)
  {
    return sp.pointee_;
  }

  ////////////////////////////////////////////////////////////////////////////////
  ///  \struct DeepCopy
  ///
  ///  \ingroup  SmartPointerOwnershipGroup
  ///  Implementation of the OwnershipPolicy used by SmartPtr
  ///  Implements deep copy semantics, assumes existence of a Clone() member
  ///  function of the pointee type. DeepCopy is not compatible with ArrayStorage
  ///  DeepCopy::Clone will only copy the first element in the array and won't
  ///  know the size of the array. Even if it did know the size, it would need to
  ///  use array new to safely work the array delete operator in ArrayStorage, but
  ///  array new will not copy the elements in the source array since it calls the
  ///  default constructor for each array element.
  ////////////////////////////////////////////////////////////////////////////////

  template<class P>
  struct DeepCopy
  {
  protected:
    DeepCopy() {}

    template<class P1>
    DeepCopy(const DeepCopy<P1>&) {}

    static P Clone(const P& val) { return val->Clone(); }

    static bool Release(const P& val) { return true; }

    static void Swap(DeepCopy&) {}

    enum { destructiveCopy = false };

  };// DeepCopy

////////////////////////////////////////////////////////////////////////////////
///  \class RefCounted
///
///  \ingroup  SmartPointerOwnershipGroup
///  Implementation of the OwnershipPolicy used by SmartPtr
///  Provides a classic external reference counting implementation
////////////////////////////////////////////////////////////////////////////////
  template <class P>
  class RefCounted
  {
  private:
    uintptr_t* pCount_;
  protected:
    RefCounted() : pCount_(static_cast<uintptr_t*>(SmallObject<>::operator new(sizeof(uintptr_t))))
    {
      assert(pCount_ != 0);
      *pCount_ = 1;
    }

    RefCounted(const RefCounted& rhs) : pCount_(rhs.pCount_) {}

    template<typename P1>
    RefCounted(const RefCounted<P1>& rhs) : pCount_(reinterpret_cast<const RefCounted&>(rhs).pCount_) {}

    P Clone(const P& val)
    {
      ++* pCount_;
      return val;
    }

    bool Release(const P&)
    {
      if (!-- * pCount_)
      {
        SmallObject<>::operator delete(pCount_, sizeof(uintptr_t));
        pCount_ = nullptr;
        return true;
      }
      return false;
    }

    void Swap(RefCounted& rhs)
    {
      std::swap(pCount_, rhs.pCount_);
    }

    enum { destructiveCopy = false };
  }; // RefCounted

  namespace Private
  {
    ////////////////////////////////////////////////////////////////////////////////
    ///  \class DeleteArrayBase
    ///
    ///  \ingroup  StrongPointerDeleteGroup
    ///  Base class used only by the DeleteArray policy class.  This stores the
    ///   number of elements in an array of shared objects.
    ////////////////////////////////////////////////////////////////////////////////

    class DeleteArrayBase
    {
    public:
      inline size_t GetArrayCount(void) const { return m_itemCount; }
    protected:
      DeleteArrayBase(void) : m_itemCount(0) {}
      explicit DeleteArrayBase(size_t itemCount) : m_itemCount(itemCount) {}
      DeleteArrayBase(const DeleteArrayBase& that) : m_itemCount(that.m_itemCount) {}

      void Swap(DeleteArrayBase& rhs);
      void OnInit(const void* p) const;
      void OnCheckRange(size_t index) const;
    private:
      size_t m_itemCount;
    }; // DeleteArrayBase
  }; // Private

  ////////////////////////////////////////////////////////////////////////////////
  ///  \class ArrayStorage
  ///
  ///  \ingroup  SmartPointerStorageGroup
  ///  Implementation of the ArrayStorage used by SmartPtr
  ///  This assumes the pointer points to the zeroth element in an array, and uses
  ///  the array-delete operator to deconstruct and deallocate the array. DeepCopy
  ///  is not compatible with ArrayStorage DeepCopy::Clone will only copy the first
  ///  element in the array and won't know the size of the array. Even if it did
  ///  know the size, it would need to use array new to safely work the array
  ///  delete operator in ArrayStorage, but array new will not copy the elements
  ///  in the source array since it calls the default constructor for each element.
  ////////////////////////////////////////////////////////////////////////////////

  template <class T>
  class ArrayStorage : public ::Loki::Private::DeleteArrayBase
  {
  public:
    typedef T* StoredType;
    typedef T* InitPointerType;
    typedef T* PointerType;
    typedef T& ReferenceType;
  private:
    StoredType pointee_;
  protected:
    // Default value to initalize the pointer
    static StoredType Default() { return nullptr; }
    // Destroy the data stored
    void Destroy() { delete[] pointee_; }
    ArrayStorage() : DeleteArrayBase(), pointee_(Default()) {}
    // the storage policy doesn't initialize the stored pointer
    // which will be initialized by the ownershippolicy's clone fn
    ArrayStorage(const ArrayStorage& that) : DeleteArrayBase(that), pointee_(nullptr) {}

    template <class U>
    ArrayStorage(const ArrayStorage<U>& that) : DeleteArrayBase(that), pointee_(nullptr) {}

    ArrayStorage(const StoredType& p, size_t count) : DeleteArrayBase(count), pointee_(p) {}

    PointerType operator->() const { return pointee_; }
    ReferenceType operator*() const { return *pointee_; }

    void Swap(ArrayStorage& rhs)
    {
      DeleteArrayBase::Swap(rhs);
      ::std::swap(pointee_, rhs.pointee_);
    }

    // Accessors
    template<class F>
    friend typename ArrayStorage<F>::PointerType GetImpl(const ArrayStorage<F>& sp);

    template<class F>
    friend const typename ArrayStorage<F>::StoredType& GetImplRef(const ArrayStorage<F>& sp);

    template<class F>
    friend typename ArrayStorage<F>::StoredType& GetImplRef(ArrayStorage<F>& sp);

  }; // ArrayStorage

  template <class T>
  inline typename ArrayStorage<T>::PointerType GetImpl(const ArrayStorage<T>& sp) { return sp.pointee_; }

  template<class T>
  inline const typename ArrayStorage<T>::StoredType& GetImplRef(const ArrayStorage<T>& sp) { return sp.pointee_; }

  template<class T>
  inline typename ArrayStorage<T>::StoredType& GetImplRef(ArrayStorage<T>& sp) { return sp.pointee_; }

  ////////////////////////////////////////////////////////////////////////////////
  ///  \class RefCounted
  ///
  ///  \ingroup  SmartPointerOwnershipGroup
  ///  Implementation of the OwnershipPolicy used by SmartPtr
  ///  Provides a classic external reference counting implementation
  ////////////////////////////////////////////////////////////////////////////////

  template <class P>
  class RefCounted
  {
  private:
    uintptr_t* pCount_;
  protected:
    RefCounted() : pCount_(static_cast<uintptr_t*>(SmallObject<>::opeartor new(sizeof(uintptr_t))))
    {
      assert(pCount_ != 0);
      *pCount_ = 1;
    }

  }; // RefCounted


}; // namespace Loki

#endif




////////////////////////////////////////////////////////////////////////////////
// class template SmartPtr (declaration)
// The reason for all the fuss above
////////////////////////////////////////////////////////////////////////////////

// template
// <
//   typename T,
//   template <class> class OwnershipPolicy = RefCounted,
// >
