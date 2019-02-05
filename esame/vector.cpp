/*
c++ -o vector vector.cpp
*/

#include <iostream>
#include <vector>

int main ()
{
  // Definisco un vector
  std::vector<double> MyVector;
  
  // Riempio il vector
  for (int i = 0; i < 10; i++)
    MyVector.push_back (i * 3.14);
  
  // Richiedo la dimensione del vector
  std::cout << "Numero elementi = ";
  std::cout << MyVector.size() << std::endl; 
  
  // Posso accedere agli elementi del vector con []
  for (int i = 0; i < MyVector.size(); i++)
    {
      std::cout << "Elemento " << i << ": ";
      std::cout << MyVector[i] << std::endl;  
    }
  
  return 0;
}
