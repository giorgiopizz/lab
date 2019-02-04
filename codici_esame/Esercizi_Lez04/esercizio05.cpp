/*
c++ -o esercizio05 esercizio05.cpp myLib.cc
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
 
#include "myLib.h"
 
int main()
{
  srand(time(NULL));
  int N    = 100000;
  int nHit = 0;
  double xMin = -5, xMax;
  double yMin = 0., yMax = 1/sqrt(2*M_PI);

  std::cout << "Inserisci l'estremo superiore che si vuole utilizzare per calcolare l'integrale della pdf Normale:";
  std::cin >> xMax;

  for (int i = 0; i < N; i++)
    {   
      if (HitMiss_Gaus(xMin, xMax, yMin, yMax) == true)
	nHit++;
    }

  double Area     = (xMax-xMin) * (yMax-yMin);
  double Integral = nHit * Area / (double)N;
  double p        = nHit / (double)N;
  double Var      = Area * Area / (double)N * p * (1-p);
  double StdDev   = sqrt(Var);

  std::cout << "Integrale della pdf Normale nel range [" << xMin << ", " << xMax << "]= " << Integral
	    << " +/- " << StdDev << std::endl;
  return 0;
}
