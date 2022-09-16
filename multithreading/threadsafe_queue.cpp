#include <chrono>
#include <condition_variable>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <shared_mutex>
#include <string>
#include <thread>

template <typename T>
class threadsafe_queue {
 private:
  mutable std::mutex m;
  std::condition_variable cv;
  std::queue<T> q;

 public:
  threadsafe_queue();
  threadsafe_queue(const threadsafe_queue&);
  threadsafe_queue operator=(const threadsafe_queue&) = delete;

  void push(T new_value) {
    {
      std::lock_guard<std::mutex> lk(m);
      q.push(new_value);
    }
    cv.notify_one();
  }

  bool try_pop(T& value) {
    std::lock_guard<std::mutex> lk(m);
    if (q.empty()) return false;
    value = q.front();
    q.pop();
    return true;
  }

  std::shared_ptr<T> try_pop() {
    std::lock_guard<std::mutex> lk(m);
    if (q.empty()) return std::shared_ptr<T>();
    std::shared_ptr<T> res(std::make_shared<T>(q.front()));
    q.pop();
    return res;
  }

  void wait_and_pop(T& value) {
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [] { return !q.empty(); });
    value = q.front();
    q.pop();
  }

  std::shared_ptr<T> wait_and_pop() {
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [] { return !q.empty(); });
    std::shared_ptr<T> res(std::make_shared<T>(q.front()));
    q.pop();
    return res;
  }

  bool empty() const {
    std::lock_guard<std::mutex> lk(m);
    return q.empty();
  }
};
