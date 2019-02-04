/*
c++ -o esercizio03 esercizio03.cpp myLib.cc `root-config --glibs --cflags`
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
  TH1F h1 ("histogram", "title", 100, mu-5*sigma2, mu+5*sigma2);
	
  double random;
  for (int i = 0; i < N; i++)
    {
      random = rand_TAC_gaus(mu, sigma1);
      h1.Fill(random);
      
      random = rand_TAC_gaus(mu, sigma2);
      h1.Fill(random);
    }

  gStyle->SetOptFit(1111);
  TCanvas c1;
  h1.Draw();
  h1.Fit("gaus");
  c1.Print("histogram.png","png");

  return 0;
}
