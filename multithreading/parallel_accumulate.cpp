#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <mutex>
#include <numeric>
#include <string>
#include <thread>
#include <vector>

template <typename Iterator, typename T>
struct accumulate_block {
  void operator()(Iterator first, Iterator last, T& result) {
    result = std::accumulate(first, last, result);
  }
};

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
  unsigned long const length = std::distance(first, last);
  if (!length) return init;

  unsigned long const min_per_thread = 25;
  unsigned long const max_threads =
      (length + min_per_thread - 1) / min_per_thread;
  unsigned long const hardware_threads = std::thread::hardware_concurrency();
  unsigned long const num_threads =
      std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
  unsigned long const block_size = length / num_threads;

  std::vector<T> results(num_threads);
  std::vector<std::thread> threads(num_threads - 1);

  Iterator block_start = first;
  for (unsigned long i = 0; i < (num_threads - 1); ++i) {
    Iterator block_end = block_start;
    // move pointer forward
    std::advance(block_end, block_size);
    // init threads, cut the task block by block
    // pass parameters to function accumulate_block
    threads[i] = std::thread(accumulate_block<Iterator, T>(), block_start,
                             block_end, std::ref(results[i]));
    block_start = block_end;
  }

  // enter the critical area here
  accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);
  // outout the critical area here
  // wait all threads come back
  std::for_each(threads.begin(), threads.end(),
                std::mem_fn(&std::thread::join));
  return std::accumulate(results.begin(), results.end(), init);
}

int main(int argc, char const* argv[]) {
  std::vector<int> arr(50000000, 10);
  std::cout << parallel_accumulate<std::vector<int>::iterator, int>(
                   arr.begin(), arr.end(), 0)
            << std::endl;
  return 0;
}
