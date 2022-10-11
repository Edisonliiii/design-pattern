#include <functional>
#include <future>
#include <iostream>
#include <thread>

/**
 * @brief Difference between packaged_task and promise
 *
 * packaged_task: wrap a function
 * promise: wrap a variable
 *
 * @param in
 * @return int
 */

int func(int in) {
  std::cout << "sleeping for 1 sec..." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));
  return in + 1;
}

int main() {
  // declare a packaged_task
  std::packaged_task<int(int)> task(func);
  // sign the contract with a future var
  std::future<int> fut = task.get_future();
  // move the task to another new thread
  // here, there is no need to use .join() & wait()
  // because we already stub the return value to the future object
  // once the other thread finish the work, let it go
  // no matter what, we already acquire the result
  std::thread(std::move(task), 5).detach();
  // get the result
  std::cout << "result " << fut.get() << std::endl;
  return 0;
}
