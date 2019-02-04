/*
c++ -o esercizio04 esercizio04.cpp myLib.cc `root-config --glibs --cflags`
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
  
  int Q;
	
  std::cout << "Quanti numeri casuali vuoi estrarre e mediare? ";
  std::cin >> Q;
	
  int N      = 10000;
  float xMin = 0.;
  float xMax = 1.;
  float mu   = 0.25;
	
  TH1F h1 ("h1", "rand_TCL", 100, xMin, xMax);
	
  double random, sum=0., sumSq=0.;
  for (int i = 0; i < N; i++)
    {
      random = 0.;
      for (int j = 0; j < Q; j++)
	random += rand_FCI_Exp(mu);
      random /= (double)Q;
      
      sum   += random;
      sumSq += random*random;
      h1.Fill(random);
    }
  double mean = sum/N;
  double var = sumSq/N - mean*mean;

  std::cout << "Media: " << mean << std::endl;	
  std::cout << "Varianza: " << var << std::endl;

  TCanvas c1;
  h1.Draw();
  c1.Print("rand_TCL.png", "png");
	
  return 0;
}
