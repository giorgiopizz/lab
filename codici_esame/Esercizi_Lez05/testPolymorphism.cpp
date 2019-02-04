/*
  c++ -o testPolymorphism testPolymorphism.cpp
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
    std::cout << "Shape::getArea() ";
    return area;
  }

  virtual double getPerimeter()
  {
    std::cout << "Shape::getPerimeter() ";
    return -1;
  }

private:
  double area;
};

class Circle: public Shape
{
public:
  Circle(double a, int c) : Shape(a)
  {
    color  = c;
    radius = sqrt(a / M_PI);
  }
  
  virtual ~Circle()
  {
    std::cout << "I'm the "
	      << "Circle::destructor"
	      << std::endl;
  }
    
  double getPerimeter()
  {
    std::cout << "Circle::getPerimeter() ";
    return 2.*M_PI*sqrt(Shape::getArea() / M_PI);
  }

  int getColor()
  { 
    return color;
  }

private:
  int color;
  int radius;
};

class Square: public Shape
{
public:
  Square(double a, int c) : Shape(a)
  {
    color = c;
    side  = sqrt(a);
  }
    
  virtual ~Square()
  {
    std::cout << "I'm the "
	      << "Square::destructor"
	      << std::endl;
  }
    
  double getPerimeter()
  {
    std::cout << "Square::getPerimeter() ";
    return 4.*sqrt(Shape::getArea());
  }
    
  int getColor()
  {
    return color;
  }
    
private:
  int color;
  int side;
};

int main()
{
  Shape* sh = new Shape(2);

  std::cout << "Area: "
	    << sh->getArea() << " perimeter: "
	    << sh->getPerimeter() << std::endl;

  delete sh;
  sh = new Circle(4,0);

  std::cout << "Area: "
	    << sh->getArea() << " perimeter: "
	    << sh->getPerimeter() << std::endl;

  delete sh;
  sh = new Square(4,0);
    
  std::cout << "Area: "
	    << sh->getArea() << " perimeter: "
	    << sh->getPerimeter() << std::endl;

  return 0;
}
