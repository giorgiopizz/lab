/*
c++ -o testEncapsulation testEncapsulation.cpp
*/

#include <iostream>
#include <cmath>

class ComplexNumber
{
public:
  ComplexNumber(double r, double i)
  {
    real = r;
    imag = i;
  }

  ~ComplexNumber()
  {
    std::cout << "I'm the "
	      << "ComplexNumber::destructor"
	      << std::endl;
  }

  double modulus()
  {
    return sqrt(real*real + imag*imag);
  }
  
private:
  double real;
  double imag;
};

int main ()
{
  ComplexNumber c(1,2);
  
  std::cout << "Modulo: " << c.modulus() << std::endl;
  
  return 0;
}
