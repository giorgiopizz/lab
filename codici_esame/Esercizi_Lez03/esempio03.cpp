/*
c++ -o esempio03 esempio03.cpp `root-config --glibs --cflags`
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "TCanvas.h"
#include "TH1F.h"

using namespace std;

double rand_range(double min, double max)
{
  return min + (max - min) * rand() / RAND_MAX;
}

double rand_CLT(double xMin, double xMax, int tries)
{
  double x = 0.;
  
  for (int i = 0; i < tries; i++)
    x += rand_range(xMin, xMax);
  
  return x / tries;
}

int main()
{
  srand(time(NULL));
  double min      = -1;
  double max      = 1;
  int nEstrazioni = 10;
  int N           = 10000;
  double numero_casuale = 0.;

  TH1F pdf ("name", "title", 100, min, max);

  for (int i = 0; i < N; i++)
    {
      numero_casuale = rand_CLT(min, max, nEstrazioni);
      std::cout << "Numero casuale: "
		<< numero_casuale << std::endl;
      pdf.Fill(numero_casuale);
    }

  TCanvas cnv;  
  pdf.Draw();
  pdf.Fit("gaus");
  cnv.Print("istogramma.png","png");
  
  return 0;
}
