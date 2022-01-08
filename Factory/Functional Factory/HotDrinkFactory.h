#pragma once
#include <memory>
#ifndef HOTDRINKFACTORY_H
#define HOTDRINKFACTORY_H

class HotDrink;
class HotDrinkFactory {
public:
    virtual std::unique_ptr<HotDrink> make() const = 0;
    virtual ~HotDrinkFactory(){}
}; // HotDrinkFactory

#endif