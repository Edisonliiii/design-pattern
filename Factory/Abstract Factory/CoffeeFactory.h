#pragma once

#ifndef COFFEEFACTORY_H
#define COFFEEFACTORY_H

#include <memory>
#include "HotDrinkFactory.h"
#include "HotDrink.h"

class Coffee;
class CoffeeFactory : public HotDrinkFactory{
public:
    std::unique_ptr<HotDrink> make() const override { return std::make_unique<Coffee>(); }
	~CoffeeFactory(){}
}; // CoffeeFactory
#endif