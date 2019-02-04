/*
c++ -o esempio01 esempio01.cpp myLib.cc istogramma.cc
*/

#include "istogramma.h"
#include "myLib.h"

#define EXTR 10
#define N_FILL 10000


int main ()
{
  // "Default" histogram
  istogramma DefaultHisto; 
	
  const int Nbin  = 30;
  const float min = 0.;
  const float max = 10.;
  
  // Constructor with initialisation values
  istogramma MyHisto (Nbin, min, max);

  // Copy constructor
  istogramma HistoCopy (MyHisto);
  istogramma HistoCopy2 = MyHisto;

  int N          = N_FILL;
  int estrazioni = EXTR;
  float random;
  for (int i = 0; i < N; i++)
    {
      random = rand_CLT (min, max, estrazioni);
      MyHisto.Fill(random);
    }
  MyHisto.Print();
  
  std::cout << "Mean = " << MyHisto.GetMean() << std::endl;
  std::cout << "RMS  = " << MyHisto.GetRMS() << std::endl;

  istogramma MyHisto2 (Nbin, min, max); 
  for (int i = 0; i < N; i++)
    {
      random = rand_range (min, max);
      MyHisto2.Fill(random);
    }
  istogramma SumHisto;
  SumHisto = MyHisto + MyHisto2;
  
  SumHisto.Print();
			
  return 0;
}
