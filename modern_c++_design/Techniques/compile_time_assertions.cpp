#include <assert.h>
// [2.1] larger types must not be cast to smaller types

template <class To, class From>
To safe_reinterpret_cast(From from) {
  assert(sizeof(From) <= sizeof(To));
  return reinterpret_cast<To>(from);
}

// usage: user specifies 'To' explicitly, compiler deduces the 'From'.
int i = ...;
char* p = safe_reinterpret_cast<char*>(i);

// c style compiler-time assertion
// For the purpose of portability, use macro check to do the potential bug on
// reinterpret_cast
// - if system pointers are larger than characters, the compilter complains that
// you are trying to create an array of length zero
//
#define STATIC_CHECK(expr) \
  { char unnamed[(expr) ? 1 : 0]; }

template <class To, class From>
To safe_reinterpret_cast(From from) {
  STATIC_CHECK(sizeof(From) <= sizeof(To));
  return reinterpret_cast<To>(from);
}
... void* somePointer = ...;
char c = safe_reinterpret_cast<char>(somePointer);

// Better Solution: compiler will utters a message such as 'undefined
// specialization CompilterTimeError<false>'
//                  it gives developer better debug information
template <bool>
struct CompileTimeError;  // template taking nontype param
template <>
struct CompileTimeError<true> {};  // true as param

#define STATIC_CHECK(expr) \
  (CompileTimeError<(expr) != 0>)())

// Better Solution:
// ellipsis function, accepcts everything
template <bool>
struct CompileTimeChecker {
  CompileTimeChecker{...};
};
template <>
struct CompileTimeChecker<false> {};

#define STATIC_CHECK(expr, msg)                                     \
  {                                                                 \
    class Error_##msg {};                                           \
    (void)sizeof(CompileTimeChecker<(expr) != 0>((Error_##msg()))); \
  }

template <class To, class From>
To safe_reinterpret_cast(From from) {
  STATIC_CHECK(sizeof(From) < sizeof(To), Destination_Type_Too_Narrow);
  return reinterpret_cast<To>(from);
}
... void* somePointer = ...;
char c = safe_reinterpret_cast<char>(somePointer);
