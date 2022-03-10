#include <iostream>
#include <string>
#include <memory>

class Address {
public:
    std::string street;
    std::string city;
    int suite;

    Address(std::string _s, std::string _c, int _sui) : street(_s), city(_c), suite(_sui) {}

    friend std::ostream& operator<<(std::ostream& os, const Address& obj) {
        return os <<"street:\t"<<obj.street<<"\ncity:\t"<<obj.city
                  <<"\nsuite:\t"<<obj.suite<<"\n----------------";
    }
}; // Address

class Employee {
public:
    std::string name;
    Address* work_addr;

    // c'tor & d'tor
    Employee(std::string _name, Address* const _work_addr) : name(_name), work_addr(new Address(*_work_addr)) {}
    ~Employee() {delete work_addr;}
    // copy c'tor
    Employee(const Employee& other) : name(other.name), work_addr(new Address(*other.work_addr)) {}
    // << operator
    friend std::ostream& operator<<(std::ostream& os, const Employee& obj) {
        return os<<"name:\t"<<obj.name<<"\naddress:\t"<<*obj.work_addr;
    }
}; // Employee


class EmployeeFactory {
private:
	// 这里解释了如何在prototype基础上构造
    static std::unique_ptr<Employee> NewEmployee(std::string _name, int _suite, Employee& proto) {
        std::unique_ptr<Employee> result = std::make_unique<Employee>(proto);
        result->name = _name;
        result->work_addr->suite = _suite;
        return result;
    }
public:
    static Employee main, aux;
    static std::unique_ptr<Employee> NewMainOfficeEmployee(std::string name, int suite) {
        return NewEmployee(name, suite, main);
    }
    static std::unique_ptr<Employee> NewAuxOfficeEmployee(std::string name, int suite) {
        return NewEmployee(name, suite, aux);
    }
};

// Build prototypes
Address* ad1 = new Address("123 East Dr", "London", 0);
Address* ad2 = new Address("123B East Dr", "London", 0);
//std::string s1 = "";
Employee EmployeeFactory::main("", ad1);
Employee EmployeeFactory::aux("", ad2);

int main(int argc, char const *argv[])
{
    std::unique_ptr<Employee> John = EmployeeFactory::NewMainOfficeEmployee("John", 100);
    std::unique_ptr<Employee> Jane = EmployeeFactory::NewAuxOfficeEmployee("Jane", 123);

    std::cout<< *John << std::endl << *Jane << std::endl;
	return 0;
}






