#include "complesso.h"

// Constructors
complesso::complesso ()
{
  re_p = 0.;
  im_p = 0.;
}

complesso::complesso (const complesso& original)
{
  re_p = original.re_p;
  im_p = original.im_p;
}

complesso::complesso (const double& re, const double& im)
{
  re_p = re;
  im_p = im;
}

complesso::~complesso ()
{
  // Il distruttore non deve fare nessuna operazione di delete
}

// Operator overloads
complesso& complesso::operator= (const complesso& original)
{
  re_p = original.re_p;
  im_p = original.im_p;
  
  return *this;
}

complesso complesso::operator+ (const complesso& original)
{
  double re = re_p + original.re_p;
  double im = im_p + original.im_p;
  
  complesso rit(re, im);
  return rit;
}

complesso complesso::operator- (const complesso& original)
{
  double re = re_p - original.re_p;
  double im = im_p - original.im_p;
  
  complesso rit(re, im);
  return rit;
}

complesso complesso::operator* (const complesso& original)
{
  double re = re_p * original.re_p - im_p * original.im_p;
  double im = im_p * original.re_p + re_p * original.im_p;
  
  complesso rit(re, im);
  return rit;
}

complesso complesso::operator/ (const complesso& original)
{
  double coeff = pow(original.re_p, 2) + pow(original.im_p, 2);
  double re = (re_p * original.re_p + im_p * original.im_p) / coeff;
  double im = (original.re_p * im_p - re_p * original.im_p) / coeff;
  
  complesso rit(re, im);
  return rit;
}

complesso& complesso::operator= (const double& original)
{
  re_p = original;
  im_p = 0.;

  return *this;
}

complesso complesso::operator^ (const int& potenza)
{
  complesso c(re_p, im_p);
  for (int i = 1; i < potenza; i++)  {
    c = c*c;
  }  
  return c;
}

// Member functions
double complesso::Re() const
{
  return re_p;
}

double complesso::Im() const
{
  return im_p;
}

double complesso::Mod() const
{
  return sqrt(pow(re_p, 2) + pow(im_p, 2));
}

double complesso::Theta() const
{
  if (re_p > 0)
    {
      return atan(im_p/re_p);
    }
  if (re_p < 0)
    {
      return atan(im_p/re_p) + M_PI;
    }

  if (im_p > 0) return M_PI / 2;
  return -M_PI / 2;
}

void complesso::Print() const
{
  if (this->Im() >= 0) std::cout << this->Re() << " + " << this->Im() << "i" << std::endl;
  else std::cout << this->Re() << " - " << -this->Im() << "i" << std::endl;
}
