/*
c++ -o esercizio01 esercizio01.cpp
 
Esercizio: scrivete un programma che, letti due numeri
           interi da terminale, restituisca il loro rapporto
*/

#include <iostream>

int main ()
{
  int numero1, numero2;
  
  std::cout << "Inserisci il primo numero: " << std::endl;
  std::cin >> numero1;
  
  std::cout << "Inserisci il secondo numero: " << std::endl;
  std::cin >> numero2;
  
  float rapporto = (float)numero1 / numero2;
  
  std::cout << "Il rapporto tra i due numeri è: "
	    << rapporto << std::endl;
  
  return 0;
}
