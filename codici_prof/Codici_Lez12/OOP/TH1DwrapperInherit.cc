#include "TH1DwrapperInherit.h"

// Copy constructor
TH1DwrapperInherit::TH1DwrapperInherit (const TH1DwrapperInherit& original)
{
  *(this) = original;
}

// Operator=
TH1DwrapperInherit& TH1DwrapperInherit::operator= (const TH1DwrapperInherit& original)
{
  *(this) = original;

  return *this;
}

int TH1DwrapperInherit::Fill (const double& value)
{
  return this->TH1D::Fill(value);
}

double TH1DwrapperInherit::GetMean () const
{
  return this->TH1D::GetMean();
}

double TH1DwrapperInherit::GetRMS () const
{
  return this->TH1D::GetRMS();
}

void TH1DwrapperInherit::Print () const
{
  TFile f("ROOThisto.root", "RECREATE");
  this->Write();
  f.Close();
  
  std::cout << "[TH1DwrapperInherit::Print]\tHistogram written into the file ROOThisto.root" << std::endl;
}

int TH1DwrapperInherit::GetMax () const
{
  return this->GetMaximum();
}

double TH1DwrapperInherit::GetIntegral () const
{
  return (this->GetBinLowEdge(this->GetNbinsX())+this->GetBinWidth(this->GetNbinsX()) - this->GetBinLowEdge(1)) / this->GetNbinsX() * this->Integral();
}

double TH1DwrapperInherit::GetBinCenter (int i) const
{
  return this->TH1D::GetBinCenter(i);
}
