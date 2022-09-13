#include <iostream>
#include <mutex>
#include <thread>

std::once_flag f1, f2;

void do_once() {
  std::call_once(f1, []() { std::cout << "here is do_once!" << std::endl; });
}

void do_once_exception(bool do_throw) {
  if (do_throw) {
    std::cout << "here is do_once_exception with exception!" << std::endl;
    // exception will not flip once_flag
    throw std::exception();
  }
  // return will flip once_flag
  std::cout << "here is do_once_exception without exception" << std::endl;
}

void do_once_e_call(bool do_throw) {
  try {
    std::call_once(f2, do_once_exception, do_throw);
  } catch (...) {
  }
}

int main() {
  // std::cout << f1 << std::endl;
  // return 0;
  std::thread st1(do_once);
  std::thread st2(do_once);
  std::thread st3(do_once);
  std::thread st4(do_once);
  st1.join();
  st2.join();
  st3.join();
  st4.join();

  std::thread t1(do_once_e_call, true);
  std::thread t2(do_once_e_call, true);
  std::thread t3(do_once_e_call, false);
  std::thread t4(do_once_e_call, true);
  t1.join();
  t2.join();
  t3.join();
  t4.join();
}