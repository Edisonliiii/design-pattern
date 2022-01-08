#include <cstdlib>
#include <iostream>

class Widget
{
};
class Gadget
{
};

template <class T>
struct OpNewCreator
{
  static T Create()
  {
    return new T;
  }

protected:
  ~OpNewCreator() {}
};

template <class T>
struct MallocCreator
{
  static T Create()
  {
    void* buf = std::malloc(sizeof(T));
    if (!buf)
      return 0;
    return new (buf) T;
  }

protected:
  ~MallocCreator()
  {
    std::cout << "MallocCreator D'tor" << std::endl;
  }
};

template <class T>
struct PrototypeCreator
{
  PrototypeCreator(T* pObj = 0)
    : pPrototype_(pObj) {}
  T* Create()
  {
    return pPrototype_ ? pPrototype_->Clone() : 0;
  }
  T* GetPrototype() { return pPrototype_; }
  void SetPrototype(T* _prototype = nullptr) { this->pPrototype_ = _prototype; }

protected:
  ~PrototypeCreator() {}

private:
  T* pPrototype_;
};

// lib code
template <template <class Created> class CreationPolicy = OpNewCreator> // here, Created can be omitted
class WidgetManager : public CreationPolicy<Widget>
{
public:
  void DoSomething()
  {
    Gadget* pw = CreationPolicy<Gadget>().Create();
    (void)pw; // no use
  }

  void SwitchPrototype(Widget* pNewPrototype)
  {
    CreationPolicy<Widget>& myPolicy = *this;
    delete myPolicy.GetPrototype();
    myPolicy.SetPrototype(pNewPrototype);
  }

private:
};

typedef WidgetManager<MallocCreator> MyWidgetManager;

int main(int argc, char const* argv[])
{
  WidgetManager<> widgetManager1;
  MyWidgetManager* widgetManager2 = new MyWidgetManager();
  delete widgetManager2;
  widgetManager2 = nullptr;
  MallocCreator<Widget>* castedWidgetManager2 = dynamic_cast<MallocCreator<Widget> *>(widgetManager2);
  // delete castedWidgetManager2;
  return 0;
}
