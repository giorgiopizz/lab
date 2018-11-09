// c++ GaussPoisson.cpp `root-config --cflags --glibs`  -o GP

#include <iostream>
#include <ctime>
#include <TMath.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TApplication.h>

using namespace std;


int main(int argc, char **argv) {

	double muA=10;
	double muB=100;

	if (argc>2) {
		muA=atof(argv[1]);
		muB=atof(argv[2]);
		}

	cout<<"Confronto Poisson e Gauss per mu pari a: "<<muA<<" e "<<muB<<endl;


	double MaxA=muA+3*sqrt(muA);
	double MaxB=muB+3*sqrt(muB);
	double minA=muA-3*sqrt(muA);
	double minB=muB-3*sqrt(muB);

	TApplication Grafica("", NULL, NULL);


	//definisco due funzioni Poissoniane
	TF1* poA= new TF1("poA", "TMath::PoissonI(x,[0])", 0, MaxA);
	poA->SetParameter(0,muA);
	poA->SetLineColor(kBlue);
	poA->SetLineWidth(3);
    TF1* poB = new TF1("poB", "TMath::PoissonI(x,[0])", 0, MaxB);
    poB->SetParameter(0,muB);
    poB->SetLineColor(kBlue);
    poB->SetLineWidth(3);

	//definisco due funzioni Gaussiane
	TF1* gaussA = new TF1("gaussA", "TMath::Gaus(x,[0],[1],1)", minA, MaxA);
	gaussA->SetParameters(muA,sqrt(muA));
	gaussA->SetFillColor(kRed-9);
	gaussA->SetFillStyle(1002);
    TF1* gaussB = new TF1("gaussB", "TMath::Gaus(x,[0],[1],1)", minB, MaxB);
    gaussB->SetParameters(muB,sqrt(muB));
	gaussB->SetFillColor(kRed-9);
	gaussB->SetFillStyle(1002);


   TCanvas *c1 = new TCanvas("c1","c1",1600,700);
   gStyle->SetOptStat(0);
   gStyle->SetLineWidth(3);
   gStyle->SetLabelSize(0.05,"XY");
   gStyle->SetTitleSize(0.05,"XY");




   c1->cd();
   gaussA->Draw();
   gaussA->GetXaxis()->SetTitle("x");
   poA->Draw("same");
   TString hA="#mu=";
   hA+=muA;
   TLegend *legendA = new TLegend(0.1,0.7,0.48,0.9);
   legendA->SetHeader(hA.Data(),"C");
   legendA->AddEntry("poA","Poisson(#mu)","l");
   legendA->AddEntry("gaussA","Gauss(#mu, #sigma=#sqrt{#mu})","l");
   legendA->Draw();



   c1->cd(2);
   gaussB->Draw();
   gaussB->GetXaxis()->SetTitle("x");
   poB->Draw("same");

   TString hB="#mu=";
   hB+=muB;
   TLegend *legendB = new TLegend(0.1,0.7,0.48,0.9);
   legendB->SetHeader(hB.Data(),"C");
   legendB->AddEntry("poB","Poisson(#mu)","l");
   legendB->AddEntry("gaussB","Gauss(#mu, #sigma=#sqrt{#mu})","l");
   legendB->Draw();


  Grafica.Run("");

  return 0;


	}
