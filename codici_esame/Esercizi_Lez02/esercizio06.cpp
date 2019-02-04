/*
c++ -o esercizio06 esercizio06.cpp

Esercizio: scrivere un programma che, dato un array di n interi
           casuali, lo ordini dal più grande al più piccolo
*/

#include <iostream>
#define DIM 10

void SortArray(double* myArray, int dim)
{
  bool flag = true;
  
  for (int i = 1; (i < dim && flag == true); i++)
    {
      flag = false;
      
      
      for (int j = 0; j < (dim - i); j++)
      	{
      	  if (myArray[j+1] > myArray[j])
      	    { 
      	      int temp     = myArray[j];
      	      myArray[j]   = myArray[j+1];
      	      myArray[j+1] = temp;

      	      flag = true;
      	    }
      	}
    }
}


int main (int argc, char** argv)
{
  int dim = DIM;
  double* data = new double[dim];
  
  std::cout << "Un-sorted values: " << std::endl;
  for (int i = 0; i < dim; i++)
    {
      data[i] = i;
      std::cout << "Val " << i << " = " << data[i] << std::endl;
    }

  SortArray(data, dim);
  std::cout << "\nSorted values: " << std::endl;
  for (int i = 0; i < dim; i++)
    {
      std::cout << "Val " << i << " = " << data[i] << std::endl;
    }
 
  delete[] data;
  
  return 0;
}
