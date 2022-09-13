#include <chrono>
#include <iostream>
#include <map>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>

bool flag;
std::mutex m;

/**
 * @brief
 * There is no deadlock forever
 * 1. default init will acquire lock immediately
 * 2. because of RAII, unique_lock on different thread
 *    will busy-waiting if mutex m is locked somewhere else
 */
void wait_for_flag() {
  std::unique_lock<std::mutex> lk(m);
  while (!flag) {
    lk.unlock();
    std::cout << "unlocked....." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "sleeping....." << std::endl;
    lk.lock();
    std::cout << "locked by " << std::this_thread::get_id() << "....."
              << std::endl;
  }
}

int main(int argc, char const *argv[]) {
  std::thread t(wait_for_flag);
  std::thread t2(wait_for_flag);
  std::thread t3(wait_for_flag);
  std::thread t4(wait_for_flag);
  std::thread t5(wait_for_flag);

  t.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();

  return 0;
}
