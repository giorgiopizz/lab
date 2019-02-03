/*
c++ -o esercizio03 esercizio03.cpp myLib.cc `root-config --glibs --cflags`
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
  float xMin = 0.;
  float xMax = 1.;
  float mu   = 0.25;
	
  TH1F h1 ("h1", "rand_FCI_Exp", 100, xMin, xMax);
	
  double random, sum=0., sumSq=0.;
  for (unsigned int i = 0; i < N; i++)
    {
      random = rand_FCI_Exp(mu);
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
  c1.Print("rand_FCI_Exp.png", "png");

  return 0;
}
