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
 * @brief relaxed: no synchronization and no ordering constrains
 * in this experiment, diff threads don't know the progress of others, it only
 * guarantee the atomicity
 *
 */

std::atomic<int> cnt = {0};

void f() {
  for (int i = 0; i < 1000; ++i) {
    cnt.fetch_add(1, std::memory_order_relaxed);
  }
}

int main(int argc, char const* argv[]) {
  std::vector<std::thread> v;
  for (int i = 0; i < 10; ++i) {
    v.emplace_back(f);
  }
  for (auto& t : v) {
    t.join();
  }
  std::cout << "Final result of cnt: " << cnt << std::endl;
  return 0;
}
