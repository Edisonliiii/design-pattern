#include "PersonBuilderBase.h"
#include "Person.h"
#ifndef PERSONBUILDER_H
#define PERSONBUILDER_H

/* This class is not meant to be inherited: this is only meant as a utility that lets us initiate
   the process of setting up a builder
 */
class PersonBuilder : public PersonBuilderBase {
private:
    // this is the obj we are building up
    Person p;
public:
    PersonBuilder() : PersonBuilderBase(p) {}    // 相當於間接性繼承了PersonBuilderBase的c'tor
}; // Person builder

#endif