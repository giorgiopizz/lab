#ifndef TH1DWRAPPERINHERIT_H
#define TH1DWRAPPERINHERIT_H

#include <iostream>

#include "TH1D.h"
#include "TFile.h"

#include "interfacciaIstogramma.h"

// ######################################################################
// # Thi is necessary otherwise we would get signature mismatch between #
// # interfacciaIstogramma::GetBinContent and TH1D::GetBinContent       #
// ######################################################################
class preTH1DwrapperInherit: public interfacciaIstogramma
{
  
 public:
  int GetBinContent(int i) const { return helperFunction(i); };
  
 protected:
  virtual int helperFunction(int i) const = 0;
};

class TH1DwrapperInherit: public preTH1DwrapperInherit, public TH1D
{
  
 public:

  // Default constructor
  TH1DwrapperInherit () {};

  // Constructor: direct call to a specific base class constructor (the base class default constructor would be called automatically)
  TH1DwrapperInherit (const int& nBin, const double& min, const double& max) : TH1D("ROOThisto","ROOThisto",nBin,min,max) {};

  // Copy constructor
  TH1DwrapperInherit (const TH1DwrapperInherit& original);

  // Operator=
  TH1DwrapperInherit& operator= (const TH1DwrapperInherit& original);

  // Destructor
  ~TH1DwrapperInherit () {};

  // Metodi
  int    Fill         (const double& value);
  void   Print        () const;
  double GetMean      () const;
  double GetRMS       () const;
  int    GetMax       () const;
  double GetIntegral  () const;
  double GetBinCenter (int i) const;

 protected:
  int helperFunction(int i) const { return static_cast<int>(this->TH1D::GetBinContent(i)); };
};

#endif
