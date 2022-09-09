#include <stdlib.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

class myClass {
 public:
  int i;
  myClass(int _i) : i(_i) {}
};

int main(int argc, char const *argv[]) {
  std::cout << "using make_shared...." << std::endl;
  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 1000000; ++i) {
    std::shared_ptr<myClass> p = std::make_shared<myClass>(123);
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << duration.count() << std::endl;

  std::cout << "using new...." << std::endl;
  start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 1000000; ++i) {
    std::shared_ptr<myClass> p(new myClass(100));
  }
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << duration.count() << std::endl;
  return 0;
}
