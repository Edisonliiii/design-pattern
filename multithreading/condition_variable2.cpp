#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>

std::condition_variable cv;
std::mutex cv_m;

int i = 0;

void waits() {
  std::unique_lock<std::mutex> lk(cv_m);
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cerr << "Waiting..." << std::endl;

  // cv.wait(lk, [] { return i == 1; });
  // std::cerr << "...finish waiting. i==1" << std::endl;
}

void signals() {
  // std::this_thread::sleep_for(std::chrono::seconds(1));
  {
    std::unique_lock<std::mutex> lk(cv_m);
    std::cerr << "Notifying...." << std::endl;
  }
  cv.notify_all();

  std::this_thread::sleep_for(std::chrono::seconds(1));
  {
    std::unique_lock<std::mutex> lk(cv_m);
    i = 1;
    std::cerr << "Notifying again...." << std::endl;
  }
  cv.notify_all();
}

int main() {
  std::thread t1(waits), t4(signals), t2(waits), t3(waits);
  t1.join();
  t2.join();
  t3.join();
  t4.join();
}
