#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
 
#include "myLib.h"

double rand_range (double min, double max)
{
  return min + (max - min) * rand() / RAND_MAX;
}

double fsin (double x)
{
  return 1. + sin(x);
}

bool HitMiss (double xMin, double xMax, double yMin, double yMax)
{
  double x = 0., y = 0.;
  x = rand_range(xMin, xMax);
  y = rand_range(yMin, yMax);
  if (y < fsin(x)) return true;
  else return false;
}
 
double fgaus (double x, double mu, double sigma)
{
  return exp(-0.5*pow((x-mu),2)/(sigma*sigma))/sqrt(2*M_PI*sigma*sigma);
}
 
double rand_TAC_gaus (double mu, double sigma)
{
  double xMin = mu-5*sigma;
  double xMax = mu+5*sigma;
  double yMin = 0.;
  double yMax = 1./sqrt(2*M_PI*sigma*sigma);
  double x = 0., y = 0.;
  
  do {
    x = rand_range(xMin, xMax);
    y = rand_range(yMin, yMax);
  } while (y > fgaus(x, mu, sigma));
  
  return x;
}
 
bool HitMiss_Gaus (double xMin, double xMax, double yMin, double yMax)
{
  double x = 0., y = 0.;
  x = rand_range(xMin, xMax);
  y = rand_range(yMin, yMax);
  
  if (y < fgaus(x, 0., 1.)) return true;  
  else return false;
}
 
double Crude_MC_gaus (double xMin, double xMax)
{
  double x = 0., y = 0.;
  x = rand_range(xMin, xMax);
  y = fgaus(x, 0., 1.);
  return y;
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

double rand_CLT (double xMin, double xMax, int tries)
{
  double x = 0.;
  
  for (int i = 0; i < tries; i++)
    x += rand_range(xMin, xMax);
  
  return x/tries;
}

long int genLinCong (long int Xn)
{
  return static_cast<long int>(A*Xn + C) % static_cast<long int>(M);
}
