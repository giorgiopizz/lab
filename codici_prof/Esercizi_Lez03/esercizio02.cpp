/*
c++ -o esercizio02 esercizio02.cpp myLib.cc `root-config --glibs --cflags`
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
 
#include "TCanvas.h"
#include "TH1F.h"
 
#include "myLib.h"
 
int main ()
{
  srand(time(NULL));
  
  int N      = 10000;
  float xMin = -5.;
  float xMax = 5.;
  float yMin = 0.;
  float yMax = 1./3.14;
	
  TH1F h1 ("h1", "rand_TAC", 100, xMin, xMax);

  double random, sum=0., sumSq=0.;
  for (unsigned int i = 0; i < N; i++)
    {
      random = rand_TAC(xMin, xMax, yMin, yMax);
      sum   += random;
      sumSq += random*random;
      h1.Fill(random);
    }
  double mean = sum/N;
  double var  = sumSq/N - mean*mean;
  
  std::cout << "Media: " << mean << std::endl;	
  std::cout << "Varianza: " << var << std::endl;
  
  TCanvas c1;	
  h1.Draw();
  c1.Print("rand_TAC.png", "png");
  
  return 0;
}
