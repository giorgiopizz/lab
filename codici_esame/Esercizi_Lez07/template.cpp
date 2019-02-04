/*
c++ -o template template.cpp
*/

#include <iostream>

#include "lib.h"

int main ()
{
  double d1 = 1.2;
  double d2 = 3.14;
  
  std::cout << "Somma di double: "<< d1 << " + " << d2 << " = ";
  std::cout << somma<double> (d1,d2) << std::endl;

  int i1 = 1;
  int i2 = 5;
  
  std::cout << "somma di int: "<< i1 << " + " << i2 << " = "; 
  std::cout << somma (i1,i2) << std::endl;

  /* Questo da' errore
     std::cout << "somma mista: "  << somma (i1,d2) << std::endl; */
  
  // Questo  invece si può fare
  std::cout << "somma mista: "<< i1 << " + " << d2 << " = ";
  std::cout << somma<double> (i1,d2) << std::endl;

  int   A = 2;
  float B = 2.22;  
  std::cout << raddoppia(A) << std::endl;
  std::cout << raddoppia(B) << std::endl;
  
  return 0;
}
