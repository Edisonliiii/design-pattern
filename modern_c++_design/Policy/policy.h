/*
  image OpNewCreator, MallocCreator and PrototypeCreator
  are three diff creator implementation,

  the common point of them is that they all have Create() method

  Policy 这种设计模式下 最好使用non-virtual protected d'tor
*/
// template member funciton
template <class T>
struct OpNewCreator
{
  static T* Create()
  {
    return new T;
  }
};

template <class T>
struct MallocCreator
{
  static T* Create()
  {
    void* buf = std::malloc(sizeof(T));
    if (!buf)
      return 0;
    return new (buf) T;
  }
};

template <class T>
struct PrototypeCreator
{
  PrototypeCreator(T* pObj = 0)
    : pPrototype_(pObj) {}
  T* Create()
  {
    return pPrototype_ ? pPrototype_->Clone() : 0;
  }
  T* GetPrototype() { return pPrototype_; }
  void SetPrototype(T* _prototype) { ...; }

private:
  T* pPrototype_;
};

// -----------------------------------------------------------------
// 每次需要明确creator的具体类型

// library code
template <class CreationPolicy>
class WidgetManager : public CreationPolicy
{
  ...
};
// application code
typedef WidgetManager<OpNewCreator<Widget>> MyWidgetMgr;

// -----------------------------------------------------------------
//
// libarary code
template <template <class Created> class CreationPolicy>
class WidgetManager : public CreationPolicy<Widget>
{
  ...
};

// application code
typedef WidgetManager<OpNewCreator> MyWidgetMgr;

// -----------------------------------------------------------------

// libarary code
template <template <class> class CreationPolicy>
class WidgetManager : public CreationPolicy<Widget>
{
  ... void DoSomething()
  {
    Gadget* pw = CreationPolicy<Gadget>().Create();
  }
  ... void Swtichprototype(Widget* pNewPrototype)
  {
    CreationPolicy<Widget>& myPolicy = *this;
    delete myPolicy.GetPrototype();
    myPolicy.SetPrototype(pNewPrototype);
  }
};

/* [1.9]
   Combine policy classes: combine various policies for various aspects of working
   eg: 1. checking before dereference
       2. threading or single threaded
*/

template <
  class T,
  template <class> class CheckingPolicy,
  template <class> class ThreadingModel>
class SmartPtr;

// implementation of NoChecking and EnforeceNotNull
template <class T>
struct NoChecking
{
  static void Check(T*) {}
};

template <class T>
struct EnforceNotNull
{
  class NullPointerException : public std::exception
  {
    ...
  };
  static void Check(T* ptr)
  {
    if (!ptr)
      throw NullPointerException();
  }
};

// app code
typedef SmartPtr<Widget, NoChecking, SingleThreaded> WidgetPtr;
typedef SmartPtr<Widget, EnforceNotNull, SingleThreaded> SafeWidgetPtr;

// SmartPtr uses the checking policy this way:
template <
  class T,
  template <class> class CheckingPolicy,
  template <class> class ThreadingModel>
class SmartPtr
  : public CheckingPolicy<T>,
  public ThreadingModel<SmartPtr>
{
public:
  ...
    // overload
    T*
    operator->()
  {
    // have to use typename, or it's going to make 'Lock' as static member
    // 1. lock 2. check 3. return
    typename ThreadingModel<SmartPtr>::Lock guard(*this);
    CheckingPolicy<T>::Check(pointee_);
    return pointee_;
  }

private:
  T* pointee_;
};

/* [1.10] Customizing Structure with Policy Classes
*/

template <class T>
class DefaultSmartPtrStorage
{
private:
  PointerType ptr_;

public:
  typedef T* PointerType;
  typedef T& ReferenceType;

protected:
  PointerType GetPointer() { return ptr_; }
  void SetPointer(PointerType ptr) { pointee_ = ptr; }
};

template <
  class T,
  template <class> class CheckingPolicy,
  template <class> class ThreadingModel,
  template <class> class Storage = DefaultSmartPtrStorage>
class SmartPtr;

/* [1.11] Compatible and Incompatible Policies
*/
template <
  class T,
  template <class> class CheckingPolicy>
class SmartPtr : public CheckingPolicy<T>
{
  ... template <
    class T1,
    template <class> class CP1>
  SmartPtr(const SmartPtr<T1, CP1>& other)
    : pointee_(other.pointee_), CheckingPolicy<T>(other)
  {
    ...
  }
};

// user case:
ExtendedWidget < -Widget

  SmartPtr<Widget, EnforceNotNull>
  SmartPtr<ExtendedWidget, NoChecking>

  // if initialize a SmartPtr<Widget, NoChecking> with
  //                 SmartPtr<ExtendedWidget, NoChecking>
  // there is no problem, compiler will compromize it
  // so as NoChecking part

  // if initialize a SmartPtr<Widget, EnforecNotNull> with
  //                 SmartPtr<ExtendedWidget, NoChecking>
  // there is no problem, compiler will compromize it
  // then, compiler tries to match SmartPtr<ExtendedWidget, NoChecking>
  //                             to EnforceNotNull's c'tor
  // Two solutions:
  // 1. EnforaceNotNull implements a c'tor accepts a NoChecking obj
  // 2. NoChecking implements a conversion operator to EnforceNotNull

  /* [1.12 Decomposing a Class into Policies]
*/

template <class T>
struct IsArray
{
  T& ElementAt(T* ptr, unsigned int index)
  {
    return ptr[index];
  }
  // const T& 是为了保护内部的ptr 不然直接返回ref就会造成数据泄露
  const T& ElementAt(T* ptr, unsigned int index) const
  {
    return ptr[index];
  }
};

template <class T>
struct IsNotArray
{
};
