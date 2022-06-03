/**
 * @file spin_lock_prac.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-05-10
 *
 * @copyright Copyright (c) 2022
 *
 *
 * lock A = False
 *
 * lock: while (A.isheld()==False) {}
 * unlock: A <- True
 */
#include <algorithm>
#include <atomic>
#include <cstddef>
#include <iostream>
#include <syncstream>
#include <thread>
#include <vector>

struct tas_lock {
  std::atomic<bool> lock_ = {false};

  void lock() {
    while (lock_.exchange(true)) {
      // busy wait and then do things
    };
  }
  // release the lock
  void unlock() { lock_.store(false); }
}