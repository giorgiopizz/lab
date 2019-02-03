/*
c++ -o esercizio01 esercizio01.cpp
*/

#include <iostream>

#include "SimpleArray.h"

int main() 
{
  SimpleArray<int> MyArray;
  char answer;
  int num;
  int index;
	
  do {
    std::cout << "Dimmi cosa vuoi fare (digita la lettera corrispondente):\n";
    std::cout << "\tPush(i)     Pop(t)     Exit(e)\n";
    std::cin >> answer;
    if (answer == 'i')
      {
	std::cout << "Inserisci un numero: ";
	std::cin >> num;
	MyArray.push(num);
      }
    else if (answer == 't')
      {
	std::cout << "Inserisci l'indice dell'elemento che vuoi estrarre dall'array\n";
	std::cout << "(il numero di elementi dell'array e` " << MyArray.size() << "): ";
	std::cin >> index;
	num = MyArray.pop(index);
	std::cout << "Hai estratto il numero " << num << "\n";
      }
  } while (answer != 'e');

  int Nelem = MyArray.size();
  std::cout << "N elementi MyArray = " << Nelem << std::endl;
  for (int i = 0; i < Nelem; i++)
    std::cout << "\telemento " << i << " = " << MyArray[i] << std::endl;

  return 0;
}
