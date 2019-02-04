#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
 
#include "myLib.h"

double rand_range(double min, double max)
{
  return min + (max - min) * rand() / RAND_MAX;
}

double rand_TAC(double xMin, double xMax, double yMin, double yMax)
{
  double x=0., y=0.;
  do
    {
      x = rand_range(xMin, xMax);
      y = rand_range(yMin, yMax);
    } while (y > fCauchy(x));
  return x;
}

double fCauchy(double x)
{
  return 1./(M_PI*(1.+x*x));
}

double rand_FCI_Exp(double mu)
{
  double x, y;
  y = rand_range(0., 1.);
  x = -mu * log(1 - y);
  return x;
}

long int genLinCong (long int Xn)
{
  return static_cast<long int>(A*Xn + C) % static_cast<long int>(M);
}
