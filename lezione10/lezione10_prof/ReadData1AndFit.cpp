/*
c++ -o ReadData1AndFit ReadData1AndFit.cpp `root-config --glibs --cflags`
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

#include "TApplication.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TMatrixDSym.h"

using namespace std;

double myGauss (double* x, double* par)
{
  return par[0] * exp(-0.5*((x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2])));
}

double myParabola (double* x, double* par)
{
  return par[0] + par[1]*x[0] + par[2]*x[0]*x[0];
}

double sum (double* x, double* par)
{
  double val = myGauss(x, par) + myParabola(x, &par[3]);
  return val;
}

bool readData(char* fileName, vector<double>& dataList, double& xMin, double& xMax)
{
  double num;
  bool first = true;
  std::fstream in;
  in.open(fileName,std::ios::in);
  if (in.good() == false) return false;
  
  while (true)
    {
      in >> num;
      if (in.eof() == true) break;
      dataList.push_back(num);
      if (first == true)
	{
	  xMin   = num;
	  xMax   = num;
	  first = false;
	}
      else
	{
	  if (num < xMin) xMin = num;
	  if (num > xMax) xMax = num;
	}
    }
  
  return true;
}

void computeChi2(TH1D* myHisto, TF1* myFun, double& Chi2, double& NDF, double& pvalue)
{
  double result = 0;
  NDF = 0.;
  for (unsigned int i = 1; i <= myHisto->GetNbinsX(); i++)
    {
      if (myHisto->GetBinContent(i) != 0.)
	{
	  result += pow((myHisto->GetBinContent(i) - myFun->Eval(myHisto->GetBinCenter(i))),2.) / myHisto->GetBinContent(i);
	  NDF++;
	}
    }

  Chi2   = result;
  NDF   -= myFun->GetNpar();
  pvalue = TMath::Prob(Chi2,NDF);
}

int main (int argc, char** argv)
{
  gStyle->SetOptFit(1112);

  if (argc < 2)
    {
      cout << "Insufficient number of parameters: ./ReadData1AndFit fileName.txt" << endl;
      return 1;
    }

  
  // #####################
  // # Reading data file #
  // #####################
  double xMin, xMax;
  vector<double> dataList;
  if (readData(argv[1],dataList,xMin,xMax) == false)
    {
      cout << "Error reading data file: " << argv[1] << endl;
      return 1;
    }

  cout << "The file " << argv[1] << " contains " << dataList.size() << " data" << endl;
  cout << "Minimum: " << xMin << endl;
  cout << "Maximum: " << xMax << endl;
  
  
  TApplication* myApp = new TApplication("myApp", NULL, NULL);

  
  // ###########################
  // # Preparing the histogram #
  // ###########################
  int nBins = 100;
  
  TH1D* h1 = new TH1D("h1","Data distribution", nBins, xMin, xMax);  
  h1->SetFillColor(kAzure+6);
  h1->GetXaxis()->SetTitle("Variable x");
  h1->GetYaxis()->SetTitle("Counts");
  for (unsigned int i = 0; i < dataList.size(); i++) h1->Fill(dataList[i]);

  TCanvas* myCanv1 = new TCanvas("myCanv1","myCanv1",0,0,700,500);

  
  // ##############################
  // # Preparing the fit function #
  // ##############################
  TF1* myFun = new TF1("myFun", sum, xMin, xMax, 6);
  myFun->SetParameter(0, 10000);        // Gaussian maximum value
  myFun->SetParameter(1, 5.);           // Gaussian mean value
  myFun->SetParameter(2, h1->GetRMS()); // Gaussian standard deviation
  myFun->SetParameter(3, 1000.);        // Intercept of the parabola
  
  myFun->SetParName(0,"Ampl");
  myFun->SetParName(1,"Mean");
  myFun->SetParName(2,"Sigma");

  myFun->SetParName(3,"Zero");
  myFun->SetParName(4,"First");
  myFun->SetParName(5,"Second");


  // ###########
  // # Fitting #
  // ###########
  myCanv1->cd();
  h1->Draw();
  h1->Fit("myFun");

  
  // #############
  // # Computing #
  // #############
  cout << "\nReduced Chi-2: " << myFun->GetChisquare()/myFun->GetNDF() << endl;
  cout << "p-value: " << myFun->GetProb() << endl;
  for (unsigned int i = 0; i < myFun->GetNpar(); i++)
    cout << "Parameter-" << i << " = " << myFun->GetParameter(i) << " +/- " << myFun->GetParError(i) << endl;

  // Compute number of entries for the signal (i.e. Gaussian)
  TF1* mySignal = new TF1("mySignal", myGauss, xMin, xMax, 3);
  mySignal->SetLineColor(kBlack);
  mySignal->SetParameter(0,myFun->GetParameter(0));
  mySignal->SetParameter(1,myFun->GetParameter(1));
  mySignal->SetParameter(2,myFun->GetParameter(2));
  cout << "\nNumber of entries for the signal (i.e. Gaussian): ";
  cout << nBins / (xMax - xMin) * mySignal->Integral(xMin, xMax);
  cout << endl;
  
  // Compute number of entries for the background (i.e. Parabola)
  TF1* myBackground = new TF1("myBackground", myParabola, xMin, xMax, 3);
  myBackground->SetLineColor(kBlue);
  myBackground->SetParameter(0,myFun->GetParameter(3));
  myBackground->SetParameter(1,myFun->GetParameter(4));
  myBackground->SetParameter(2,myFun->GetParameter(5));
  cout << "Number of entries for the background (i.e. Parabola): ";
  cout << nBins / (xMax - xMin) * myBackground->Integral(xMin, xMax);
  cout << endl;

  double Chi2, NDF, pvalue;
  computeChi2(h1,myFun,Chi2,NDF,pvalue);
  cout << "\nMy Chi-2: " << Chi2 << endl;
  cout << "My NDF: " << NDF << endl;
  cout << "My reduced Chi-2: " << Chi2/NDF << endl;
  cout << "My p-value: " << pvalue << endl;

  myBackground->Draw("same");

  myCanv1->Modified();
  myCanv1->Update();


  // ###########################
  // # Print covariance matrix #
  // ###########################
  TFitResultPtr r = h1->Fit("myFun", "S");
  r->Print("V");

  TMatrixDSym cov = r->GetCovarianceMatrix();
  // TMatrixDSym cov = r->GetCorrelationMatrix();
  cout << "\nRetrieved covariance matrix" << endl;
  for (int i = 0; i < myFun->GetNpar(); i++)
    {
      for (int j = 0; j < myFun->GetNpar(); j++)
	{
	  double sigma_ij = cov(i,j);
	  cout << setw(15) << sigma_ij;
	}
      cout << endl;
    }

  TH1D* h2 = new TH1D("h2","Data distribution", nBins, xMin, xMax);
  h2->GetXaxis()->SetTitle("Variable x");
  h2->GetYaxis()->SetTitle("Counts");
  for (unsigned int i = 0; i < dataList.size(); i++)
    {
      h2->SetBinContent(i+1,h1->GetBinContent(i+1));
      h2->SetBinError(i+1,sqrt(h1->GetBinContent(i+1)));
    }

  TCanvas* myCanv2 = new TCanvas("myCanv2","myCanv2",0,0,700,500);
  
  
  // ###########
  // # Fitting #
  // ###########
  myCanv2->cd();
  h2->Draw();
  h2->Fit("myFun");
  
  myCanv2->Modified();
  myCanv2->Update();

  
  myApp->Run(); 
  return 0;
}
