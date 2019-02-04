/*
c++ -o testInheritance testInheritance.cpp
*/

#include <iostream>
#include <cmath>
 
class Shape
{
public:
  Shape(double a)
  {
    area = a;
  }
  
  ~Shape()
  {
    std::cout << "I'm the "
	      << "Shape::destructor"
	      << std::endl;
  }

  double getArea()
  {
    return area;
  }

private:
  double area;
};

class Circle: public Shape
{
public:
  Circle(double a, int c) : Shape(a)
  {
    color = c;
  }
  
  ~Circle()
  {
    std::cout << "I'm the "
	      << "Circle::destructor"
	      << std::endl;
  }
  
  double getRadius()
  { 
    return sqrt(getArea() / M_PI);
  }

  int getColor()
  { 
    return color;
  }
  
private:
  int color;
};

int main()
{
  Shape sh(1);
  Circle cir(4,0);
  
  std::cout << "Area: "
	    << sh.getArea() << std::endl;

  std::cout << "Area: "
	    << cir.getArea() << " radius: "
	    << cir.getRadius() << std::endl;
  
  return 0;
}
