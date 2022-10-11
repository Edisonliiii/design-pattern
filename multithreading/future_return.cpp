#include <future>
#include <iostream>
#include <string>

/**
 * @brief
 *
 * std::launch::async -- asynchronous evaluation
 * std::launch::deferred -- lazy evaluation
 * @return int
 */

int find_the_answer_to_ltuae() {
  std::this_thread::sleep_for(std::chrono::seconds(3));
  return 1;
};

void do_other_things() {
  std::cout << "Doing other things..." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(4));
  std::cout << "Other things done!" << std::endl;
  return;
};

// struct X {
//   int val = 100;
//   X(){};
//   X(X const &x) {  // not a legit implementation, for convenient
//     val = x.val;
//   }
//   void foo(int, std::string const &) {
//     std::cout << "calling X::foo...." << std::endl;
//     return;
//   };
//   std::string bar(std::string const &) {
//     std::cout << "calling X::bar...." << std::endl;
//     return "";
//   };
// };

// X x;

// std::future<void> xfoo = std::async(&X::foo, &x, 42, "hello");
// std::future<std::string> xbar = std::async(&X::bar, &x, "seya");

// struct Y {
//   double operator()(double) { return .0; };
// };
// Y y;
// std::future<double> yoperator = std::async(Y(), 3.1);  // call move c'tor
// std::future<double> yoperator2 =
//     std::async(std::ref(y), 3.1);  // call copy c'tor

// X baz(X &) {
//   std::cout << "calling baz...." << std::endl;
//   return X();
// };                                                        // call copy-c'tor
// std::future<X> xcopyctor = std::async(baz, std::ref(x));  // baz(x)

// class move_only {
//  public:
//   move_only();
//   move_only(move_only &&m) {
//     if (this == &m) return *this;
//     return *this;
//   };
//   move_only(move_only const &) = delete;
//   move_only &operator=(move_only &&);
//   move_only &operator=(move_only const &) = delete;

//   void operator()();
// };

// std::future<void> move_onlymctor =
//     std::async(move_only());  // plus call move c'tor

int main(int argc, char const *argv[]) {
  // if the launch policy is not explicitly specified, then the behavior of
  // async will not be predictable. It depends on the resource availability
  // to choose either std::launch::async or std::launch::deferred
  std::future<int> ans =
      std::async(std::launch::async, find_the_answer_to_ltuae);
  // std::async(std::launch::deferred, find_the_answer_to_ltuae);
  do_other_things();
  std::cout << "Result: " << ans.get() << std::endl;
  return 0;
}
