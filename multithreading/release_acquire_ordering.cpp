#include <stdlib.h>

#include <algorithm>
#include <atomic>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

/**
 * @brief example for release-acquire synchronization
 * https://en.cppreference.com/w/cpp/atomic/memory_order#Release-Acquire_ordering
 */

std::atomic<std::string*> ptr;
int data;

void producer() {
  std::string* p = new std::string("hello");
  data = 42;
  ptr.store(p, std::memory_order_release);
}

void consumer() {
  std::string* p2;
  while (!(
      p2 = ptr.load(
          std::memory_order_acquire))) {  // will busy waiting until producer
                                          // thread finish all write operations
                                          // before memory_order_release
  }
  assert(*p2 == "hello");
  assert(data == 42);
}

int main(int argc, char const* argv[]) {
  std::thread t1(producer);
  std::thread t2(consumer);
  t1.join(), t2.join();
  return 0;
}
