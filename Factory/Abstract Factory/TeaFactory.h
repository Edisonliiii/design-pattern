#pragma once

#ifndef TEAFACTORY_H
#define TEAFACTORY_H

#include <memory>
#include "HotDrinkFactory.h"

class HotDrink;
class Tea;
class TeaFactory : public HotDrinkFactory {
public:
     std::unique_ptr<HotDrink> make() const override { return std::make_unique<Tea>(); }
     ~TeaFactory(){}
}; // TeaFactory

#endif