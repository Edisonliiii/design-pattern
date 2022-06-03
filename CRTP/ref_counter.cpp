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

// calculate obj c'tor and d'tor times
template <typename T>
class counter {
 public:
  static int obj_creat;
  static int obj_alive;

  counter() {
    ++obj_creat;
    ++obj_alive;
  }

  counter(const counter &) {
    ++obj_creat;
    ++obj_alive;
  }

 protected:
  ~counter() { --obj_alive; }
};

template <typename T>
int counter<T>::obj_creat(0);

template <typename T>
int counter<T>::obj_alive(0);

class X : counter<X> {
 public:
  void printer() {
    std::cout << obj_creat << std::endl;
    std::cout << obj_alive << std::endl;
  }
};

class Y : counter<Y> {
 public:
  void printer() {
    std::cout << obj_creat << std::endl;
    std::cout << obj_alive << std::endl;
  }
};

int main(int argc, char const *argv[]) {
  X x1, x2, x3;
  Y y1;
  x1.printer();
  x2.printer();
  x3.printer();
  y1.printer();
  return 0;
}
