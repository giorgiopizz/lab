/*
c++ -o esercizio04 esercizio04.cpp
*/

#include <iostream>
#define DIM 10


template<class T>
void SortArray(T* myArray, int dim)
{
  bool flag = true;
  
  for (int i = 1; (i < dim && flag == true); i++)
    {
      flag = false;
      
      
      for (int j = 0; j < (dim - i); j++)
      	{
      	  if (myArray[j+1] > myArray[j])
      	    { 
      	      T temp       = myArray[j];
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
  

  // ##################
  // # Test with char #
  // ##################
  char* dataC = new char[dim];
  
  std::cout << "Test with char" << std::endl;
  std::cout << "Un-sorted values: " << std::endl;
  for (int i = 0; i < dim; i++)
    {
      dataC[i] = char(i+65);
      std::cout << "Val " << i << " = " << dataC[i] << std::endl;
    }

  SortArray(dataC, dim);
  std::cout << "\nSorted values: " << std::endl;
  for (int i = 0; i < dim; i++)
    {
      std::cout << "Val " << i << " = " << dataC[i] << std::endl;
    }
 
  delete[] dataC;


  // #####################
  // # Test with integer #
  // #####################
  int* dataI = new int[dim];
  
  std::cout << "\n\nTest with integer" << std::endl;
  std::cout << "Un-sorted values: " << std::endl;
  for (int i = 0; i < dim; i++)
    {
      dataI[i] = i;
      std::cout << "Val " << i << " = " << dataI[i] << std::endl;
    }

  SortArray(dataI, dim);
  std::cout << "\nSorted values: " << std::endl;
  for (int i = 0; i < dim; i++)
    {
      std::cout << "Val " << i << " = " << dataI[i] << std::endl;
    }
 
  delete[] dataI;


  // ####################
  // # Test with double #
  // ####################
  double* dataD = new double[dim];
  
  std::cout << "\n\nTest with double" << std::endl;
  std::cout << "Un-sorted values: " << std::endl;
  for (int i = 0; i < dim; i++)
    {
      dataD[i] = i/static_cast<double>(dim);
      std::cout << "Val " << i << " = " << dataD[i] << std::endl;
    }

  SortArray(dataD, dim);
  std::cout << "\nSorted values: " << std::endl;
  for (int i = 0; i < dim; i++)
    {
      std::cout << "Val " << i << " = " << dataD[i] << std::endl;
    }
 
  delete[] dataD;

  return 0;
}
