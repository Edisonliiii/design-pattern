#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <string>
#include <thread>
#include <vector>

template <class DerivedT>  // templaterized type
class Base {
 private:
  struct accessor : DerivedT {                    // inherient from defined type
    static int foo(DerivedT& derived) {           // pass derived ref
      int (DerivedT::*fn)() = &DerivedT::do_foo;  // derived's func ptr
      return (derived.*fn)();                     // call thru ptr
    }
  };

 public:  // interface
  DerivedT& dervied() { return static_cast<DerivedT&>(*this); }
  int foo() {
    // call private foo with current instance as a derived ref
    return accessor::foo(this->dervied());
  }
};

struct Derived : Base<Derived> {
 public:
  int do_foo() {
    std::cout << "hello Derived!" << std::endl;
    return 1;
  }
};

struct Derived2 : Base<Derived2> {
 public:
  int do_foo() {
    std::cout << "hello Derived2!" << std::endl;
    return 1;
  }
};

int main(int argc, char const* argv[]) {
  Derived d;
  d.foo();
  Derived2 d2;
  d2.foo();
  return 0;
}
