#pragma once

#include <map>
#include <string>
#include <memory>
#include "CoffeeFactory.h"
#include "TeaFactory.h"
#include "HotDrinkFactory.h"
//class HotDrinkFactory;
class HotDrink;
//class CoffeeFactory;
//class TeaFactory;

class DrinkFactory {
private:
    std::map<std::string, std::unique_ptr<HotDrinkFactory>> hot_factories;
public:
    DrinkFactory() {
        hot_factories["coffee"] = std::make_unique<CoffeeFactory>();
        hot_factories["tea"] = std::make_unique<TeaFactory>();
    }

    std::unique_ptr<HotDrink> make_drink(const std::string& name, int val) {
         std::unique_ptr<HotDrink> drink = hot_factories[name]->make();
         drink->prepare(val);
         return drink;
    }
}; // DrinkFactory