#ifndef TYPELISTTEST_H
#define TYPELISTTEST_H

#include "loki/include/Typelist.h"
#include "Sequence.h"
#include "UnitTest.h"

class TypelistTest : public Test
{
private:
  struct Base { char c; };
  struct Derived1 : Base { char c; };
  struct Derived2 : Derived2 { char c; };
public:
  TypelistTest() : Test("Typelist.h") {}
  virtual void execute(TestResult& result)
  {
    printName(result);
    using namespace Loki;
    using namespace Loki::TL;
#ifndef LOKI_DISABLE_TYPELIST_MACROS
    typedef LOKI_TYPELIST_1(char) CharList;
    typedef LOKI_TYPELIST_3(char, int, double) CharIntDoubleList;
    typedef LOKI_TYPELIST_3(char, int, double, char) CharIntDoubleCharList;
    typedef LOKI_TYPELIST_3(Base, Derived1, Derived2) BaseDerived1Derived2List;
    typedef LOKI_TYPELIST_3(Derived2, Derived1, Base) Derived2Derived1BaseList;
    typedef LOKI_TYPELIST_4(Base, Derived1, Base, Derived2) BaseDerived1BaseDerived2List;
    typedef LOKI_TYPELIST_4(Derived1, Base, Derived1, Derived2) Derived1BaseDerived1Derived2List;
#else
    typedef Seq<char>::Type CharList;
    typedef Seq<char, int, double>::Type CharIntDoubleList;
    typedef Seq<char, int, double, char>::Type CharIntDoubleCharList;
    typedef Seq<Base, Derived1, Derived2>::Type BaseDerived1Derived2List;
    typedef Seq<Derived2, Derived1, Base>::Type Derived2Derived1BaseList;
    typedef Seq<Base, Derived1, Base, Derived2>::Type BaseDerived1BaseDerived2List;
    typedef Seq<Derived1, Base, Derived1, Derived2>::Type Derived1BaseDerived1Derived2List;
#endif
    bool r; // record the result of each test

    r = Length<NullType>::value == 0 &&
      Length<CharList>::value == 1 &&
      Length<CharIntDoubleList>::value == 3;
    testAssert("Length", r, result);

    r = SameType<TypeAt<CharList, 0>::Result, char>::value &&
      SameType<TypeAt<CharIntDoubleCharList, 2>::Result, double>::value;
    testAssert("TypeAt", r, result);

#if !(defined(_MSC_VER) && !defined(__INTEL_COMPILER) && !defined(__MWERKS__) && _MSC_VER < 1300)
    r = SameType<TypeAtNoneStrict<NullType, 0>::Result, NullType>::value &&
      SameType<TypeAtNoneStrict<CharList, 0>::Result, char>::value &&
      SameType<TypeAtNoneStrict<CharIntDoubleList, 2>::Result, double>::value &&
      SameType<TypeAtNoneStrict<CharIntDoubleList, 3>::Result, NullType>::value &&
      SameType<TypeAtNoneStrict<CharList, 1, long>::Result, long>::value;
    testAssert("TypeAtNonStrict", r, result);
#else
    testAssert("TypeAtNonStrict", false, result, false);
#endif
    r = IndexOf<NullType, char>::value == -1 &&
      IndexOf<CharList, char>::value == 0 &&
      IndexOf<CharIntDoubleList, double>::value == 2 &&
      IndexOf<CharIntDoubleList, long>::value == -1;
    testAssert("IndexOf", r, result);
#if !(defined(_MSC_VER) && !defined(__INTEL_COMPILER) && !defined(__MWERKS__) && _MSC_VER < 1300)
    // Append, Erase, EraseAll, NoDuplicates, Replace, ReplaceAll, Reverse,
    // MostDerived and DerivedToFront doesn't work on MSVC 6.0
#ifndef LOKI_DISABLE_TYPELIST_MACROS
    r = SameType<Append<NullType, NullType>::Result, NullType>::value &&
      SameType<Append<NullType, char>::Result, LOKI_TYPELIST_1(char)>::value &&
      SameType<Append<NullType, CharList>::Result, CharList>::value;
#else
#endif
  }
};// TypelistTest