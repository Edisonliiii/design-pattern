#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

class Point {
private:
    double x, y;
    // make it private, no problem to public it, but will create a ambiguity, cuz there would be 2 c'tor
    Point(double _x, double _y) : x(_x), y(_y) {}

    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        return os << "x: "<<point.x<<" y: "<<point.y;
    }
    // 友元类的所有成员函数都是另一个类的friend 函数 都可以访问另一个类中的所有信息 private included
    // cuz c'tor has been invisiable to PointFactory, 
    friend class PointFactory;
};

class PointFactory {
public:
    static Point NewCartesian(double _x, double _y) {return Point(_x, _y);}
    static Point NewPolar(double _r, double _theta) {return Point(_r*cos(_theta), _r*sin(_theta));}
}; // PointFactory

int main(int argc, char const *argv[])
{
    Point cartesianPoint = PointFactory::NewCartesian(1.1, 2.2);
    Point polarPoint = PointFactory::NewPolar(2.0, M_PI_4);

    std::cout<< cartesianPoint << std::endl;
    std::cout<< polarPoint << std::endl;

    return 0;
}