#ifndef COMPLESSO_H
#define COMPLESSO_H

#include <iostream>
#include <cmath>

class complesso
{ 
public:
  // Constructors
  complesso  ();
  complesso  (const double& re, const double& im);
  complesso  (const complesso& original);
  ~complesso (); // Destructor
  
  // Operator overloads
  complesso& operator= (const complesso& original);
  complesso& operator= (const double& original);
  complesso  operator+ (const complesso& original);
  complesso  operator- (const complesso& original);
  complesso  operator* (const complesso& original);
  complesso  operator/ (const complesso& original);
  complesso  operator^ (const int& potenza);

  // Member functions
  double Re()    const;
  double Im()    const;
  double Mod()   const;
  double Theta() const;
  void   Print() const;
  
  // Data members
private:
  double re_p;
  double im_p;
};

#endif
