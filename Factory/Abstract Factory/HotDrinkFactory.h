#pragma once

#ifndef HOTDRINKFACTORY_H
#define HOTDRINKFACTORY_H

#include <memory>

class HotDrink;    // forwarding declaration
// abstract factory
class HotDrinkFactory {
public:
    virtual std::unique_ptr<HotDrink> make() const = 0;
    virtual ~HotDrinkFactory(){}
}; // HotDrinkFactory

#endif