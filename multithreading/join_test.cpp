/**
 * @file join_test.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-05-02
 *
 * @copyright Copyright (c) 2022
 *
 *
 *
 *
 * [Thread order and their c'tors]
 * join(): has nothing to do with which thread obj is run first
 *         It only tell the main thread to wait it come back
 */
#include <chrono>    // std::chrono::seconds
#include <iostream>  // std::cout
#include <thread>    // std::thread, std::this_thread::sleep_for

void pause_thread(int n) {
  std::cout << "pause of " << n << " seconds ended " << std::endl;
}

int main() {
  std::cout << "Spawning 3 threads...\n";
  std::thread t1(pause_thread, 1);
  std::thread t2(pause_thread, 2);
  std::thread t3(pause_thread, 3);
  std::cout << "Done spawning threads. Now waiting for them to join:\n";
  t1.join();
  t2.join();
  t3.join();
  std::cout << "All threads joined!\n";

  return 0;
}