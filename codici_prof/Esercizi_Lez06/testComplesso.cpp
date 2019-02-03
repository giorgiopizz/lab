/*
c++ -o testComplesso complesso.cc testComplesso.cpp
*/

#include <iostream>
#include <cstdlib>

#include "complesso.h"

int main()
{
  complesso z1(3.,2.5);
  complesso z2 = z1;
  std::cout << "z1 = ";
  z1.Print();
  std::cout << "z2 = ";
  z2.Print();
  
  complesso zSum = z1+z2;
  std::cout << "Somma = ";
  zSum.Print();
  
  complesso zDiff = z1-z2;
  std::cout << "Differenza = ";
  zDiff.Print();
  
  complesso zProd = z1*z2;
  std::cout << "Prodotto = ";
  zProd.Print();
  
  complesso zDiv = z1/z2;
  std::cout << "Divisione = ";
  zDiv.Print();
  
  complesso zPow = z1^2;
  std::cout << "z1^2 = ";
  zPow.Print();
  
  std::cout << "Modulo z1 = " << z1.Mod() << std::endl;
  std::cout << "Fase z1 = " << z1.Theta() << std::endl;

  return 0;
}
