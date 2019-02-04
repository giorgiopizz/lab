/*
c++ -o esercizio02 esercizio02.cpp

Esercizio: dichiarate un puntatore e poi cercate di assegnargli direttamente
           un valore numerico. Cosa succede? Perchè?
*/

#include <iostream>

int main()
{
  int* pointer;
  
  pointer = 5;
  std::cout << "valore scritto in pointer " << pointer << '\n';  
  
  return 0;
}
