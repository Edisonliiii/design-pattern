#ifndef COW_PTR_H
#define COW_PTR_H
// https://github.dev/HadrienG2/copy-on-write-ptr/blob/master/copy_on_write_ptr.hpp
#include <stdlib.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

template <typename T, typename OwnershipFlag = bool>
class cow_ptr {
 private:
  std::shared_ptr<T> payload;
  OwnershipFlag ownership;

 public:
  cow_ptr(T* ptr) : payload(ptr), ownership(true) {}
  // move semantic
  cow_ptr(cow_ptr&& c_ptr) {
    payload = c_ptr.payload;
    ownership = true;
  }
  // c'tor: do not own the payload
  cow_ptr(const cow_ptr& c_ptr) {
    payload = c_ptr.payload;
    ownership = false;
  }
  // copy assignment
  cow_ptr& operator=(cow_ptr&& c_ptr) = default;
  cow_ptr& operator=(const cow_ptr& c_ptr) {
    payload = c_ptr.payload;
    ownership = false;
  }
  // d'tor, default is sufficient
  ~cow_ptr() = default;

  void cow() {
    // waitforimpl
  }

  // accessors
  const T& read() const { return *payload; }
  void write(T value) {
    cow();
    *payload = value;
  }
};

#endif