#pragma once

#include <memory>
#include "HotDrink.h"
#include "HotDrinkFactory.h"

#ifndef COFFEEFACTORY_H
#define COFFEEFACTORY_H

class Coffee;
class CoffeeFactory : public HotDrinkFactory {
public:
    std::unique_ptr<HotDrink> make() const override { return std::make_unique<Coffee>(); }
    ~CoffeeFactory(){}
}; // CoffeeFactory

#endif