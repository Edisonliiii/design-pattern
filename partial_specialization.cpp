// primary template
template <typename T>
class List {
public:
  // ...
  void append(T const&);
  inline std::size_t length() const;
}; // List


// there is an issue, List<void*> will recursively contain a member of that same List<void*> type
// then we need a partial specialization
template <typename T>
class List<T*>
{
private:
  List<void*> impl;
  // ...
public:
  // ...
  inline void append(T* p) { impl.append(p); }
  inline std::size_t length() const { return impl.length() }
};

// will solve the issue, because full spcz(specialization) are preferred over partial specialization
template<>
class List<void*>
{
  //...
  void append(void* p);
  inline std::size_t length() const;
};

// pointer-to-member partial spcz
template<typename C>
class List<void* C::*>
{
public:
  using ElementType = void* C::*;
  //...
  void append(ElementType pm);
  inline std::size_t length() const;
  //...
};

// partial spcz for any pointer2member except pointer2void*
// because it has been specifically impl earlier
// the upper one should be more specilized than this one
template<typename T, typename C>
class List<T* C::*>
{
private:
  List<void* C::*> impl;
public:
  using ElementType = void* C::*;
  //...
  inline void append(ElementType pm) { impl.append((void* C::*)pm); }
  inline std::size_t length() const {
    return impl.length();
  }
  //...
};