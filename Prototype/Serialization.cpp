#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/serialization.hpp>


class Address {
public:
    std::string street, city;
    int suite;

    friend std::ostream& operator<<(std::ostream& os, const Address& obj) {
        return os << "street:\t" << obj.street << "\ncity:\t" << obj.city
                  << "\nsuite:\t" << obj.suite << "\n-------------------";
    }
private:
    friend class boost::serialization::access;

    template<class A>
    void serialize(Ar& ar, const unsigned int version) {
        ar& street;
        ar& city;
        ar& suite;
    }
}; // Address

class Employee {
public:
    std::string name;
    Address* address;
    
}; // Employee

int main(int argc, char const *argv[])
{
	
	return 0;
}