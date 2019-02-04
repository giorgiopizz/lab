/*
c++ -o esempio02 esempio02.cpp
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

#define MAX_NUM 100000

double rand_range(double min, double max)
{
  return min + (max - min) * rand() / RAND_MAX;
}

double rand_CLT(double xMin, double xMax, int tries)
{
  double x = 0.;
  
  for (int i = 0; i < tries; i++)
    x += rand_range(xMin, xMax);
  
  return x / tries;
}

int main()
{
  srand(time(NULL));
  int N = MAX_NUM;
  double numero_casuale = 0.;
  
  for (int i = 0; i < N; ++i)
    {
      numero_casuale = rand_CLT(-1, 1, 10);
      std::cout << "Numero casuale: "
		<< numero_casuale << std::endl;
    }
  
  return 0;
}
