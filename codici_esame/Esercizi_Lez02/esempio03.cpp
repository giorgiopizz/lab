/*
  c++ -o esempio03 esempio03.cpp
*/

#include <iostream>

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

  // Alloca dinamicamente un vettore di dim posti
  int* vec = new int[dim];
  
  // Riempie il vettore
  for (int i = 0; i < dim; ++i)
    {
      vec[i] = i+1;
    }

  // Stampa i posti pari del vettore
  std::cout << "Uso l'array\n";
  for (int i = 0; i < dim; ++i)
    {
      if (i%2 == 0)
	{
	  std::cout << "Alla posizione " << i << " c'è " << vec[i] << std::endl;
	}
    }

  // Fa lo stesso con i puntatori
  std::cout << "Uso i puntatori\n";
  for (int* p = vec; (p-vec) < dim; ++p)
    {
      if ((p-vec)%2 == 0)
	{
	  std::cout << "Alla posizione " << p-vec << " c'è " << *p << std::endl;
	}
    }
  
  delete[] vec;
  
  return 0;
}
