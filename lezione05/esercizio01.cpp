/*
c++ -o esercizio01 esercizio01.cpp istogramma.cc myLib.cc
*/


#include <cmath>
#include <cstdlib>

#include "istogramma.h"
#include "myLib.h"


int main()
{
  srand (time(NULL));

  double a;
  double b;
  std::cout << "Inserisci gli estremi dell'intervallo [a,b) in cui generare i numeri: ";
  std::cin >> a >> b;

  int N;
  std::cout << "Inserisci quanti numeri casuali vuoi generare: ";
  std::cin >> N;

  // Istanzio l'istogramma
  double min;
  double max;
  std::cout << "Inserisci gli estremi dell'istogramma [min,max): ";
  std::cin >> min >> max;

  int nBin;
  std::cout << "Inserisci il numero di bin dell'istogramma: ";
  std::cin >> nBin;

  // Construtor
  istogramma histo(nBin, min, max);

  // Riempio l'istogramma
  int estrazioni = 10;
  double random;
  for (int i = 0; i < N; i++)
    {
      random = rand_CLT (a, b, estrazioni);
      histo.Fill(random);
    }

  // Stampo
  std::cout << "Mean = "       <<  std::setprecision(5) << histo.GetMean() << std::endl;
  std::cout << "RMS  = "       <<  std::setprecision(5) << histo.GetRMS()  << std::endl;
  std::cout << "Overflow  = "  << histo.GetOverflow() << std::endl;
  std::cout << "Underflow = "  << histo.GetUnderflow() << std::endl;
  std::cout << "Max counts = " << histo.GetMax() << std::endl;
  std::cout << "Integral ["    << min << ", " << max << "] = " << histo.GetIntegral() << std::endl;
  histo.Print();

  /*// Operator overloading
  istogramma histo2 (nBin, min, max);
  for (int i = 0; i < N; i++)
    {
      random = rand_CLT (min, max, estrazioni);
      histo2.Fill(random);
    }
  istogramma SumHisto;
  SumHisto = histo + histo2;
  SumHisto.Print();
  */
  return 0;
}
