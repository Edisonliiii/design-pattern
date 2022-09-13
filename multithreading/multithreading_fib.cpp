#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <utility>
#include <vector>
std::mutex m_a, m_b, m_c;
long a = 1, b = 1, c;
void update() {
  {  // Note: std::lock_guard or atomic<int> can be used instead
    std::unique_lock<std::mutex> lk(m_a);
    a++;
  }

  {  // Note: see std::lock and std::scoped_lock for details and alternatives
    std::unique_lock<std::mutex> lk_b(m_b, std::defer_lock);
    std::unique_lock<std::mutex> lk_c(m_c, std::defer_lock);
    std::lock(lk_b, lk_c);
    b = std::exchange(c, b + c);
  }
}

int main() {
  std::chrono::high_resolution_clock::time_point begin_time =
      std::chrono::high_resolution_clock::now();
  // std::vector<std::thread> threads;
  // for (unsigned i = 0; i < 120; ++i) threads.emplace_back(update);

  // for (auto& i : threads) i.join();
  // std::chrono::high_resolution_clock::time_point stop_time =
  //     std::chrono::high_resolution_clock::now();

  for (long i = 0; i < 11; ++i) {
    c = a + b;
    a = b;
    b = c;
  }
  std::chrono::high_resolution_clock::time_point stop_time =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> slapsed =
      std::chrono::duration_cast<std::chrono::duration<double>>(stop_time -
                                                                begin_time);
  std::cout << "time takes " << slapsed.count() * 1000 << "ms" << std::endl;
  // std::cout << a << "'th and " << a + 1 << "'th Fibonacci numbers: " << b
  //           << " and " << c << '\n';
  std::cout << c << std::endl;
}