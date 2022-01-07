#include "Person.h"

#ifndef PERSONBUILDERBASE_H
#define PERSONBUILDERBASE_H

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase {
protected:
    // ref to the obj that is being built. 相當於一個指針 這裡沒有Person的內存結構 只有一個ref
    // 從這裡開始就是標準的builder和具體實現的分離 作為builder的root 僅僅持有ref
    Person& person;
    // set this c'tor as protected so that only the inheritors can use it (PersonAddressBuilder and PersonJobBuilder)
    explicit PersonBuilderBase(Person& person_) : person{person_} {}
public:
    // give Person a properly defined move constructor
    // 这里是重载Person这个关键字 不是()
    operator Person() {return std::move(person);}
    // builder facets： returning builder facets
    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;
}; // person builder base


#endif