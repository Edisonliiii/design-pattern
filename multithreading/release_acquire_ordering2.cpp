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

std::vector<int> data;
std::atomic<int> flag = {0};

void t1() {
  data.push_back(42);
  flag.store(1, std::memory_order_release);
}

void t2() {
  int expected = 1;
  while (
      !flag.compare_exchange_strong(expected, 2, std::memory_order_relaxed)) {
    expected = 1;
  }
}

void t3() {
  while (flag.load(std::memory_order_acquire) < 2) {
  }
  assert(data.at(0) == 42);  // will never fire
}

int main() {
  std::thread a(t1);
  std::thread b(t2);
  std::thread c(t3);
  a.join();
  b.join();
  c.join();
}
