#include "istogramma.h"

// Constructor
istogramma::istogramma (const int& nBin, const double& min, const double& max):
  nBin_p       (nBin),
  min_p        (min),
  max_p        (max),
  step_p       ((max_p - min_p) / nBin_p),
  binContent_p ( new int[nBin_p] ),
  entries_p    (0),
  underflow_p  (0),
  overflow_p   (0),
  sum_p        (0.),
  sum2_p       (0.)
{
  // Azzero gli elementi dell'istogramma
  for (int i = 0; i < nBin_p; ++i)
    binContent_p[i] = 0;
}

// Destructor
istogramma::~istogramma ()
{
  delete[] binContent_p;
}

int istogramma::Fill (const double& value)
{
  if (value < min_p)
    {
      ++underflow_p;
      return -1;
    }
  
  if (value >= max_p)
    {
      ++overflow_p;
      return -1;
    }
  
  ++entries_p;

  int bin = int((value-min_p) / step_p);
  ++binContent_p[bin];
  
  sum_p  += value;
  sum2_p += value*value;
  
  return bin;
}

double istogramma::GetMean () const
{
  return (sum_p/entries_p);
}

double istogramma::GetRMS () const
{
  return sqrt( sum2_p/entries_p - (sum_p/entries_p)*(sum_p/entries_p) );
}

void istogramma::Print () const
{
  // Normalizza l'istogrammma al valore maggiore
  int max = 0;
  for (int i = 0; i < nBin_p; ++i)
    {
      if (binContent_p[i] > max) max = binContent_p[i];
    }

  // Fattore di dilatazione per la rappresentazione dell'istogramma
  int scale = 50;
  
  // Disegna l'asse y
  std::cout << "        +----------------------------------------------------------------> Entries" << std::endl;
  
  // Disegna il contenuto dei bin
  for (int i = 0; i < nBin_p; ++i)
    {
      std::cout << std::fixed << std::setw(8) << std::setprecision(2) << min_p + i * step_p <<"|";
      int freq = int(scale * binContent_p[i] / max);
      for (int j = 0; j < freq; ++j)
        std::cout << "#";
      
      std::cout << binContent_p[i] << std::endl;      
    }
  
  std::cout << "        | X axis\n" << std::endl;
}

int istogramma::GetMax () const
{
  int max = 0;
  for (int i = 0; i < nBin_p; i++)
    {
      if (binContent_p[i] > max) max = binContent_p[i];
    }
  return max;
}

double istogramma::GetIntegral () const
{
  return entries_p*step_p;
}

int istogramma::GetUnderflow () const
{
  return underflow_p;
}

int istogramma::GetOverflow () const
{
  return overflow_p;
}

double istogramma::GetBinCenter (int i) const
{
  return (0.5+i)*step_p + min_p;
}

int istogramma::GetBinContent (int i) const
{
  return binContent_p[i];
}
