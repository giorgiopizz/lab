/*
c++ -o memDinamica memDinamica.cpp
*/

#include <iostream>

int* creaVettore(int dim)
{
  int* array = new int[dim];
  return array;
}

int main()
{
  int dim = 0;
  
  std::cout << "Inserisci la dimensione del vettore: ";
  std::cin >> dim;

  if (dim < 0)
  {
    std::cout << "Numero negativo" << std::endl;
    return -1;
  }

  // Alloca dinamicamente un vettore di dim celle                                                             
  int* vec = creaVettore(dim);

  // Riempi il vettore                                                                                        
  for (int i = 0; i < dim; ++i)
    {
      vec[i] = i+1;
    }

  // Stampa gli elementi del vettore                                                                          
  for (int i = 0; i < dim; ++i)
    {
      std::cout << "Contenuto della cella " << i << " : " << vec[i] << std::endl;
    }

  delete[] vec;

  return 0;
}
