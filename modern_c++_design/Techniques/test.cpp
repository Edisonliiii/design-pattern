#include <iostream>

#define DESTINATION_TYPE_TOO_NARROW "Destination_Type_Too_Narrow"

template<bool> struct CompileTimeError;
template<> struct CompileTimeError<true> {};

template<bool> struct CompileTimeChecker { CompileTimeChecker(...); }; // if bool is true, accept anything
template<> struct CompileTimeChecker<false> { };                       // if bool is false

#define STATIC_CHECK(expr) {char unnamed[(expr) ? 1 : 0];}
#define STATIC_CHECK_2(expr) \
  (CompileTimeError<(expr) != 0>())

// -- class ERROR_##msg : generate new class
// -- if initialize the compiletimechecker as true, everything is ok
//    else, error
#define STATIC_CHECK_3(expr, msg) \
  { \
    class ERROR_##msg {}; \
    (void)sizeof CompileTimeChecker<(expr) != 0>((ERROR_##msg())); \
  }

template <class To, class From>
To safe_reinterpret_cast(From from)
{
  std::cout<< (sizeof(From) <= sizeof(To)) <<std::endl;
  //STATIC_CHECK(sizeof(From) < sizeof(To));
  //STATIC_CHECK_2(sizeof(From) <= sizeof(To));
  STATIC_CHECK_3(sizeof(From) <= sizeof(To), DESTINATION_TYPE_TOO_NARROW);
  return reinterpret_cast<To>(from);
}

// 2.5 ----------

template <typename T>
struct Type2Type
{
  typedef T OriginalType;
};

template <class T, class U>
T* Create(const U& arg, Type2Type<T>)
{
  return new T(arg);
}

template <class U>
std::string* Create(const U& arg, Type2Type<std::string>)
{
  std::cout<< "String partially specialization." <<std::endl;
  return new std::string(arg);
}



int main(int argc, char const *argv[])
{
  char arr[0];
  int a = 100;
  void* somePointer = &a;
  char c = safe_reinterpret_cast<long long>(somePointer);
  std::cout<< true <<std::endl;

  std::cout<< "---2.5---" <<std::endl;
  std::string* pStr = Create("hello", Type2Type<std::string>());
  std::cout<< *pStr <<std::endl;
  return 0;
}












