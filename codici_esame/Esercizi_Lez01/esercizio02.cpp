/*
c++ -o esercizio02 esercizio02.cpp

Esercizio: scrivere un programma che scrive a terminale
           la radice quadrata di 2, il cubo di 2 il seno di pigreco/4
*/

#include <iostream>
#include <cmath>

int main ()
{
  double due = 2;
  double radice_due = sqrt(due);
  std::cout << "La radice quadrata di due è : " << radice_due << std::endl;
  
  double due_al_cubo = pow(2., 3);
  std::cout << "Il cubo di 2 è : " << due_al_cubo << std::endl;
  
  double sin_45 = sin(M_PI/4.);
  std::cout << "Il seno di pi/4 è:  " << sin_45  << std::endl;
  
  return 0;
}
