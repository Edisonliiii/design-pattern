#ifndef TYPETRAITSTEST_H
#define TYPETRAITSTEST_H

#include <loki/TypeTraits.h>

class TypeTraitsTest : public Test {
 public:
  TypeTraitsTest() : Test("TypeTraits.h") {}

  virtual void execute(TestResult& result) {
    printName(result);
    using namespace Loki;
    bool r;

    r = TypeTraits<int*>::isPointer && !TypeTraits<int>::isPointer &&
        SameType<TypeTraits<int*>::PointeeType, int>::value &&
        SameType<TypeTraits<int>::PointeeType, NullType>::value;
  }
}

#endif  // TYPETRAITSTEST_H