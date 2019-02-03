/*
c++ -o esercizio03 esercizio03.cpp complesso.cc
*/

#include <iostream>
#include <string>
#include <vector>

#include "complesso.h"

int main() 
{
  complesso Z0 (0,0);
  std::vector <complesso> ListaDiComplessi;
  double re = 0., im = 0.;

  do {
    std::cout << "Inserisci parte reale e immaginaria di un numero complesso\n";
    std::cout << "\t(0 0 per uscire):\n";
    std::cin >> re >> im;
    complesso z(re,im);
    ListaDiComplessi.push_back(z);
  } while (re != 0 && im != 0);
	
  complesso somma (0,0);
  for (int i = 0; i < ListaDiComplessi.size(); i++)
    {
      somma = somma + ListaDiComplessi[i];
    }
  std::cout << "La somma dei numeri complessi inseriti e`: ";
  somma.Print();

  return 0;
}
