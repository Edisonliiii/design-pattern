#pragma once
#include <string>
#include <map>
#include <memory>
#include <functional>

#include "CoffeeFactory.h"
#include "TeaFactory.h"

#ifndef DRINKFACTORY_H
#define DRINKFACTORY_H

/*  Builder和Factory的差别在于 Builder可以分部分初始化obj 而Factory是返回不同类别的object 但不能分部分初始化 
 */

class HotDrink;
class DrinkFactory {
private:
    std::map<std::string, std::unique_ptr<HotDrinkFactory>> factories;
public:
    DrinkFactory() {
        factories["coffee"] = std::make_unique<CoffeeFactory>();
        factories["tea"] = std::make_unique<TeaFactory>();
    }

    inline std::unique_ptr<HotDrink> make_drink(const std::string& name, int val) {
        std::unique_ptr<HotDrink> drink = factories[name]->make();
        drink->prepare(val);
        return drink;
    }
}; // DrinkFactory

class DrinkWithVolumeFactory {
private:
    std::map<std::string, std::function<std::unique_ptr<HotDrink>(int val)>> factories;
public:
	// c'tor
	DrinkWithVolumeFactory() {
		factories["coffee"] = [](int val) {
			std::unique_ptr<HotDrink> coffee = std::make_unique<Coffee>();
			coffee->prepare(val);
            return coffee;
		}; // 直接返回初始化后的coffee对象 只不过对象的类型比较特殊 是一个函数

		factories["tea"] = [](int val) {
            std::unique_ptr<HotDrink> tea = std::make_unique<Tea>();
            tea->prepare(val);
            return tea;
		}; // 直接返回初始化后的tea对象
	}

	inline std::unique_ptr<HotDrink> make_drink(const std::string& name, int val) {
	    return factories[name](val);       // 给对应函数传参
	}

}; // DrinkWithVolumeFactory

#endif