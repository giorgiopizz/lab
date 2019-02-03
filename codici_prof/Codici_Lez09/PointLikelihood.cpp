/*
c++ -o PointLikelihood PointLikelihood.cpp  `root-config --cflags --glibs`
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <TApplication.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TF1.h>
#include <TLine.h>
#include <TStyle.h>
#include <TMath.h>

using namespace std;

double BisezioneRicorsiva(TF1* func, double xMin, double xMax, double precision)
{
  double x_m = 0.5 * (xMin + xMax);
  
  if ((xMax - xMin) < precision) return x_m;

  if (func->Eval(x_m) * func->Eval(xMin) < 0)
    return BisezioneRicorsiva(func, xMin, x_m, precision);
  
  return BisezioneRicorsiva(func, x_m, xMax, precision);
}

void intervallo(double muhat, int nsample, TF1* floglike, double* interval, double lmin, double lmax)
{
  floglike->SetParameters(muhat,nsample*1.);
  double lkmax=floglike->Eval(muhat);
  
  TF1 *func = new TF1("func", "floglike+0.5-[2]", lmin, lmax);
  func->SetParameter(2,lkmax);
  
  interval[0]=BisezioneRicorsiva(func, lmin, muhat,.0000001);
  interval[1]=BisezioneRicorsiva(func, muhat, lmax, .0000001);	
}


int main(int argc, char** argv)
{
  TApplication theApp("theApp", NULL, NULL);
  
  TCanvas* c1 = new TCanvas("c1","c1",1800,700);
  c1->Divide(2,1);
  gStyle->SetOptFit(1111);
  gStyle->SetLineWidth(3);
  gStyle->SetLabelSize(0.04,"XY");
  gStyle->SetTitleSize(0.04,"XY");
	
  double mu=5;		//media distrib. esponenziale
  int nsample;    //numero di campionamenti della pdf
  cout<<"Numero di campionamenti "<<endl;
  cin>>nsample;

  TF1 *fpdf = new TF1("fpdf", "1/[0]*exp(-x/[0])", 0, 1000);
  fpdf->SetParameter(0,mu);
	
  int nbin=100;
  double sigma_attesa=mu/sqrt(nsample*1.);
  double min=mu-5*sigma_attesa, max=mu+5*sigma_attesa;	
  if (min<=0) min=0.1;
	
  //determino la pdf dell'estimatore numericamente
  TH1F *hmedia=new TH1F("hmedia","pdf numerica per l'estimatore",nbin,min,max);
  double sum;
  int nexp=10000;     //numero di volte in cui ripeto l'esperimento	
  for (int j=0;j<nexp;j++) {
    sum=0;
    for (int i=0;i<nsample;i++) sum+=fpdf->GetRandom(0, 1000);
    hmedia->Fill(sum/(nsample*1.));	
  }
  hmedia->Scale(1/(nexp*1.));
  hmedia->SetLineColor(1);hmedia->SetFillColor(1);hmedia->SetFillStyle(3001);
			
  //pdf numerica dell'estimatore	
  c1->cd(1);  
  hmedia->Draw("histo E");
  TF1 *fgauss = new TF1("fgauss", "gausn", min, max); 
  hmedia->Fit(fgauss);
  fgauss->Draw("same");
  TF1 *fgamma = new TF1("fgamma", "[2]*TMath::GammaDist(x,[0],0,[1])", min, max);
  fgamma->SetParameters(mu*sqrt(nsample),1/sqrt(nsample),.1);
  hmedia->Fit(fgamma,"LR+");
  fgamma->SetLineColor(4);
  fgamma->Draw("same");
  //~ cout<<"Mu vero "<<mu<<endl;
  cout<<"\nEstimatore media aritmetica (e' anche il MLE), per "<<nsample<<" campionamenti\n";
  cout<<"                  Media attesa per l'estimatore =  "<<mu<<endl;
  cout<<"    Deviazione standard attesa per l'estimatore =  "<<sigma_attesa<<endl;
  cout<<"    Intervallo a 1 sigma "<<mu-mu/sqrt(nsample)<<"<mu<"<< mu+mu/sqrt(nsample)<<endl<<endl;

  cout<<"\n Toy MC con "<<nexp<<" esperimenti, usato per costruire la pdf dell'estimatore \n";
  cout<<"      Media estimatore da Toy MC =  "<<hmedia->GetMean()<<endl;   
  cout<<"   Deviazione standard da Toy MC =  "<<hmedia->GetRMS()<<endl;
  int binmin=(mu-sigma_attesa-min)/(max-min)*nbin+1;
  int binmax=(mu+sigma_attesa-min)/(max-min)*nbin+1;
  cout<<binmin<<endl;
  cout<<"Copertura intervallo da Var[x_medio] = "<<hmedia->Integral(binmin,binmax)<<"%"<<endl<<endl;
       
 
    
  //loglikelihood calcolata per l'ultimo set di dati campionati
  c1->cd(2);
  double muhat;
  double lmin=1, lmax=20;
  lmin=min, lmax=max;
  TF1 *floglike = new TF1("floglike", "-[1]*TMath::Log(x)-[1]/x*[0]", lmin, lmax);
  double interval[2];
    
  //calcolo copertura dell'intervallo ottenuto da lnL-0.5
  double copertura=0;
  int ncicli=10000;
  for (int j=0;j<ncicli;j++) {
    sum=0;
    for (int i=0;i<nsample;i++) sum+=fpdf->GetRandom(0,1000);
    muhat=sum/nsample;
    intervallo(muhat, nsample, floglike, interval, lmin, lmax);
    if (interval[0]<mu && interval[1]>mu) copertura++;
  }
  TLine lmedia(muhat,floglike->Eval(lmin),muhat,floglike->Eval(muhat));
  lmedia.SetLineColor(3);
  TLine llmezzi(lmin,floglike->Eval(muhat)-0.5,lmax,floglike->Eval(muhat)-0.5);
  llmezzi.SetLineColor(3);
    
  floglike->Draw("");
  lmedia.Draw("same");
  llmezzi.Draw("same");
  c1->Update();

  cout<<"Copertura intervallo ln(L)-0.5 = "<<copertura/(ncicli*1.)<<"%"<<endl;
  cout<<"\nStima da un singolo data-set\n";
  cout<<"      Valore di mu da MLE =  "<<muhat<<endl;   
  cout<<"      Intervallo di confidenza da Likelihood+1/2 "<<interval[0]<<"<mu<"<<interval[1]<<endl;

  theApp.Run();
  return 0;
}
