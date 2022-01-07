#include "PersonBuilderBase.h"
#include <string>
#ifndef PERSONJOBBUILDER_H
#define PERSONJOBBUILDER_H

class PersonJobBuilder : public PersonBuilderBase
{
private:
    typedef PersonJobBuilder Self;
public:
    explicit PersonJobBuilder(Person& person) : PersonBuilderBase{person} {}
    Self& at(std::string company_name_) {person.company_name = company_name_; return *this;}
    Self& as_a(std::string position_) {person.position = position_; return *this;}
    Self& earning(int annual_income_) {person.annual_income = annual_income_; return *this;}
}; // person job builder

#endif