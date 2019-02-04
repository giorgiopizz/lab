/*
c++ -o esempio01 esempio01.cpp
*/

#include <iostream>

int main()
{
  int* pointer; // Dichiaro puntatore senza inizializzarlo
  std::cout << "Indirizzo a cui punta pointer " << pointer << '\n'; 

  pointer = NULL; // Setto pointer a puntare all'indirizzo nullo
  std::cout << "Indirizzo nullo a cui punta pointer " << pointer << '\n';
  
  int num = 5;
  pointer = &num;  // Setto pointer all'indirizzo di num
  std::cout << "Num valore " << num << '\n';
  std::cout << "Valore puntato da pointer " << *pointer << '\n';
  std::cout << "Indirizzo di num " << &num << '\n';
  std::cout << "Valore scritto in pointer " << pointer << '\n';  

  // Tutto quello che faccio con *pointer lo faccio "sulla variabile a cui punta pointer", quindi su num
  *pointer = 100;
  std::cout << "num is: " << num << '\n';
  
  (*pointer)++;
  std::cout << "num is: " << num << '\n';
  
  (*pointer)--;
  std::cout << "num is: " << num << '\n';
  
  return 0;
}
