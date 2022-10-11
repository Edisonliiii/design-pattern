#include <iostream>

class Alpha {
 public:
  Alpha() { std::cout << "ctor" << std::endl; }
  Alpha(Alpha &) { std::cout << "copy ctor" << std::endl; }
  Alpha(Alpha &&) { std::cout << "move ctor" << std::endl; }
  Alpha &operator=(Alpha &a) {
    if (this == &a) return *this;
    std::cout << "copy asgn op" << std::endl;
  }
  Alpha &operator=(Alpha &&a) {  // for rvalue only
    if (this == &a) return *this;
    std::cout << "move asgn op" << std::endl;
  }
};

Alpha foo(Alpha a) {  // copy ctor
  return a;           // move ctor
}

Alpha bar(Alpha &&a) {
  return a;  // Copy ctor is called (unexpected).
}

int main() {
  Alpha a, b;
  a = foo(a);
  // a = foo(Alpha());
  // a = bar(Alpha());
  // b = a;
  return 0;
}