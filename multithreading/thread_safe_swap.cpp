#include <exception>
#include <memory>
#include <mutex>
#include <stack>

class some_big_object {};

void swap(some_big_object& l, some_big_object& r);

class X {
 private:
  some_big_object some_detail;
  std::mutex m;

 public:
  X(some_big_object const& sd) : some_detail(sd) {}
  friend void swap(X& l, X& r) {
    if (&l == &r) return;
    // lock both mutexes
    std::lock(l.m, r.m);  // give all mutexes avoid deadlock init
    // make sure they will be property released
    std::lock_guard<std::mutex> lock_a(l.m, std::adopt_lock);
    std::lock_guard<std::mutex> lock_b(r.m, std::adopt_lock);
    swap(l.some_detail, r.some_detail);
  }

  friend void swap_(X& l, X& r) {
    if (&l == &r) return;
    // using automatic deduction
    // equal to:
    // std::scoped_lock<std::mutex, std::mutex> guard(l, r)
    std::scoped_lock guard(l.m, r.m);
    swap(l.some_detail, r.some_detail);
  }
};  // X