/*
c++ -o esempio01 esempio01.cpp
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

#define MAX_NUM 100000

double fgaus(double x)
{
  return exp(-0.5*x*x);
}

double rand_range(double min, double max)
{
  return min + (max - min) * rand() / RAND_MAX;
}

double rand_TAC(double xMin, double xMax, double yMin, double yMax)
{
  double x = 0., y = 0.;
  do {
    x = rand_range(xMin, xMax);
    y = rand_range(yMin, yMax);
  } while (y > fgaus(x));
  return x;
}

int main()
{
  srand(time(NULL));
  int N = MAX_NUM;
  double numero_casuale = 0.;
  
  for (int i = 0; i < N; ++i)
    {
      numero_casuale = rand_TAC(-1., 1., 0., 1.);
      std::cout << "Numero casuale: "
		<< numero_casuale << std::endl;
    }

  return 0;
}
