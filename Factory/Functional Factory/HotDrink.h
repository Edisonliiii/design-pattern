#pragma once

#ifndef HOTDRINK_H
#define HOTDRINK_H

class HotDrink {
public:
    virtual void prepare(int volume) = 0;
    virtual ~HotDrink(){}
}; // HotDrink

class Tea : public HotDrink {
public:
    void prepare(int volume) override {
        std::cout << "Take tea bag, boil water, pour " << volume << "ml" << std::endl;
    }
    virtual ~Tea(){}
}; // Tea

class Coffee : public HotDrink {
public:
    void prepare(int volume) override {
        std::cout << "Grind some beans, boil water, pour " << volume << "ml" << std::endl;
    }
    virtual ~Coffee(){}
}; // Coffee

#endif

