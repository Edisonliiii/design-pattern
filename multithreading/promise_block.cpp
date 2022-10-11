#include <future>
#include <iostream>
#include <thread>

int main(int argc, char const *argv[]) {
  std::promise<int> prom;
  std::future<int> f = prom.get_future();

  std::thread t(
      [](std::promise<int> p) {  // p as a param
        std::this_thread::sleep_for(std::chrono::seconds(2));
        p.set_value(100);
      },
      std::move(prom));

  std::cout << f.get() << std::endl;
  if (t.joinable()) t.join();
  return 0;
}
