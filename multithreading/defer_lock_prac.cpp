#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <list>
#include <mutex>
#include <numeric>
#include <string>
#include <thread>
#include <vector>

class some_big_object {};
void swap(some_big_object& l, some_big_object& r);

class X {
 private:
  some_big_object some_detail;
  std::mutex m;

 public:
  X(some_big_object const& val) : some_detail(val) {}
  friend void swap(X& l, X& r) {
    if (&l == &r) return;
    // normally, mutex will get held at once e.g. using lock_guard
    // here, mutexes are unlocked because we flag it using defer_lock
    std::unique_lock<std::mutex> lock_a(l.m, std::defer_lock);
    std::unique_lock<std::mutex> lock_b(r.m, std::defer_lock);
    // we lock them here
    // unique_lock obj provide lock & unlock and try_lock
    std::lock(lock_a, lock_b);
    swap(l.some_detail, r.some_detail);
  }
};