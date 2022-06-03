#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <string>
#include <thread>
#include <vector>

struct Record {
  int id;
  // other data...
  std::mutex mutex;
};

std::map<int, std::shared_ptr<Record>> records;

class LockedRecord {
  std::shared_ptr<Record> ptr;
  std::unique_lock<std::mutex> lock;

 public:
  LockedRecord() = default;
  // init record pointer and the unique_lock
  LockedRecord(const std::shared_ptr<Record>& p) : ptr(p), lock(p->mutex) {}
  bool ownsRecord() const { return ptr != nullptr; }
  Record& record() const { return *ptr; }
};

LockedRecord getAndProcess(int id) {
  auto it = records.find(id);
  if (it != records.end()) {
    LockedRecord lr(it->second);
    return lr;  // transfers the lock's ownership
                // no need to use move explicitly, local var
                // cuz compiler will call move
  }
  return {};  // return empty LockedRecord
}

void process(int id) {
  auto lr = getAndProcess(id);
  if (lr.ownsRecord()) {
    std::cout << lr.record().id << std::endl;
  }
}