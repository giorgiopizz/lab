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
 
int main ()
{
  srand(time(NULL));
  
  int N   = 10000;
  float a = 0.;
  float b = 10.;	
  
  TH1F h1 ("h1", "rand_range", 100, a, b);
  
  double random, sum=0., sumSq=0.;
  for (unsigned int i = 0; i < N; i++)
    {
      random = rand_range(a,b);
      sum   += random;
      sumSq += random*random;
      h1.Fill(random);
    }
  double mean = sum/N;
  double var  = sumSq/N - mean*mean;
  
  std::cout << "Media: " << mean << std::endl;
  std::cout << "(a+b)/2: " << 0.5*(a+b) << std::endl;
  
  std::cout << "Varianza: " << var << std::endl;
  std::cout << "(b-a)^2/12: " << (1./12.)*(b-a)*(b-a) << std::endl;
  
  TCanvas c1;	
  h1.Draw();
  c1.Print("rand_range.png", "png");
  
  return 0;
}
