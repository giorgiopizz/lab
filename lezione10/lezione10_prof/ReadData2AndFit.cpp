/*
c++ -o ReadData2AndFit ReadData2AndFit.cpp `root-config --cflags --glibs`
*/

#include <iostream>
#include <fstream>

#include "TStyle.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TF1.h"
#include "TMath.h"

using namespace std;

double myGauss (double* x, double* par)
{
  return par[0] * exp(-0.5*((x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2])));
}

double myExp (double* x, double* par)
{
  return par[0] * exp(-x[0]/par[1]);
}

double sum (double* x, double* par)
{
  double val = myGauss(x, par) + myGauss(x, &par[3]) + myExp(x, &par[6]);
  return val;
}

double signal (double* x, double* par)
{
  double val = myGauss(x, par) + myGauss(x, &par[3]);
  return val;
}

bool readData(char* fileName, TH1D* myHisto)
{
  double val;
  fstream f;
  f.open(fileName,ios::in);
  if (f.good() == false) return false;
  while (true)
    {
      f >> val;
      if (f.eof() == true) break;
      myHisto->Fill(val);
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


int main(int argc, char** argv)
{
  int nBins   = 200;
  double xMin = 0;
  double xMax = 200;

  if (argc < 2)
    {
      cout << "Insufficient number of parameters: ./ReadData2AndFit fileName.txt" << endl;
      return 1;
    }

  gStyle->SetOptFit(1112);

  TApplication* myApp = new TApplication("myApp", NULL, NULL);
  TCanvas* myCanv = new TCanvas("myCanv","myCanv",0,0,700,500);
  TH1D* myHisto = new TH1D("myHisto","myHisto",nBins,xMin,xMax);

  TF1* myFun = new TF1("myFun",sum,xMin,xMax,8);
  myFun->SetParameter(0,570);
  myFun->SetParameter(1,130);
  myFun->SetParameter(2,3);

  myFun->SetParameter(3,260);
  myFun->SetParameter(4,170);
  myFun->SetParameter(5,3);

  myFun->SetParameter(6,1000);
  myFun->SetParameter(7,100);

  myFun->SetParName(0,"AmplG1");
  myFun->SetParName(1,"Mean1");
  myFun->SetParName(2,"Sigma1");

  myFun->SetParName(3,"AmplG2");
  myFun->SetParName(4,"Mean2");
  myFun->SetParName(5,"Sigma2");

  myFun->SetParName(6,"AmplE");
  myFun->SetParName(7,"Tau");

  if (readData(argv[1],myHisto) == false)
    {
      cout << "Error reading data file: " << argv[1] << endl;
      return 1;
    }

  myCanv->cd();
  myHisto->Draw("same");
  myHisto->Fit("myFun");

  myCanv->Modified();
  myCanv->Update();

  cout << "\nReduced Chi-2: " << myFun->GetChisquare()/myFun->GetNDF() << endl;
  cout << "p-value: " << myFun->GetProb() << endl;

  // Compute number of entries for the signal (i.e. two Gaussians)
  TF1* mySignal = new TF1("mySignal",signal,xMin,xMax,6);
  mySignal->SetParameter(0,myFun->GetParameter(0));
  mySignal->SetParameter(1,myFun->GetParameter(1));
  mySignal->SetParameter(2,myFun->GetParameter(2));
  mySignal->SetParameter(3,myFun->GetParameter(3));
  mySignal->SetParameter(4,myFun->GetParameter(4));
  mySignal->SetParameter(5,myFun->GetParameter(5));
  cout << "\nNumber of entries for the signal (i.e. two Gaussians): " << nBins / (xMax - xMin) * mySignal->Integral(xMin, xMax) << endl;

  // Compute number of entries for the background (i.e. Exponential)
  TF1* myBackground = new TF1("myBackground",myExp,xMin,xMax,2);
  myBackground->SetParameter(0,myFun->GetParameter(6));
  myBackground->SetParameter(1,myFun->GetParameter(7));
  cout << "Number of entries for the background (i.e. Exponential): " << nBins / (xMax - xMin) * myBackground->Integral(xMin, xMax) << endl;
  mySignal->Draw("same");
  myBackground->Draw("same");
  double Chi2, NDF, pvalue;
  computeChi2(myHisto,myFun,Chi2,NDF,pvalue);
  cout << "\nMy Chi-2: " << Chi2 << endl;
  cout << "My NDF: " << NDF << endl;
  cout << "My reduced Chi-2: " << Chi2/NDF << endl;
  cout << "My p-value: " << pvalue << endl;

  myApp->Run();
  return 0;
}
