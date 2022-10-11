
#include <functional>
#include <future>
#include <iostream>
#include <thread>

void func(std::future<int>& fut) {
  int x = fut.get();
  std::cout << "value: " << x << std::endl;
}

int main() {
  /**
   * @brief promise 作用类似于 packed_task
   * packed_task 是一个更完备的promise 已经做好了func2future的mapping
   *
   */
  std::promise<int> prom;
  std::future<int> fut = prom.get_future();
  std::thread t(func, std::ref(fut));
  prom.set_value(144);
  t.join();
  return 0;
}