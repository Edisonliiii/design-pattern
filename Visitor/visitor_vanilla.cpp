#include <iostream>
#include <list>
using namespace std;

/* [multiple dispatch]
which function to call is based on the runtime types of multiple dispatch

*/

class Element;
class ConcreteElementA;
class ConcreteElementB;

class Visitor
{
public:
  virtual void VisitConcreteElementA(ConcreteElementA* ca) = 0;
  virtual void VisitConcreteElementB(ConcreteElementB* cb) = 0;
};

class ConcreteVisitorA : public Visitor
{
public:
  void VisitConcreteElementA(ConcreteElementA* ca) override
  {
    cout << "ConcreteVisitorA::VisitConcreteElementA" << endl;
  }
  void VisitConcreteElementB(ConcreteElementB* cb) override
  {
    cout<< "ConcreteVisitorA::VisitConcreteElementB" << endl;
  }
};

class ConcreteVisitorB : public Visitor
{
public:
  void VisitConcreteElementA(ConcreteElementA* ca) override
  {
   cout << "ConcreteVisitorB::VisitConcreteElementA" << endl; 
  }
  void VisitConcreteElementB(ConcreteElementB* cb) override
  {
    cout<< "ConcreteVisitorB::VisitConcreteElementB" << endl;
  }
};

class ConcreteVisitorC : public Visitor
{
public:
  void VisitConcreteElementA(ConcreteElementA* ca) override
  {
   cout << "ConcreteVisitorC::VisitConcreteElementA" << endl; 
  }
  void VisitConcreteElementB(ConcreteElementB* cb) override
  {
    cout<< "ConcreteVisitorC::VisitConcreteElementB" << endl;
  }
};

// interface
class Element
{
public:
  virtual void Accept(Visitor* visitor) = 0;
};

// element A
class ConcreteElementA : public Element
{
public:
  // double dispatch appears here
  // 1. the type of visitor, there are more than one targeting method in each visitor for every elemtn
  // 2. the type of current element, 
  void Accept(Visitor* visitor)
  {
    cout << "ConcreteElementA: ";
    visitor -> VisitConcreteElementA(this);
  }

  void OperationA() {
    cout << "OperationA" << endl;
  }
};

// element B
class ConcreteElementB : public Element
{
public:
  void Accept(Visitor* visitor)
  {
    cout << "ConcreteElementB: ";
    visitor -> VisitConcreteElementB(this);
  }

  void OperationB() {
    cout << "OperationB" << endl;
  }
};

// object collection
class ObjectStructure
{
private:
  list<Element*> elements;         // objs 
public:
  void Attach(Element* element)
  {
    elements.push_back(element);
  }
  void Detach(Element* element)
  {
    elements.remove(element);
  }
  void Accept(Visitor* visitor) // 根据指定的visitor 跑定制的方法
  {
    for (auto e = elements.begin(); e != elements.end(); ++e)
    {
      (*e)->Accept(visitor);
    }
  }
};




int main() {
    ObjectStructure* o = new ObjectStructure();

    ConcreteElementA* ca = new ConcreteElementA();
    ConcreteElementB* cb = new ConcreteElementB();

    o->Attach(ca);
    o->Attach(cb);

    ConcreteVisitorA* cv1 = new ConcreteVisitorA();
    ConcreteVisitorB* cv2 = new ConcreteVisitorB();
    ConcreteVisitorC* cv3 = new ConcreteVisitorC();

    o->Accept(cv1);
    // ConcreteElementA: ConcreteVisitorA::VisitConcreteElementA
    // ConcreteElementB: ConcreteVisitorA::VisitConcreteElementB
    o->Accept(cv2);
    // ConcreteElementA: ConcreteVisitorB::VisitConcreteElementA
    // ConcreteElementB: ConcreteVisitorB::VisitConcreteElementB
    o->Accept(cv3);
    // ConcreteElementA: ConcreteVisitorC::VisitConcreteElementA
    // ConcreteElementB: ConcreteVisitorC::VisitConcreteElementB
    delete ca;
    delete cb;
    delete cv1;
    delete cv2;
    delete cv3;
    delete o;

    return 0;
}









