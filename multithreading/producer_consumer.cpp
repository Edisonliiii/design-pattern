#include <chrono>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

std::mutex g_mutex;
bool g_ready = false;
int g_data = 0;

int produceData() {
  int randD = rand() % 1000;
  cout << "data: " << randD << endl;
  return randD;
}

void consumeData(int data) { cout << data << endl; }

// consumer
void consumer() {
  while (true) {
    while (!g_ready) {  // false, waiting
      this_thread::sleep_for(chrono::seconds(1));
    }
    // true, out!
    unique_lock<mutex> ul(g_mutex);
    consumeData(g_data);
    g_ready = false;
    ul.unlock();
  }
}

// producer
void producer() {
  while (true) {
    // false, doing things, consumer must be waiting
    unique_lock<mutex> ul(g_mutex);
    g_data = produceData();
    g_ready = true;
    ul.unlock();
    // true, waiting, producer must be doing
    while (g_ready) {
      this_thread::sleep_for(chrono::seconds(1));
    }
  }
}

void consumerThread() { consumer(); }

void producerThread() { producer(); }

int main() {
  std::thread t1(consumerThread);
  std::thread t2(producerThread);
  t1.join();
  t2.join();
  return 0;
}