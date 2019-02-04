/*
c++ -o ErroreMedia ErroreMedia.cpp myLib.cc `root-config --glibs --cflags`
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
  int N    = 10000;
  int Q    = 10000;
  double a = 0., b = 10.;

  TH1F h1 ("histogram", "title", 100, a, b);
  double mean, random;
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
    }

  gStyle->SetOptFit(1111);
  TCanvas c1;
  h1.Draw();
  h1.Fit("gaus");
  c1.Print("histogram.png","png");

  return 0;
}
