#include <iostream>
#include <memory>

class Proxy {
 public:
  int val = 100;
  Proxy() {}
  Proxy(const int val) : val(val) { std::cout << "c'tor" << std::endl; }
  Proxy(const Proxy& obj) { val = obj.val; }
  ~Proxy() { std::cout << "d'tor" << std::endl; }
};  // Proxy

int main(int argc, char const* argv[]) {
  std::shared_ptr<Proxy> ptr_1 = std::make_shared<Proxy>(10);
  // std::cout << "object value: " << *ptr_1 << std::endl;

  std::cout << "object address: " << ptr_1.get() << std::endl;

  std::cout << "ref count after ptr_1: " << ptr_1.use_count() << std::endl;

  std::shared_ptr<Proxy> ptr_2 = ptr_1;

  std::cout << "object address: " << ptr_2.get() << std::endl;

  std::cout << "ref count after ptr_2, ptr_1: " << ptr_1.use_count()
            << std::endl;

  std::cout << "ref count after ptr_2, ptr_2: " << ptr_2.use_count()
            << std::endl;

  std::weak_ptr<Proxy> ptr_3 = ptr_2;

  std::cout << "ref count after ptr_2, ptr_1: " << ptr_1.use_count()
            << std::endl;

  std::cout << "ref count after ptr_2, ptr_2: " << ptr_2.use_count()
            << std::endl;

  return 0;
}
