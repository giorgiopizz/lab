/*
c++ -o esercizio06 esercizio06.cpp myLib.cc
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
 
#include "myLib.h"
 
int main()
{
  srand(time(NULL));
  int N = 10000;
  double xMin = -5, xMax;
  double sum = 0., sumSq = 0., y;

  std::cout << "Inserisci l'estremo superiore che si vuole utilizzare per calcolare l'integrale della pdf Normale:";
  std::cin >> xMax;
  
  for (int i = 0; i < N; i++)
    {
      y = Crude_MC_gaus(xMin, xMax);
      sum   += y;
      sumSq += y*y;
    }

  double mean = sum / N;
  double var  = sumSq / N - mean*mean;
  var *= (double)N / (N-1); // Correzione per evitare il bias dello stimatore

  double ErrMean     = sqrt(var/N);
  double Integral    = (xMax-xMin)*mean;
  double ErrIntegral = (xMax-xMin)*ErrMean;

  std::cout << "Integrale della pdf Normale nel range [" << xMin << ", " << xMax << "]= " << Integral 
	    << " +/- " << ErrIntegral << std::endl;
  return 0;
}
