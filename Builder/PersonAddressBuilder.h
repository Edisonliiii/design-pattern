#include "PersonBuilderBase.h"
#include <string>
#ifndef PERSONADDRESSBUILDER_H
#define PERSONADDRESSBUILDER_H

class PersonAddressBuilder : public PersonBuilderBase {
private:
    typedef PersonAddressBuilder Self;
public:
    explicit PersonAddressBuilder(Person& person) : PersonBuilderBase{person} {}
    Self& at(std::string street_address_) {person.street_address = street_address_; return *this;}
    Self& with_postcode(std::string post_code_) {person.post_code = post_code_; return *this;}
    Self& in(std::string city_) {person.city = city_; return *this;}
}; // person addr builder

#endif