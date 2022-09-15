#include <chrono>
#include <condition_variable>
#include <iostream>
#include <map>
#include <mutex>
#include <queue>
#include <shared_mutex>
#include <string>
#include <thread>

std::mutex mut;

void test() {
  std::unique_lock<std::mutex> lk(mut);
  // lk.lock();
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  // lk.unlock();
}

int main(int argc, char const *argv[]) {
  std::thread t1(test);
  std::thread t2(test);
  std::thread t3(test);
  std::thread t4(test);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  return 0;
}
