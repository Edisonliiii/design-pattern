// plain
template <class Window, class Controller>
class Widget {
  // ...
};

// explicitly specialize
template <>
class Widget<ModalDialog, MyController> {
  // ...
};

// partial specialization
template <class Window>
class Widget<Window, MyController> {
  // ...
};

/// eg:
template <class ButtonArg>
class Widget<Button<ButtonArg>, MyController> {
  //...
};

// [2.3 Local Classes]
class Interface {
 public:
  virtual void Fun() = 0;
  ...
};

template <class T, class P>
Interface* MakeAdapter(const T& obj, const P& arg) {
  class Local : public Interface {
   private:
    T obj_;
    P arg_;

   public:
    Local(const T& obj, const P& arg) : obj_(obj), arg_(arg) {}
    virtual void Fun() { obj_.Call(arg_); }
  };
  return new Local(obj, arg);
}

/**[2.4 Mapping Integral Constants to Types]
 * Int2Type <0> is different from Int2Type<1>
 * Usage:
 * 1. call one of several different functions, depending on a compile-time
 * constant
 * 2. need to do this dispath at compile time
 */
template <int v>
struct Int2Type {
  enum { value = v };
};

template <class T>
class NiftyContainer {
  ...
};

/**
 *  => better
 * Problem:
 * 1. the compiler won't let you get away with this code(if condition)
 *    -- For example, if isPl.. == true, it will use pObj->Clone()
 *    -- NiftyContainer::Dosomething() does not comile for any type that doesn't
 *       define a member function Clone()
 *    -- For compiler, it will still compile both branches
 *    -- It's possible for the nonpoly branch of the code to fail to compile, if
 *       T is a poly type and the nonpoly code branch attemps new T(*pObj), the
 *       code might fail to compile, therefore it would be nice if it can avoid
 *       compile time issue
 */
template <typename T, bool isPolymorphic>
class NiftyContainer {
  //...
  void DoSomething() {
    T* pSomeObj = ...;
    if (isPolymorphic) {
      T* pNewObj = pSomeObj->Clone();
      ...
    } else {
      T* pNewObj = new T(*pSomeObj);
      ...
    }
  }
};

/**
 * @brief better solution than above
 * In this way, compiler will avoid the abovementioned template issues
 */
template <typename T, bool isPolymorephic>
class NiftyContainer2 {
 private:
  void DoSomething(T* pObj, Int2Type<true>) {
    T* pSomeObj = pObj->Clone();
    //...
  }
  void DoSomething(T* pObj, Int2Type<false>) {
    T* pNewObj = new T(*pObj);
    // ...
  }

 public:
  void DoSomething(T* pObj) { DoSomething(pObj, Int2Type<isPolymorephic>()); }
};

// [2.5 Type2Type Mapping]
// ! partially specialize a function is fucking illegal

// wrong one
template <class U>
Widget* Create<Widget, U>(const U& arg) {
  return new Widget(arg, -1);
}

// => better
template <class T, class U>
T* Create(const U& arg, T /* dummy */) {
  return new T(arg);
}

template <class U>
Widget* Create(const U& arg, Widget) {
  return new Widget(arg, -1);
}

// => better: Type2Type is devoid of any value, but let you select which one to
// overload 相当于上面int2type的generalization
template <typename T>
struct Type2Type {
  typedef T OriginalType;
};

template <class T, class U>
T* Create(const U& arg, Type2Type<T>) {
  return new T(arg);
}

template <class U>
Widget* Create(const U& arg, Type2Type<Widget>) {
  return new Widget(arg, -1);
}
// user case
std::string* pStr = Create("Hello", Type2Type<std::string>());
Widget* pW = Create(100, Type2Type<Widget>);

/**
 * @brief 2.6 Type Selection
 * Usage: some generic code needs to select one type to another
 *
 * For example, for NifftyContainer, if you want to use vector as its backend
 * storage, then you might want to store it as value, because it's direct. Else,
 * you want to store it as polymorphic pointers, because you got an inheritance
 * chain
 *
 * Drawbacks;
 * -- A new trait struct for each new type
 * -- clumsy
 */
template <typename T, bool isPolymorphic>
struct NiftyContainer3ValueTraits {
  typedef T* ValueType;
};

template <typename T>
struct NiftyContainer3ValueTraits<T, false> {
  typedef T ValueType;
};

template <typename T, bool isPolynorphic>
class NiftyContainer3 {
  typedef NiftyContainer3ValueTraits<T, isPolynorphic> Traits;
  typedef typename Traits::ValueType ValueType;
};

/**
 * @brief Selector
 *
 */
template <bool flag, typename T, typename U>
struct Select {
  typedef T Result;
};

template <typename T, typename U>
struct Select<false, T, U> {
  typedef U Result;
}

template <typename T, bool isPoly>
class NiftyContainer4 {
  typedef typename Select<isPoly, T*, T>::Result ValuType;
};
