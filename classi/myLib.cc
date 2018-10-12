#include "myLib.h"

double rand_range (double min, double max)
{
  return rand() / (double)RAND_MAX * (max-min) + min;
}

double rand_CLT (double xMin, double xMax, int tries)
{
  double x = 0.;
  
  for (int i = 0; i < tries; i++)
    x += rand_range(xMin, xMax);
  
  return x/tries;
}
