/*
c++ -o FitMomenta FitMomenta.cpp `root-config --cflags --glibs`
*/

#include <iostream>
#include <fstream>

#include "TApplication.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TF1.h"
#include "TF2.h"
#include "TFitResult.h"
#include "TMath.h"
using namespace std;

double distro1 (double* x, double* par)
{
  return 2*par[0]/sqrt(M_PI)*pow(x[0],1/2)*exp(-par[1]*x[0]);
}

double distro2 (double* x, double* par)
{
  return 2*par[0]/sqrt(M_PI)*pow(x[0],par[2])*exp(-par[1]*x[0]);
}

double distro3 (double *x,double *par){
  return par[0]*x[0]*exp(-par[1]*x[0]);
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
double likely_distro1(double * x, double * par){
        //par[0] è n, par[1]...par[n+1] sono le x

        double val=0;
        for(int i=1;i<par[0]+1;i++){
                val+=2*x[0]/sqrt(M_PI)*pow(par[i],1/2)*exp(-x[1]*par[i]);
        }
        return val;
}
double likely_distro3(double * x, double * par){
        //par[0] è n, par[1]...par[n+1] sono le x

        double val=0;
        for(int i=1;i<par[0]+1;i++){
                val+=x[0]*par[i]*exp(-x[1]*par[i]);
        }
        return val;
}
long double likely(TF1 * fun, TH1D * histo){
        long double val=1;
        for(int i=0;i<histo->GetNbinsX();i++){
                val*=fun->Eval(histo->GetBinCenter(i));
        }
        return val;
}
int main ()
{
  gStyle->SetOptFit(1112);

  TApplication* myApp = new TApplication("myApp", NULL, NULL);
  TCanvas* myCanv     = new TCanvas("myCanv","myCanv",0,0,700,500);
  TH1D* histo         = new TH1D("histo","histo",100,0,4);

  TF1* myFun1 = new TF1("myFun1",distro1,0.,4,2);
  myFun1->SetParameter(0,1.);
  myFun1->SetParameter(1,1.);

  TF1* myFun2 = new TF1("myFun2",distro2,0.,4,3);
  myFun2->SetParameter(0,1.);
  myFun2->SetParameter(1,1.);

  TF1* myFun3 = new TF1("myFun3",distro3,0.,4,2);
  myFun3->SetParameter(0,1.);
  myFun3->SetParameter(1,1.);

  ifstream DataFile("energy_distr.txt");
  double var;
  vector<double> dati;
  while(true)
    {
      DataFile >> var;
      dati.push_back(var);
      if(DataFile.eof() == true) break;
      histo->Fill(var);
    }
  DataFile.close();

  histo->Draw();
  TFitResultPtr r;

  r = histo->Fit("myFun1","S+");
  r->Print("V");
  double Chi2_1, NDF_1, pvalue_1;
  computeChi2(histo,myFun1,Chi2_1,NDF_1,pvalue_1);
  cout << "Chi-2 = " << Chi2_1 << "\tReduced Chi-2 = " << Chi2_1/NDF_1 << "\tp-value = " << pvalue_1 << "\n" << endl;

  myFun2->SetLineColor(kGreen);
  r = histo->Fit("myFun2","S+");
  r->Print("V");
  double Chi2_2, NDF_2, pvalue_2;
  computeChi2(histo,myFun2,Chi2_2,NDF_2,pvalue_2);
  cout << "Chi-2 = " << Chi2_2 << "\tReduced Chi-2 = " << Chi2_2/NDF_2 << "\tp-value = " << pvalue_2 << "\n" << endl;

  myFun3->SetLineColor(kBlue);
  r = histo->Fit("myFun3","S+");
  r->Print("V");
  double Chi2_3, NDF_3, pvalue_3;
  computeChi2(histo,myFun3,Chi2_3,NDF_3,pvalue_3);
  cout << "Chi-2 = " << Chi2_3 << "\tReduced Chi-2 = " << Chi2_3/NDF_3 << "\tp-value = " << pvalue_3 << "\n" << endl;

  cout << "The best function to describe the data is the one with Chi-2/NDF closer to 1" << endl;

  myCanv->Modified();
  myCanv->Update();
  /*TCanvas * cnv=new TCanvas("can","myCanv",0,0,700,500);
  cnv->cd();
  //loglike1 bounds:
  double x1_min=myFun1->GetParameter(0)-sqrt(myFun1->GetParameter(0));
  double x1_max=myFun1->GetParameter(0)+sqrt(myFun1->GetParameter(0));
  double x2_min=myFun1->GetParameter(1)-sqrt(myFun1->GetParameter(1));
  double x2_max=myFun1->GetParameter(1)+sqrt(myFun1->GetParameter(1));
  TF2* loglike1=new TF2("loglike1", likely_distro1,histo->GetNbinsX()+1,x1_min,x1_max,x2_min,x2_max);
  loglike1->SetParameter(0,histo->GetNbinsX());
  for(int i=1;i<histo->GetNbinsX()+1;i++){
          loglike1->SetParameter(i,histo->GetBinCenter(i-1));
  }
  loglike1->Draw("surf2z");
  cnv->Modified();
  cnv->Update();*/
  long double a=likely(myFun3,histo),b=likely(myFun1,histo);
  cout<<"Rapporti tra likely"<<a<<" "<<b<<" "<<a/b<<endl;

  myApp->Run();
  return 0;
}
