#ifndef INTERFACCIAISTOGRAMMA_H
#define INTERFACCIAISTOGRAMMA_H

class interfacciaIstogramma
{

 public:

  // Operator=
  virtual interfacciaIstogramma& operator= (const interfacciaIstogramma& original) { return *(this); };

  // Destructor
  virtual ~interfacciaIstogramma () {};

  // Metodi
  virtual int    Fill          (const double& value) = 0;
  virtual void   Print         () const = 0;
  virtual double GetMean       () const = 0;
  virtual double GetRMS        () const = 0;
  virtual int    GetMax        () const = 0;
  virtual double GetIntegral   () const = 0;
  virtual double GetBinCenter  (int i) const = 0;
  virtual int    GetBinContent (int i) const = 0;
};

#endif
