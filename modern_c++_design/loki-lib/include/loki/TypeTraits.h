#ifndef LOKI_TYPETRAITS_INC_
#define LOKI_TYPETRAITS_INC_

#include <loki/Sequence.h>
#include <loki/Typelist.h>

#if (defined _MSC_VER) && (_MSC_VER < 1400)
#include <string>
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 41800)  // qualifier applied to function type has no
                                  // meaning, ignored
#endif

namespace Loki {
template <typename T>
struct IsCustomUnsignedInt {
  enum { value = 0 };
};  // IsCustomUnsignedInt

template <typename T>
struct IsCustomSignedInt {
  enum { value = 0 };
};  // IsCustomSignedInt

template <typename T>
struct IsCustomFloat {
  enum { value = 0 };
};  // IsCustomFloat

namespace Private {
#ifndef LOKI_DISABLE_TYPELIST_MACROS
typedef LOKI_TYPELIST_4(unsigned char, unsigned short int, unsigned int,
                        unsigned long int) StdUnsignedInts;
typedef LOKI_TYPELIST_4(signed char, short int, int, long int) StdSignedInts;
typedef LOKI_TYPELIST_3(bool, char, wchar_t) StdOtherInts;
typedef LOKI_TYPELIST_3(float, double, long double) StdFloats;
#else
typedef Loki::Seq<unsigned char, unsigned short int, unsigned int,
                  unsigned long int>::Type StdUnsignedInts;
typedef Loki::Seq<signed char, short int, int, long int>::Type StdSignedInts;
typedef Loki::Seq<bool, char, wchar_t>::Type StdOtherInts;
typedef Loki::Seq<float, double, long double>::Type StdFloats;
#endif

template <typename U>
struct AddPointer {
  typedef U* Result;
};  // AddPointer

template <typename U>
struct AddPointer<U&> {
  typedef U* Result;
}  // AddPointer for ptr reference

template <class U>
struct AddReference {
  typedef U& Result;
};

template <class U>
struct AddReference<U&> {
  typedef U& Result;
};

template <>
struct AddReference<void> {
  typedef NullType Result;
};

template <class U>
struct AddParameterType {
  typedef const U& Result;
};

template <class U>
struct AddParameterType<U&> {
  typedef U& Result;
};

template <>
struct AddParameterType<void> {
  typedef NullType Result;
};

template <typename T>
struct IsFunctionPointerRaw {
  enum { result = 0 };
};

template <typename T>
struct IsFunctionPointerRaw<T (*)()> {
  enum { result = 1 };
};

template <typename T, typename P01>
struct IsFunctionPointerRaw<T (*)(P01)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02>
struct IsFunctionPointerRaw<T (*)(P01, P02)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08,
                                  P09)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09,
          typename P10>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  P10)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09,
          typename P10, typename P11>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  P10, P11)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09,
          typename P10, typename P11, typename P12>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  P10, P11, P12)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09,
          typename P10, typename P11, typename P12, typename P13>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  P10, P11, P12, P13)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09,
          typename P10, typename P11, typename P12, typename P13, typename P14>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  P10, P11, P12, P13, P14)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09,
          typename P10, typename P11, typename P12, typename P13, typename P14,
          typename P15>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  P10, P11, P12, P13, P14, P15)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09,
          typename P10, typename P11, typename P12, typename P13, typename P14,
          typename P15, typename P16>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  P10, P11, P12, P13, P14, P15, P16)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09,
          typename P10, typename P11, typename P12, typename P13, typename P14,
          typename P15, typename P16, typename P17>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  P10, P11, P12, P13, P14, P15, P16, P17)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09,
          typename P10, typename P11, typename P12, typename P13, typename P14,
          typename P15, typename P16, typename P17, typename P18>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  P10, P11, P12, P13, P14, P15, P16, P17,
                                  P18)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09,
          typename P10, typename P11, typename P12, typename P13, typename P14,
          typename P15, typename P16, typename P17, typename P18, typename P19>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  P10, P11, P12, P13, P14, P15, P16, P17, P18,
                                  P19)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09,
          typename P10, typename P11, typename P12, typename P13, typename P14,
          typename P15, typename P16, typename P17, typename P18, typename P19,
          typename P20>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  P10, P11, P12, P13, P14, P15, P16, P17, P18,
                                  P19, P20)> {
  enum { result = 1 };
};

template <typename T>
struct IsFunctionPointerRaw<T (*)(...)> {
  enum { result = 1 };
};

template <typename T, typename P01>
struct IsFunctionPointerRaw<T (*)(P01, ...)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02>
struct IsFunctionPointerRaw<T (*)(P01, P02, ...)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, ...)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, ...)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, ...)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, ...)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, ...)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08,
                                  ...)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  ...)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09,
          typename P10>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  P10, ...)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09,
          typename P10, typename P11>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  P10, P11, ...)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09,
          typename P10, typename P11, typename P12>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  P10, P11, P12, ...)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09,
          typename P10, typename P11, typename P12, typename P13>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  P10, P11, P12, P13, ...)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09,
          typename P10, typename P11, typename P12, typename P13, typename P14>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  P10, P11, P12, P13, P14, ...)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09,
          typename P10, typename P11, typename P12, typename P13, typename P14,
          typename P15>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  P10, P11, P12, P13, P14, P15, ...)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09,
          typename P10, typename P11, typename P12, typename P13, typename P14,
          typename P15, typename P16>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  P10, P11, P12, P13, P14, P15, P16, ...)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09,
          typename P10, typename P11, typename P12, typename P13, typename P14,
          typename P15, typename P16, typename P17>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  P10, P11, P12, P13, P14, P15, P16, P17,
                                  ...)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09,
          typename P10, typename P11, typename P12, typename P13, typename P14,
          typename P15, typename P16, typename P17, typename P18>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  P10, P11, P12, P13, P14, P15, P16, P17, P18,
                                  ...)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09,
          typename P10, typename P11, typename P12, typename P13, typename P14,
          typename P15, typename P16, typename P17, typename P18, typename P19>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  P10, P11, P12, P13, P14, P15, P16, P17, P18,
                                  P19, ...)> {
  enum { result = 1 };
};

template <typename T, typename P01, typename P02, typename P03, typename P04,
          typename P05, typename P06, typename P07, typename P08, typename P09,
          typename P10, typename P11, typename P12, typename P13, typename P14,
          typename P15, typename P16, typename P17, typename P18, typename P19,
          typename P20>
struct IsFunctionPointerRaw<T (*)(P01, P02, P03, P04, P05, P06, P07, P08, P09,
                                  P10, P11, P12, P13, P14, P15, P16, P17, P18,
                                  P19, P20, ...)> {
  enum { result = 1 };
};

template <typename T>
struct IsMemberFunctionPointerRaw {
  enum { result = 0 };
};

template <typename T, typename S>
struct IsMemberFunctionPointerRaw<T (S::*)()> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01>
struct IsMemberFunctionPointerRaw<T (S::*)(P01)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, P17)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, P17, P18)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18,
          typename P19>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, P17, P18, P19)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18,
          typename P19, typename P20>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, P17, P18, P19, P20)> {
  enum { result = 1 };
};

template <typename T, typename S>
struct IsMemberFunctionPointerRaw<T (S::*)(...)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, ...)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, ...)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, ...)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, ...)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, ...)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, ...)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           ...)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, ...)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, ...)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, ...)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, ...)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, ...)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, ...)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           ...)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, ...)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, ...)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, P17, ...)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, P17, P18, ...)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18,
          typename P19>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, P17, P18, P19, ...)> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18,
          typename P19, typename P20>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, P17, P18, P19, P20, ...)> {
  enum { result = 1 };
};

// Const versions

template <typename T, typename S>
struct IsMemberFunctionPointerRaw<T (S::*)() const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01>
struct IsMemberFunctionPointerRaw<T (S::*)(P01) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06)
                                      const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07)
                                      const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, P06, P07, P08, P09, P10, P11, P12, P13) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14)
                                      const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, P06, P07, P08, P09, P10, P11, P12, P13, P14, P15)
                                      const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, P17) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, P17, P18) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18,
          typename P19>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, P17, P18, P19) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18,
          typename P19, typename P20>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, P06, P07, P08, P09, P10, P11, P12, P13, P14, P15,
    P16, P17, P18, P19, P20) const> {
  enum { result = 1 };
};

template <typename T, typename S>
struct IsMemberFunctionPointerRaw<T (S::*)(...) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, ...) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, ...) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, ...) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, ...) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, ...)
                                      const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, ...)
                                      const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           ...) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, ...) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, ...) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, ...) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, ...) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, P06, P07, P08, P09, P10, P11, P12, ...) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, ...)
                                      const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, P06, P07, P08, P09, P10, P11, P12, P13, P14, ...)
                                      const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, ...) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, ...) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, P17, ...) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, P17, P18, ...) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18,
          typename P19>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, P06, P07, P08, P09, P10, P11, P12, P13, P14, P15,
    P16, P17, P18, P19, ...) const> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18,
          typename P19, typename P20>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, P06, P07, P08, P09, P10, P11, P12, P13, P14, P15,
    P16, P17, P18, P19, P20, ...) const> {
  enum { result = 1 };
};

// Volatile versions

template <typename T, typename S>
struct IsMemberFunctionPointerRaw<T (S::*)() volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01>
struct IsMemberFunctionPointerRaw<T (S::*)(P01) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05,
                                           P06) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06,
                                           P07) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, P06, P07, P08, P09, P10, P11, P12, P13) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13,
                                           P14) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, P17) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, P17, P18) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18,
          typename P19>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, P17, P18, P19) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18,
          typename P19, typename P20>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, P06, P07, P08, P09, P10, P11, P12, P13, P14, P15,
    P16, P17, P18, P19, P20) volatile> {
  enum { result = 1 };
};

template <typename T, typename S>
struct IsMemberFunctionPointerRaw<T (S::*)(...) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, ...) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, ...) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, ...) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, ...) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05,
                                           ...) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06,
                                           ...) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           ...) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, ...) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, ...) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, ...) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, ...) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, P06, P07, P08, P09, P10, P11, P12, ...) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13,
                                           ...) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           ...) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, ...) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, ...) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, P17, ...) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, P17, P18, ...) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18,
          typename P19>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, P06, P07, P08, P09, P10, P11, P12, P13, P14, P15,
    P16, P17, P18, P19, ...) volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18,
          typename P19, typename P20>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, P06, P07, P08, P09, P10, P11, P12, P13, P14, P15,
    P16, P17, P18, P19, P20, ...) volatile> {
  enum { result = 1 };
};

// Const volatile versions

template <typename T, typename S>
struct IsMemberFunctionPointerRaw<T (S::*)() const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01>
struct IsMemberFunctionPointerRaw<T (S::*)(P01) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05)
                                      const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06)
                                      const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07)
                                      const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12)
                                      const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13)
                                      const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14)
                                      const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, P06, P07, P08, P09, P10, P11, P12, P13, P14, P15)
                                      const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, P17) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, P17, P18) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18,
          typename P19>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, P06, P07, P08, P09, P10, P11, P12, P13, P14, P15,
    P16, P17, P18, P19) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18,
          typename P19, typename P20>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, P06, P07, P08, P09, P10, P11, P12, P13, P14, P15,
    P16, P17, P18, P19, P20) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S>
struct IsMemberFunctionPointerRaw<T (S::*)(...) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, ...) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, ...) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, ...) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, ...)
                                      const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, ...)
                                      const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, ...)
                                      const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           ...) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, ...) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, ...) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, ...) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, ...)
                                      const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, ...)
                                      const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, ...)
                                      const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, P06, P07, P08, P09, P10, P11, P12, P13, P14, ...)
                                      const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, ...) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, ...) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17>
struct IsMemberFunctionPointerRaw<T (S::*)(P01, P02, P03, P04, P05, P06, P07,
                                           P08, P09, P10, P11, P12, P13, P14,
                                           P15, P16, P17, ...) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, P06, P07, P08, P09, P10, P11, P12, P13, P14, P15,
    P16, P17, P18, ...) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18,
          typename P19>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, P06, P07, P08, P09, P10, P11, P12, P13, P14, P15,
    P16, P17, P18, P19, ...) const volatile> {
  enum { result = 1 };
};

template <typename T, typename S, typename P01, typename P02, typename P03,
          typename P04, typename P05, typename P06, typename P07, typename P08,
          typename P09, typename P10, typename P11, typename P12, typename P13,
          typename P14, typename P15, typename P16, typename P17, typename P18,
          typename P19, typename P20>
struct IsMemberFunctionPointerRaw<T (S::*)(
    P01, P02, P03, P04, P05, P06, P07, P08, P09, P10, P11, P12, P13, P14, P15,
    P16, P17, P18, P19, P20, ...) const volatile> {
  enum { result = 1 };
};
};  // namespace Private

/**
 * @brief Class template TypeTraits
 *
 * Figures out at compile time various properties of any given type
 * Invocations (T is a type, TypeTraits<T>::Property)
 *
 * - isPointer          : returns true is T is a pointer type
 */
template <typename T>
class TypeTraits {
 private:
  // ------------- area for UnConst
  template <class U>
  struct UnConst {
    typedef U Result;
    enum { isConst = 0 };
  };

  template <class U>
  struct UnConst<const U> {
    typedef U Result;
    enum { isConst = 1 };
  };

  template <class U>
  struct UnConst<const U&> {
    typedef U& Result;
    enum { isConst = 1 };
  };

  // ------------- area for UnVolatile
  template <class U>
  struct UnVolatile {
    typedef U Result;
    enum { isVolatile = 0 };
  };

  template <class U>
  struct UnVolatile<volatile U> {
    typedef U Result;
    enum { isVolatile = 1 };
  };

  template <class U>
  struct UnVolatile<volatile U&> {
    typedef U& Result;
    enum { isVolatile = 1 };
  };

  // ------------- area for PointerTraits
  template <class U>
  struct PointerTraits {
    enum { result = false };
    typedef NullType PointeeType;
  };

  template <class U>
  struct PointerTraits<U*> {
    enum { result = true };
    typedef U PointeeType;
  };

  template <class U>
  struct PointerTraits<U*&> {
    enum { result = true };
    typedef U PointeeType;
  };

  // ------------- area for ReferenceTraits
  template <class U>
  struct ReferenceTraits {
    enum {result = false};
    typedef NullType ReferredType;
  };

 public:
  typedef typename UnConst<T>::Result NonConstType;
  typedef typename UnVolatile<T>::Result NonVolatileType;
  typedef
      typename UnVolatile<typename UnConst<T>::Result>::Result UnqualifiedType;
  typedef typename PointerTraits<UnqualifiedType>::PointeeType PointeeType;
};  // TypeTraits

};  // namespace Loki

#endif  // LOKI_TYPETRAITS_INC_