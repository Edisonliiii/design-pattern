#pragma once
#include <iostream>
#include <string>

#ifndef HOTDRINK_H
#define HOTDRINK_H

class HotDrink {
public:
    virtual void prepare(int volume) = 0;
    virtual ~HotDrink(){}           // 即便是智能指針 也需要顯式聲明出這個析構函數
}; // HotDrink


class Tea : public HotDrink {
    void prepare(int volume) override {
         std::cout<<"Take tea bag, boil water, pour " << volume << "ml" << std::endl;
    }
public:
    virtual ~Tea(){}               
}; // Tea

class Coffee : public HotDrink {
    void prepare(int volume) override {
        std::cout<< "Grind some beans, boil water, pour " << volume << "ml" << std::endl;
    }
public:
    virtual ~Coffee(){}
}; // Coffee

#endif