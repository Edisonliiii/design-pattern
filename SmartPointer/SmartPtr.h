template <class T>
class SmartPtr {
 public:
  explicit SmartPtr(T* pointee) : pointee(pointee) {}
  SmartPtr& operator=(const SmartPtr& other);
  ~SmartPtr();
  T* operator=() const { return *pointee; }

 private:
  T* pointee;
};  // SmartPtr