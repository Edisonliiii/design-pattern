#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <mutex>
#include <numeric>
#include <string>
#include <thread>
#include <vector>

class thread_guard {
 private:
  std::thread& t;

 public:
  explicit thread_guard(std::thread& t_) : t(t_) {}
  ~thread_guard() {
    if (t.joinable()) {
      t.join();
    }
  }
  thread_guard(thread_guard const&) = delete;
  thread_guard& operator=(thread_guard const&) = delete;
};