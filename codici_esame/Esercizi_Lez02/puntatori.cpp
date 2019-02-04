/*
c++ -o puntatori puntatori.cpp
*/

#include <iostream>

int main()
{
  int var = 137;
  std::cout << "var vale: " << var 
            << " ed il suo indirizzo e`: " << &var << std::endl;
  
  int* ptr;
  std::cout << "Indirizzo a cui punta ptr e`: " << ptr << std::endl;
  
  ptr = &var;
  std::cout << "Ora ptr punta a var: " << ptr
            << " ed il valore a cui punta e`: " << *ptr << std::endl;
  
  *ptr = 100;
  std::cout << "var ora vale: " << var << std::endl;
  
  int pippo = *ptr;
  std::cout << "La variabile pippo vale: " << pippo << std::endl;
  
  (*ptr)++;
  std::cout << "var ora vale: " << var << " e pippo vale: " << pippo << std::endl;
  
  int vec[] = {2, 20};
  std::cout << "Vec[0] = " << *vec << "; Vec[1] = " << *(vec+1) << std::endl;
  
  return 0;
}
