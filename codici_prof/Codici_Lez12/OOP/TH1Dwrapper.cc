#include "TH1Dwrapper.h"

// Default constructor
TH1Dwrapper::TH1Dwrapper ()
{
  ROOThisto_p = new TH1D();
}

// Constructor
TH1Dwrapper::TH1Dwrapper (const int& nBin, const double& min, const double& max)
{
  ROOThisto_p = new TH1D("ROOThisto","ROOThisto",nBin,min,max);
}

// Copy constructor
TH1Dwrapper::TH1Dwrapper (const TH1Dwrapper& original)
{
  *(this) = original;
}

// Operator=
TH1Dwrapper& TH1Dwrapper::operator= (const TH1Dwrapper& original)
{
  if (ROOThisto_p != NULL) delete ROOThisto_p;
  *ROOThisto_p = *original.ROOThisto_p;

  return *(this);
}

// Destructor
TH1Dwrapper::~TH1Dwrapper ()
{
  delete ROOThisto_p;
}

int TH1Dwrapper::Fill (const double& value)
{
  return ROOThisto_p->Fill(value);
}

double TH1Dwrapper::GetMean () const
{
  return ROOThisto_p->GetMean();
}

double TH1Dwrapper::GetRMS () const
{
  return ROOThisto_p->GetRMS();
}

void TH1Dwrapper::Print () const
{
  TFile f("ROOThisto.root", "RECREATE");
  ROOThisto_p->Write();
  f.Close();
  
  std::cout << "[TH1Dwrapper::Print]\tHistogram written into the file ROOThisto.root" << std::endl;
}

int TH1Dwrapper::GetMax () const
{
  return ROOThisto_p->GetMaximum();
}

double TH1Dwrapper::GetIntegral () const
{
  return (ROOThisto_p->GetBinLowEdge(ROOThisto_p->GetNbinsX())+ROOThisto_p->GetBinWidth(ROOThisto_p->GetNbinsX()) - ROOThisto_p->GetBinLowEdge(1)) / ROOThisto_p->GetNbinsX() *
    ROOThisto_p->Integral();
}

double TH1Dwrapper::GetBinCenter (int i) const
{
  return ROOThisto_p->GetBinCenter(i);
}

int TH1Dwrapper::GetBinContent (int i) const
{
  return ROOThisto_p->GetBinContent(i);
}
