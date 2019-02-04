#ifndef ISTOGRAMMA_H
#define ISTOGRAMMA_H

#include <iostream>
#include <iomanip>
#include <cmath>

#include "interfacciaIstogramma.h"

class istogramma: public interfacciaIstogramma
{
public:

  // Default constructor
  istogramma ();

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

  // Member functions
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

  // Data members
private:
  
  int    nBin_p;
  double min_p;
  double max_p;
  double step_p;       // Ampiezza del bin
  int*   binContent_p; // Array che contiene i conteggi nei bin
  int    underflow_p;  // Conteggi sotto min_p
  int    overflow_p;   // Conteggi sopra max_p
  int    entries_p;    // Conteggi totali tra min_p e max_p
  float  sum_p;        // Somma di tutti i valori inseriti nell'istogramma
  float  sum2_p;       // Somma dei quadrati
};

#endif
