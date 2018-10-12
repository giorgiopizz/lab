#ifndef istogramma_h
#define istogramma_h

#include <iostream>
#include <iomanip>

class istogramma
{
  
 public:

  // Default constructor
  istogramma();

  // Constructor
  istogramma (const int& nBin, const double& min, const double& max);

  // Copy constructor
  istogramma (const istogramma& original);

  // Operator=
  istogramma& operator= (const istogramma& original);

  // Operator+
  istogramma operator+ (const istogramma& histo);
  
  // Destructor
  ~istogramma ();

  // Metodi
  int    Fill          (const double& value);
  void   Print         () const;
  double GetMean       () const;
  double GetRMS        () const;
  int    GetMax        () const;
  double GetIntegral   () const;
  int    GetUnderflow  () const;
  int    GetOverflow   () const;
  double GetBinCenter  (int i) const;
  int    GetBinContent (int i) const;

  // Attributi
 private:
  
  int    nBin_p;
  double min_p;
  double max_p;
  double step_p;
  int*   binContent_p;
  int    entries_p;
  int    overflow_p;
  int    underflow_p;
  double sum_p;
  double sum2_p;
};

#endif
