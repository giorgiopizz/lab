/*
c++ -o HitMiss HitMiss.cpp myLib.cc
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

#include "myLib.h"
 
int main()
{
  srand(time(NULL));
  int N       = 100000;
  int nHit    = 0;
  double xMin = 0., xMax = 2*M_PI;
  double yMin = 0., yMax = 2.;
  
  for (int i = 0; i < N; i++)
    {
      if (HitMiss(xMin, xMax, yMin, yMax)==true) 
	nHit++;
    }
  
  double Area     = (xMax-xMin) * (yMax-yMin);
  double Integral = nHit * Area / (double)N;
  double p        = nHit / (double)N;
  double Var      = Area * Area / (double)N * p * (1.-p);
  double StdDev   = sqrt(Var);
  
  std::cout << "Integral = " << Integral 
	    << " +- "<< StdDev << std::endl;
  return 0;
}
