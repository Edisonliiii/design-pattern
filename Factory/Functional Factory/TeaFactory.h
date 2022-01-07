#pragma once

#include <memory>
#include "HotDrink.h"
#include "HotDrinkFactory.h"

#ifndef TEAFACTORY_H
#define TEAFACTORY_H

class Tea;
class TeaFactory : public HotDrinkFactory{
public:
    std::unique_ptr<HotDrink> make() const override { return std::make_unique<Tea>(); }
    ~TeaFactory(){}
}; // TeaFactory

#endif