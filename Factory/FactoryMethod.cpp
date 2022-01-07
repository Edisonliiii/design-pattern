#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

enum class PointType {cartesian, polar};

class Point {
protected:
	double x, y;
    Point(const double _x, const double _y) : x(_x), y(_y) {}
public:
	// friend 可以直接访问类的私有成员 是非成员函数 定义在类外的普通函数 不属于任何类 但需要在类的定义中加以声明
	// 生命可以放在private / ppublic没什么区别
	// 一个函数可以是多个类的friend 只需要在各个类中分别声明 且不能被继承
    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
    	return os << "x: "<< point.x << "y: "<< point.y;
    }
    // each of these static funcs is called Factory Method
    // Create Point and then return it
    static Point NewCartesian (double _x, double _y) { return Point(_x, _y); }
    static Point NewPolar (double _r, double _theta) { return Point(_r, _theta); }
}; // Point


int main(int argc, char const *argv[])
{
	Point p = Point::NewPolar(5, M_PI_4);
	std::cout<< p <<std::endl;
	return 0;
}