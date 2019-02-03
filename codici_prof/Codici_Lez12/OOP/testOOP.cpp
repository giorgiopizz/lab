/*
c++ -o testOOP testOOP.cpp istogramma.cc TH1Dwrapper.cc TH1DwrapperInherit.cc myLib.cc `root-config --cflags --glibs`
*/


#include <iostream>
#include <cstring>

#include "interfacciaIstogramma.h"
#include "istogramma.h"
#include "TH1Dwrapper.h"
#include "TH1DwrapperInherit.h"
#include "myLib.h"

#define EXTR 10


// ########################################################################################
// # Funzione che fa uso dell'interfaccia polimorfica alle classi di istogrammi           #
// # E` completamente agnostica del tipo di istanza concreta scelta per l'istogrammazione #
// ########################################################################################
void manipHisto (interfacciaIstogramma* histo, const double min, const double max, const int N)
{
  // Riempio l'istogramma
  int estrazioni = EXTR;
  double random;
  for (int i = 0; i < N; i++)
    {
      random = rand_CLT (min, max, estrazioni);
      histo->Fill(random);
    }
  
  // Stampo
  std::cout << "Mean = "       <<  std::setprecision(5) << histo->GetMean() << std::endl;
  std::cout << "RMS  = "       <<  std::setprecision(5) << histo->GetRMS()  << std::endl;
  std::cout << "Max counts = " << histo->GetMax() << std::endl;
  std::cout << "Integral ["    << min << ", " << max << "] = " << histo->GetIntegral() << std::endl;
  histo->Print();
}


int main(int argc, char** argv)
{
  srand (1);

  if (argc != 2)
    {
      std::cout << "Errore! Il numero di parametri non e` corretto: ./testOOP [1=istogramma.h o 2=TH1D.h]" << std::endl;
      return 1;
    }
  
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

  
  interfacciaIstogramma* histo;
  // ############################################
  // # Particolarizzo l'interfaccia polimorfica #
  // ############################################
  if     (strcmp(argv[1],"1") == 0) histo = new istogramma(nBin, min, max);
  else if(strcmp(argv[1],"2") == 0) histo = new TH1Dwrapper(nBin, min, max);
  else if(strcmp(argv[1],"3") == 0) histo = new TH1DwrapperInherit(nBin, min, max);
  else
    {
      std::cout << "Errore! Parametro non corretto: " << argv[1] << std::endl;
      return 1;
    }
  // ############################################
  manipHisto(histo,min,max,N);


  delete histo;
  return 0;
}
