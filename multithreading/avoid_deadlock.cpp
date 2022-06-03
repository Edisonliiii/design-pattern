/**
 [Deadlock]
 threads need to hold both lock on something, they are waiting for each other

 -- lock the two mutexes in the same order e.g. always lock A before B
 -- avoid thread join cycle
 -- avoid nested lock
 -- avoid calling user-supplied code while holding a lock
 -- acquire locks in a fixed order (even read-only can also cause deadlock)
    e.g. a linked-list L, each node has its own mutex
         iterator a = L.begin()
         iterator b = L.end()
         a: increasing, b: decreasing
         at one time: a->next = b, b->next = a
         a will need it's next mutex to read
         b will need it's next mutex to read
         deadlock!
*/
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

class hierarchical_mutex {
  std::mutex internal_mutex;
  unsigned long const hierarchical_value;  // max one
  unsigned long previous_hierarchy_value;  // temporarily hold the value
  // representing the hierarchy value for the current thread
  // it's ULONG_MAX, so at the beginning, all threads could be locked
  static thread_local unsigned long this_thread_hierarchy_value;

  void check_for_hierarchy_violation() {
    if (this_thread_hierarchy_value <= hierarchical_value) {
      throw std::logic_error("mutex hierarchy violated!");
      // not pass
    }
    // pass
  }

  void update_hierarchy_value() {  // update previous h-value and
                                   // (decrease)this_thread_h_value
    previous_hierarchy_value = this_thread_hierarchy_value;
    this_thread_hierarchy_value = hierarchical_value;
  }

 public:
  explicit hierarchical_mutex(unsigned long value)
      : hierarchical_value(value), previous_hierarchy_value(0) {}

  // lock_guard object will use lock and unlock functions
  void lock() {
    check_for_hierarchy_violation();
    internal_mutex.lock();
    update_hierarchy_value();
  }

  void unlock() {
    if (this_thread_hierarchy_value != hierarchical_value) {
      throw std::logic_error("mutex hierarchy violated!");
      // not pass
    }
    // pass (this_thread_hierarchy_value == hierarchical_value)
    // current thread is the one being run
    this_thread_hierarchy_value = previous_hierarchy_value;
    internal_mutex.unlock();
  }

  bool try_lock() {
    check_for_hierarchy_violation();
    if (!internal_mutex.try_lock()) return false;
    update_hierarchy_value();
    return true;
  }
};  // hierarchical_mutex

// init as max at the beginning
thread_local unsigned long hierarchical_mutex::this_thread_hierarchy_value(
    ULONG_MAX);

hierarchical_mutex high_level_mutex(1000);
hierarchical_mutex low_level_mutex(100);
hierarchical_mutex other_level_mutex(300);

int do_low_level_stuff() {
  // std::cout << "doing lower level stuff" << std::endl;
  return -1;
};  // doesn't lock any mutexes
void do_high_level_stuff(int some_param){};
void do_other_stuff(){};

int low_level_func() {
  std::lock_guard<hierarchical_mutex> llm(low_level_mutex);
  std::cout << "low level mutex" << std::endl;
  return do_low_level_stuff();
}

void high_level_func() {
  // lock_guard<..> it can only accept BasicLockable elements
  // BasicLockable: have member function m.lock() & m.unlock()
  // transfer ownership
  std::lock_guard<hierarchical_mutex> hlm(high_level_mutex);
  std::cout << "high level mutex" << std::endl;
  do_high_level_stuff(low_level_func());
}

void other_stuff() { high_level_func(); }
void other_stuff_lower() { std::cout << "other level mutex" << std::endl; }
void thread_a() { high_level_func(); }
void thread_b() {
  std::lock_guard<hierarchical_mutex> olm(other_level_mutex);
  // other_stuff();
  other_stuff_lower();
}

int main(int argc, char const *argv[]) {
  std::thread ta(thread_a);
  std::thread tb(thread_b);  // illegal, because we tried to lock higher
  // level lock after holding lower level lock
  ta.join();
  tb.join();
  std::cout << "[Main] All threads joined!\n";
  return 0;
}
