#ifndef TH1DWRAPPER_H
#define TH1DWRAPPER_H

#include <iostream>

#include "TH1D.h"
#include "TFile.h"

#include "interfacciaIstogramma.h"

class TH1Dwrapper: public interfacciaIstogramma
{

 public:
  
  // Default constructor
  TH1Dwrapper ();

  // Constructor
  TH1Dwrapper (const int& nBin, const double& min, const double& max);

  // Copy constructor
  TH1Dwrapper (const TH1Dwrapper& original);

  // Operator=
  TH1Dwrapper& operator= (const TH1Dwrapper& original);

  // Destructor
  ~TH1Dwrapper ();

  // Metodi
  int    Fill          (const double& value);
  void   Print         () const;
  double GetMean       () const;
  double GetRMS        () const;
  int    GetMax        () const;
  double GetIntegral   () const;
  double GetBinCenter  (int i) const;
  int    GetBinContent (int i) const;

  // Attributi
 private:
  
  TH1D* ROOThisto_p;
};

#endif
