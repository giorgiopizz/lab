/*
c++ -o SimpleArray SimpleArray.cpp
*/

#include <iostream>

#include "SimpleArray.h"

#define N_ELEM 10

int main() 
{
  int elementi = N_ELEM;
  
  // Array semplice di int
  SimpleArray<int> arrayInt(elementi);
  std::cout << " Array riempito con int " << std::endl;

  // Riempimento
  for(int i = 0; i < elementi; i++)
    arrayInt.element(i) = 2 * i;
  
  // Rilettura
  for(int i = 0; i < elementi; i++)
    std::cout << " elemento " << i << " = " << arrayInt.element(i) << std::endl; 
  
  // Array semplice di float
  SimpleArray<float> arrayFloat(elementi);
  std::cout << "\n Array riempito con float " << std::endl;
  // Riempimento
  for(int i = 0; i < elementi; i++)
    arrayFloat.element(i) = 0.5 + arrayInt.element(i);
  
  // Rilettura
  for(int i = 0; i < elementi; i++)
    std::cout << " elemento " << i << " = " << arrayFloat[i] << std::endl;
  
  return 0; // Chiama automaticamente il distruttore
}
