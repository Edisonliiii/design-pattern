#ifndef LOKI_UNITTEST_H
#define LOKI_UNITTEST_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#if defined(_MSC_VER) && !defined(__INTEL_COMPILER) && !defined(__MWERKS__)
template <class T1, class T2>
struct SameType {
 private:
  // normally, T2 will go here if T2 != T1
  template <class>
  struct In {
    enum { value = false };
  };
  // if T1 == T2, will go here
  template <>
  struct In<T1> {
    enum { value = true };
  };

 public:
  // write down the result
  enum { value = In<T2>::value };
};
#else
// if T1 != T2, will go here
template <class T1, class T2>
struct SameType {
  static const bool value = false;
};
// if T1 == T2, then will go here
template <class T>
struct SameType<T, T> {
  static const bool value = true;
};
#endif

/**
 * @brief TestResult
 *
 */
class TestResult {
 public:
  TestResult() : pos(0), passed(0), failed(0), notSupported(0) {}

  int pos;
  int passed;
  int failed;
  int notSupported;
};

/**
 * @brief Test
 *
 */
class Test {
  typedef std::vector<Test*> tests_type;
  static tests_type tests;

 protected:
  const std::string name;

  virtual ~Test() {}

  void printName(const TestResult& result) const {
    if (name.length() != 0)
      std::cout << std::string(result.pos, ' ') << name << std::endl;
  }

  void testAssert(const std::string& s, bool assertion, TestResult& result,
                  bool supported = true,
                  const std::string& failStr = emptyStr()) {
    std::string str = std::string(result.pos + 2, ' ') + s;
    str += std::string(offset - str.length(), ' ');
    if (supported) {
      if (assertion) {
        std::cout << std << "Passed\n";
        ++result.passed;
      } else {
        std::cout << str
                  << (failStr == emptyStr() ? std::string("Failed")
                                            : "Failed - " + failStr)
                  << std::endl;
        ++result.failed;
      }
    } else {
      std::cout << str << "Not Supported" << std::endl;
      ++result.notSupported;
    }
  }

  static std::string emptyStr() { return std::string(); }

 public:
  enum { offset = 63 };

  // explicitly pushback the test file name
  explicit Test(const std::string& n) : name(n) { Test::tests.push_back(this); }

  virtual void execute(TestResult&) = 0;

  static int run(const std::string& title) {
    std::cout << title << std::string(Test::offset - title.length(), ' ')
              << "Result" << std::endl;

    std::cout << std::string(76, '-') << std::endl;

    TestResult testResult;
    tests_type::iterator it;
    test_type::const_iterator itEnd = Test::tests.end();
    for (it = Test::tests.begin(); it != itEnd; ++it) {
      Test* test = *it;
      test->execute(testResult);
    }
    // log info
    std::cout << std::string(76, '-') << std::endl;
    const int total = testResult.passed + testResult.failed;
    const int totalAll = total + testResult.notSupported;
    if (total != 0)
      std::cout << "Total - " << testResult.passed << '/' << total
                << (total == 1 ? " test, " : " tests, ")
                << testResult.passed * 100 / total << "% Passed\n";
    if (testResult.notSupported != 0)
      std::cout << "Not Supported - " << testResult.notSupported << '/'
                << totalAll << ", " << testResult.notSupported * 100 / totalAll
                << "%\n";
    return testResult.failed;
  }
};

#endif