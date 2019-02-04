/*
c++ -o esercizio01 esercizio01.cpp istogramma.cc myLib.cc
*/

#include "istogramma.h"
#include "myLib.h"

#define EXTR 10


int main()
{
  srand (1);
  
  double a;
  double b;
  std::cout << "Inserisci gli estremi dell'intervallo [a,b) in cui generare i numeri: ";
  std::cin >> a >> b;
  
  int N;
  std::cout << "Inserisci quanti numeri casuali vuoi generare: ";
  std::cin >> N;
  
  // Istanzia l'istogramma
  double min;
  double max;
  std::cout << "Inserisci gli estremi dell'istogramma [min,max): ";
  std::cin >> min >> max;

  int nBin;
  std::cout << "Inserisci il numero di bin dell'istogramma: ";
  std::cin >> nBin;
  
  // Construtor
  istogramma histo(nBin, min, max);
  
  // Riempie l'istogramma
  int estrazioni = EXTR;
  double random;
  for (int i = 0; i < N; i++)
    {
      random = rand_CLT (min, max, estrazioni);
      histo.Fill(random);
    }

  // Print
  std::cout << "Mean = "       << std::setprecision(5) << histo.GetMean() << std::endl;
  std::cout << "RMS  = "       << std::setprecision(5) << histo.GetRMS()  << std::endl;
  std::cout << "Overflow   = " << histo.GetOverflow()  << std::endl;
  std::cout << "Underflow  = " << histo.GetUnderflow() << std::endl;
  std::cout << "Max counts = " << histo.GetMax()       << std::endl;
  std::cout << "Integral ["    << min << ", " << max << "] = " << histo.GetIntegral() << std::endl;
  histo.Print();

  return 0;
}
