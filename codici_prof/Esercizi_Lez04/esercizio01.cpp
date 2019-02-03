/*
c++ -o esercizio01 esercizio01.cpp myLib.cc `root-config --glibs --cflags`
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

#include "TCanvas.h"
#include "TH1F.h"

#include "myLib.h"
 
int main()
{
  srand(time(NULL));
  int N = 10000;
  int Q;

  std::cout << "Digitare quanti numeri campionare da una pdf uniforme: ";
  std::cin >> Q;

  double a = 0., b = 10.;

  TH1F h1 ("histogram", "title", 100, a, b);
  double mean, random, mu = 0., sigmaMu = 0.;
  for (int i = 0; i < N; i++)
    {
      mean = 0;
      for (int j = 0; j < Q; j++)
	{
	  random = rand_range(a,b);
	  mean  += random;
	}
      mean /= Q;
      h1.Fill(mean);
      
      mu += mean;
      sigmaMu += mean*mean;
    }
	
  mu /= (double)N;
  sigmaMu = sqrt(sigmaMu/(double)N - mu*mu);

  std::cout << "Per il TCL, la deviazione std della media di " << Q << " numeri estratti da una pdf uniforme nel range ["
	    << a <<", " << b << "] è:\n" << sqrt(1./Q)*(b-a)/sqrt(12.) << std::endl;
  std::cout << "Il valore stimato per la dev std della media campionando la pdf della media è:\n" << sigmaMu << std::endl;

  TCanvas c1;
  h1.Draw();
  c1.Print("histogram.png","png");

  return 0;
}
