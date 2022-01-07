// plain
template <class Window, class Controller>
class Widget
{
  // ...
};

// explicitly specialize
template <>
class Widget<ModalDialog, MyController>
{
  // ...
};

// partial specialization
template <class Window>
class Widget <Window, MyController>
{
  // ...
};

/// eg:
template <class ButtonArg>
class Widget<Button<ButtonArg>, MyController>
{
  //...
};

// [2.3 Local Classes]
class Interface
{
public:
  virtual void Fun() = 0;
...
};

template <class T, class P>
Interface* MakeAdapter (const T& obj, const P& arg)
{
  class Local : public Interface
  {
  private:
    T obj_;
    P arg_;
  public:
    Local(const T& obj, const P& arg) : obj_(obj), arg_(arg) {}
    virtual void Fun() { obj_.Call(arg_); }
  };
  return new Local(obj, arg);
}


// [2.4 Mapping Integral Constants to Types]
template <int v>
struct Int2Type
{
  enum { value = v };
};
  // Int2Type <0> is different from Int2Type<1>

template <class T>
class NiftyContainer
{
  ...
};

// => better
template <typename T, bool isPolymorphic>
class NiftyContainer
{
  ...
  void DoSomething()
  {
    T* pSomeObj = ...;
    if (isPolymorphic)
    {
      T* pNewObj = pSomeObj->Clone();
      ...
    }
    else
    {
      T* pNewObj = new T(*pSomeObj);
      ...
    }
  }
};


// => better
template <typename T, bool isPolymorphic>
class NiftyContainer
{
private:
  void DoSomething(T* pObj, Int2Type<true>)
  {
    T* pNewObj = pObj->Clone();
    ...
  }

  void DoSomething(T* pObj, Int2Type<false>)
  {
    T* pNewObj = new T(*pObj);
    ...
  }
public:
  void DoSomething(T* pObj)
  {
    DoSomething(pObj, Int2Type<isPolymorphic>);
  }
};

// [2.5 Type2Type Mapping]

// ! partially specialize a function is fucking illegal

// wrong one
template <class U>
Widget* Create<Widget, U> (const U& arg)
{
  return new Widget(arg, -1);
}

// => better
template <class T, class U>
T* Create(const U& arg, T /* dummy */)
{
  return new T(arg);
}

template <class U>
Widget* Create(const U& arg, Widget)
{
  return new Widget(arg, -1);
} 


// => better: Type2Type is devoid of any value, but let you select which one to overload
template <typename T>
struct Type2Type
{
  typedef T OriginalType;
};

template <class T, class U>
T* Create(const U& arg, Type2Type<T>)
{
  return new T(arg);
}

template <class U>
Widget* Create(const U& arg, Type2Type<Widget>)
{
  return new Widget(arg, -1);
}




































