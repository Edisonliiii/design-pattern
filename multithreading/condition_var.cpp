#include <chrono>
#include <condition_variable>
#include <iostream>
#include <map>
#include <mutex>
#include <queue>
#include <shared_mutex>
#include <string>
#include <thread>

struct data_chunk {};

std::mutex mut;
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;

bool more_data() { return true; }
bool is_last_chunk(data_chunk d) { return true; }
data_chunk prepare_data() { return data_chunk(); }
void process_data(data_chunk d) {}

void data_preparation_thread() {
  while (more_data()) {
    data_chunk const nxt_data = prepare_data();
    {  // critical area
      std::lock_guard<std::mutex> lk(mut);
      data_queue.push(nxt_data);
    }
    data_cond.notify_one();
  }
}

void data_processing_thread() {
  while (true) {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [] { return !data_queue.empty(); });
    data_chunk nxt_data = data_queue.front();
    data_queue.pop();
    lk.unlock();
    process_data(nxt_data);
    if (is_last_chunk(nxt_data)) break;
  }
}