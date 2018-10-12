#include "istogramma.h"

istogramma::istogramma()
{
  nBin_p       = 0;
  min_p        = 0.;
  max_p        = 0.;
  step_p       = 0.;
  binContent_p = NULL;
  entries_p    = 0; 
  underflow_p  = 0; 
  overflow_p   = 0; 
  sum_p        = 0.; 
  sum2_p       = 0.; 
}

istogramma::istogramma (const int& nBin, const double& min, const double& max):
 nBin_p       (nBin),
 min_p        (min),
 max_p        (max),
 step_p       ((max_p - min_p) / nBin_p),
 binContent_p ( new int[nBin_p] ),
 entries_p    (0),
 overflow_p   (0),
 underflow_p  (0),
 sum_p        (0.),
 sum2_p       (0.)
{
  // Azzero gli elementi dell'istogramma
  for (int i = 0; i < nBin_p; ++i)
    binContent_p[i] = 0;
}

istogramma::istogramma (const istogramma& original)
{
  std::cout << "Ci sono arrivato00"<<std::endl;
  *(this) = original;
}

istogramma& istogramma::operator= (const istogramma& original)
{
  nBin_p       = original.nBin_p;
  min_p        = original.min_p;
  max_p        = original.max_p;
  step_p       = original.step_p;
  if (binContent_p != NULL){
	std::cout << "ciao " << binContent_p[0] << std::endl;
	delete[] binContent_p;
  }
  binContent_p = new int [nBin_p];

  for (int i = 0; i < nBin_p; i++)
    binContent_p[i] = original.binContent_p[i];
  
  entries_p   = original.entries_p;
  underflow_p = original.underflow_p; 
  overflow_p  = original.overflow_p; 
  sum_p       = original.sum_p; 
  sum2_p      = original.sum2_p; 

  return *this;
}


istogramma istogramma::operator+ (const istogramma& histo)
{
  istogramma SumHisto (histo);
  std::cout << "Ci sono arrivato000"<<std::endl;
  if (nBin_p != histo.nBin_p || min_p != histo.min_p || max_p != histo.max_p)
    {
      std::cout << "[istogramma::operator+]\tErrore: i due istogrammi hanno binning differente" << std::endl;
      return SumHisto;
  }
  
  for (int i = 0; i < nBin_p; i++)
    SumHisto.binContent_p[i] += binContent_p[i];
  
  SumHisto.entries_p   += entries_p;
  SumHisto.underflow_p += underflow_p;
  SumHisto.overflow_p  += overflow_p;
  SumHisto.sum_p       += sum_p;
  SumHisto.sum2_p      += sum2_p;
  
  return SumHisto;
}

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
  return ( sum2_p/entries_p - (sum_p/entries_p)*(sum_p/entries_p) );
}

void istogramma::Print () const
{
  // Normalizza l'istogrammma al valore maggiore
  int max = 0;
  for (int i = 0; i < nBin_p; ++i)
  {
    if (binContent_p[i] > max) max = binContent_p[i] ;
  }

  // Fattore di dilatazione per la rappresentazione dell'istogramma
  int scale = 50;
  
  // Disegna l'asse y
  std::cout << "        +---------------------------------------------------------------->" << std::endl;
  
  // Disegna il contenuto dei bin
  for (int i = 0; i < nBin_p; ++i)
    {
      std::cout << std::fixed << std::setw(8) << std::setprecision(2) << min_p + i * step_p <<"|";
      int freq = int(scale * binContent_p[i] / max);
      for (int j = 0; j < freq; ++j)
        std::cout << "#";
      
      std::cout << std::endl;
    }
  
  std::cout << "        |\n" << std::endl;
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
