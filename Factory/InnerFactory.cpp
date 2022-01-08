#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

class Point {
private:
    double x, y;
    Point(double _x, double _y) : x(_x), y(_y) {}
    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
         return os << "x: "<<point.x << " y: "<<point.y;
    }
public:
    // inner class <--> outer class (可以互访private)
    class PointFactory {
    public:
    	static Point NewCartesian(double x, double y) { return Point(x, y); }
    	static Point NewPolar(double x, double y) { return Point(x*cos(y), x*sin(y)); }
	}; // PointFactory
}; // Point

int main(int argc, char const *argv[])
{
    Point p = Point::PointFactory::NewCartesian(1.1, 2.2);
    std::cout<< p << std::endl;
	return 0;
}

