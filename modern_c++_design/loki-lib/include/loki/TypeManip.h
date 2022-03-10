#ifndef LOKI_TYPEMANIP_INC_
#define LOKI_TYPEMANIP_INC_

namespace Loki {
// Int2Type
template <int v>
struct Int2Type {
  enum { value = v };
};

/**
 * @brief We can NOT partial specialize a function
 * e.g.(counterexample) this is NOT working
 * template<class U>
 * Widget* Create<Widget, U>(const U& arg)
 * {
 *  return new Widget(arg, -1);
 * }
 *
 * The right way is we create a tag structure and we use it like
 * template <class T, class U>
 * T* Create(const U& arg, Type2Type<T>)
 * {
 *  return new T(arg);
 * }
 *
 * template <class U>
 * Widget* Create(const U& arg, Type2Type<Widget>)
 * {
 *  return new Widget(arg, -1);
 * }
 *
 * User case:
 * String* str = Create("Hello", Type2Type<String>());
 * Widget* pw = Create(100, Type2Type<Widget>());
 * @tparam T
 */
template <typename T>
struct Type2Type {
  typedef T OriginalType;
};

/**
 * @brief Select type
 *
 * Idea: imagine there is a generic container
 * template<class T> class NiftyContainer
 * {
 *  // Ptr -> object<T>
 * };
 *
 * To duplicate an obj contained in NiftyContainer
 * we need to call either its copy c'tor (for nonploymorphic types) or a Clone()
 * virtual function (for polymorphic types)
 *
 * template <typename T, bool isPolymorphic>
 * class NiftyContainer
 * {
 *  ...
 *  void DoSomething()
 *  {
 *    T* pSomeObj = ...;
 *    if (isPloymorphic){
 *      T* pNewObj = pSomeobj->Clone();
 *      ...
 *    } else {
 *      T* pNewObj = new T (*pSomeObj);
 *      ...
 *    }
 *  }
 *  ...
 * }
 *
 * @tparam flag
 * @tparam T
 * @tparam U
 */
template <bool flag, typename T, typename U>
struct Select {
  typedef T Result;
};

template <typename T, typename U>
struct Select<false, T, U> {
  typedef U Result;
};

// IsSameType
template <typename T, typename U>
struct IsSameType {
  enum { value = false };
};

template <typename T>
struct IsSameType<T, T> {
  enum { value = true };
};

// Helper types small and big
// make sure sizeof(small) < sizeof(big)
/**
 * @brief
 * Example: const bool convExists = sizeof(Test(T())) == sizeof(Small), here T()
 * is the type we wants to check, T() is the c'tor
 * - Test(...), is an undefined behavior,  but this doesn't matter. Nothing
 * actually calls the function. It's not even implemented.
 */
namespace Private {
// thanks to the powerful sizeof
template <class T, class U>
struct ConversionHelper {
  // doesn't matter which platform, arch or instruction set is using
  // Small and Big are two absolutly diff types
  typedef char Small;
  struct Big {
    char dummy[2];
  };
  // the thought is basically utilizing the compiler to distinguish plateform
  // difference utilize the type of return value to check the result Here is
  // either type Big or type Small to determine if T and U are the same if T and
  // U are exactly the same, they will call the same overloaded function
  // inbetween a. or b. if T and U are diff, they will call the diff These two
  // static functions both stay unimplemented
  static Big Test(...);  // a. accept anything else
  static Small Test(U);  // b. accept U only

  // if T makes its default constructor private, then above method will fail
  // it stays unimplemented
  // e.g. const bool convExists = sizeof(Test(MakeT()) == sizeof(small))
  static T MakeT();
};
}  // namespace Private

/**
 * @brief
 *    figures out the conversion relationships between two types
 *    a) Conversion<T, U>::exists
 *    return (at compile time) true if there is an implicit conversion from T to
 U
 *    e.g. Derived to Base

 *    b) Conversion <T,U>::exists2Way
 *    returns (at compile time)true if there are both conversions from T
 *    to U and from U to T (example: int to char and back)

 *    c) Conversion<T, U>::sameType
 *    returns (at compile time) true if T and U represent the same type
 *
 * @tparam T
 * @tparam U
 */
template <class T, class U>
struct Conversion {
  // here is the handler
  typedef Private::ConversionHelper<T, U> H;
#ifndef __MWERKS__
  enum { exists = sizeof(typename H::Small) == sizeof((H::Test(H::MakeT()))) };
#else
  enum { exists = false };
#endif
  enum { exists2Way = exists && Conversion<U, T>::exists };
  enum { sameType = false };
};

template <class T>
struct Conversion<T, T> {
  enum { exists = 1, exists2Way = 1, sameType = 1 };
};

template <class T>
struct Conversion<void, T> {
  enum { exists = 0, exists2Way = 0, sameType = 0 };
};

template <class T>
struct Conversion<T, void> {
  enum { exists = 0, exists2Way = 0, sameType = 0 };
};

template <>
struct Conversion<void, void> {
 public:
  enum { exists = 1, exists2Way = 1, sameType = 1 };
};

/**
 * @brief
 * SuperSubclass<B, D>::value where B and D are types
 * returns true if B is a pub base of D, if B and D area aliases of the same
 * type Core idea: when we pass a pointer, if formal parameter == base pointer
 *    it can accept both derived ptr / based ptr
 * else if formal parameter == derivced pointer
 *    it can accept only derived ptr
 *
 * if U(base) <- T(derived): value = true
 * else value = false
 *
 * value == true iff they have inheritence and not totally same
 *
 * Three cases:
 * 1. T is the same type as U
 * 2. T is an unambiguous public base of U
 * 3. T is void
 *
 * @tparam T - base ptr
 * @tparam U - derived ptr
 */
template <class T, class U>
struct SuperSubclass {
  enum {
    value =
        (::Loki::Conversion<const volatile U*, const volatile T*>::exists &&
         !::Loki::Conversion<const volatile T*, const volatile void*>::sameType)
  };
  // Dummy enum
  enum { dontUseWithIncompleteTypes = (sizeof(T) == sizeof(U)) };
};

template <>
struct SuperSubclass<void, void> {
  enum { value = false };
};

template <class U>
struct SuperSubclass<void, U> {
  enum {
    value =
        (::Loki::Conversion<const volatile U*, const volatile void*>::exists &&
         !::Loki::Conversion<const volatile void*,
                             const volatile void*>::sameType)
  };

  enum { dontUseWithIncompleteTypes = (0 == sizeof(U)) };
};

template <class T>
struct SuperSubclass<T, void> {
  enum {
    value =
        (::Loki::Conversion<const volatile void*, const volatile T*>::exists &&
         !::Loki::Conversion<const volatile T*, const volatile void*>::sameType)
  };

  enum { dodontUseWithIncompleteTypes = (sizeof(T) == 0) };
}

/**
 * @brief class template SuperSubclassStrict
 * Invocation: SuperSubclassStrict<B, D>::value where B and D are types.
 * Returns true if B is a public base of D.
 * Don't allow B and D are the same type
 */
template <class T, class U>
struct SuperSubclassStrict {
  enum {
    value =
        (::Loki::Conversion<const volatile U*, const volatile T*>::exists &&
         !::Loki::Conversion<const volatile T*,
                             const volatile void*>::sameType &&
         !::Loki::Conversion<const volatile T*, const volatile U*>::sameType)
  };

    enum { dontUseWithIncompleteTypes = (sizeof(T) == sizeof(U) };
};

template <>
struct SuperSubclassStrict<void, void> {
  enum { value = false };
};

template <class U>
struct SuperSubclassStrict<void, U> {
  enum {
    value =
        (::Loki::Conversion<const volatile U*, const volatile void*>::exists &&
         !::Loki::Conversion<const volatile void*,
                             const volatile void*>::sameType &&
         !::Loki::Conversion<const volatile void*, const volatile U*>::sameType)
  };

  enum { dontUseWithIncompleteTypes = 0 == sizeof(U) };
};

template <class T>
struct SuperSubclassStrict<T, void> {
  enum {
    value =
        (::Loki::Conversion<const volatile void*, const volatile T*>::exists &&
         !::Loki::Conversion<const volatile T*,
                             const volatile void*>::sameType &&
         !::Loki::Conversion<const volatile T*, const volatile void*>::sameType)
  };

  // Dummy enum to make sure that both classes are fully defined.
  enum { dontUseWithIncompleteTypes = (sizeof(T) == 0) };
};
};  // namespace Loki

// public interfaces
#define LOKI_SUPERSUBCLASS(T, U) ::Loki::SuperSubclass<T, U>::value

#define LOKI_SUPERSUBCLASS_STRICT(T, U) ::Loki::SuperSubclassStrict<T, U>::value

#endif  // LOKI_TYPEMANIP_INC_