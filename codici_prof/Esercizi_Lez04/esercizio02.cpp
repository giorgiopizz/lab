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
 
int main()
{
  srand(time(NULL));
  int N = 10000;
  int Q;
  double mu, sigma;
	
  std::cout << "Digitare quanti numeri campionare da una pdf gaussiana: ";
  std::cin >> Q;
  std::cout << "Impostare MU e SIGMA della pdf gaussiana: ";
  std::cin >> mu >> sigma;	
	
  TH1F h1 ("histogram", "title", 100, mu-5*sigma/sqrt((double)Q), mu+5*sigma/sqrt((double)Q));
  double mean, random, MeanMu=0., sigmaMu=0.;
  for (int i = 0; i < N; i++)
    {
      mean = 0;
      for (int j = 0; j < Q; j++)
	{
	  random = rand_TAC_gaus(mu, sigma);
	  mean += random;
	}
      mean /= Q;
      h1.Fill(mean);
      MeanMu  += mean;
      sigmaMu += mean*mean;
    }
  
  MeanMu /= (double)N;
  sigmaMu = sqrt(sigmaMu/(double)N - MeanMu*MeanMu);
  
  std::cout << "Per il TCL, la deviazione std della media di " << Q << " numeri estratti da una pdf gaussiana con sigma = "
	    << sigma << " è:\n" << sigma/sqrt((double)Q) << std::endl;
  std::cout << "Il valore stimato per la dev std della media campionando la pdf della media è:\n" << sigmaMu << std::endl;
	
  std::cout << "Il rapporto tra dev std della pdf gaussiana di partenza e dev std della media è:\n" << sigma/sigmaMu << std::endl;

  TCanvas c1;
  h1.Draw();
  c1.Print("histogram.png","png");

  return 0;
}
