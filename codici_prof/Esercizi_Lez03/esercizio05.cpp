/*
c++ -o esercizio05 esercizio05.cpp myLib.cc `root-config --cflags --glibs`
*/

// #############
// # ROOT CODE #
// #############
#include "TCanvas.h"
#include "TH1D.h"
#include "TF1.h"

#include <iostream>
#include <cmath>

#include "myLib.h"

#define N  1000000
#define Q    10000
#define NBINS 1000
#define SEED     1


int main()
{
  // #############
  // # ROOT CODE #
  // #############
  TCanvas c0("c0","c0",0,0,700,500);
  TH1D    h0("h0","h0",NBINS,0,1);
  TCanvas c1("c1","c1",0,0,700,500);
  TH1D    h1("h1","h1",NBINS/5,-3,3);


  long int valNew;
  long int valOld = SEED;
  
  for (unsigned int i = 0; i < N; i++)
    {
      valNew = genLinCong(valOld);
      // std::cout << "Generated number [" << i << "] = " << valNew << std::endl;
      valOld = valNew;

      h0.Fill(static_cast<double>(valNew) / M);      
    }

  
  double mean  = 0.5;             // Mean value of the uniform distribution in the unterval [0,1)
  double sigma = 1/sqrt(12. * Q); // Standard deviation of the uniform distribution in the unterval [0,1) divided by sqrt(Q),
                                  // where Q is the number of averaged uniform random variables
  double avg;
  for (unsigned int i = 0; i < N/100; i++)
    {
      avg = 0;
      
      for (unsigned int j = 0; j < Q; j++)
	{
	  valNew = genLinCong(valOld);
	  avg   += static_cast<double>(valNew) / M;
	  valOld = valNew;
	}
      avg /= Q;

      h1.Fill((avg - mean) / sigma);
    }


  // #############
  // # ROOT CODE #
  // #############
  c0.cd();
  h0.GetYaxis()->SetRangeUser(0.0,N/NBINS + N/NBINS);
  h0.Draw();
  c0.Print("esercizio05_h0.png","png");

  c1.cd();
  h1.Draw();
  h1.Fit("gaus");
  c1.Print("esercizio05_h1.png","png");

  return 0;
}
