/*
c++ -o esercizio04 esercizio04.cpp myLib.cc `root-config --glibs --cflags`
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

#include "TCanvas.h"
#include "TStyle.h"
#include "TH1F.h"
 
#include "myLib.h"
 
int main()
{
  srand(time(NULL));
  int N = 10000;

  double mu = 0., sigma1 = 0.5, sigma2 = 2.;
  TH1F h1 ("histogram", "title", 100, -7, 7);

  for (int j = 0; j < N; j++)
    {
      double random, sum = 0.;
      
      random = rand_TAC_gaus(mu, sigma1);
      sum  += random;
	  
      random = rand_TAC_gaus(mu, sigma2);
      sum  += random;
      
      h1.Fill(sum);
    }
  
  gStyle->SetOptFit(1111);
  TCanvas c1;
  h1.Draw();
  h1.Fit("gaus");
  c1.Print("histogram.png","png");

  return 0;
}
