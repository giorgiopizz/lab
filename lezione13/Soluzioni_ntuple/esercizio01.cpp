/*
c++ -o esercizio01 esercizio01.cpp `root-config --cflags --glibs`
*/

#include <iostream>

#include "TStyle.h"
#include "TApplication.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TF1.h"
#include "TCut.h"

#define FILEIN_NAME  "data.root"
#define FILEOUT_NAME "graphs.root"

using namespace std;

int main (int argc, char** argv)
{
  gStyle->SetOptStat(1110);
  TApplication* myApp = new TApplication("myApp",NULL,NULL);

  
  // ####################
  // # Reading the data #
  // ####################
  TFile* myFileIn = new TFile (FILEIN_NAME,"READ");
  TNtuple* myNtuple = (TNtuple*) myFileIn->Get("myNtuple");
  myNtuple->Scan();
 

  // #####################
  // # Plotting the data #
  // #####################
  TCanvas* c1 = new TCanvas ("c1","Marginal distribution of x");
  TH1D* h1 = new TH1D("h1","h1",4000,0,4000);
  myNtuple->Draw("E1 >> h1");
  c1->cd();
  h1->Draw();
  c1->Modified();
  c1->Update();


  TCanvas* c2 = new TCanvas ("c2","Marginal distribution of y");
  TH1D* h2 = new TH1D("h2","h2",4000,0,4000);
  myNtuple->Draw("E2 >> h2");
  c2->cd();
  h2->Draw();
  c2->Modified();
  c2->Update();


  TCanvas* c3 = new TCanvas ("c3","Zoom");
  TH1D* h1Zoom = new TH1D("h1Zoom","h1Zoom",40,490,530);
  myNtuple->Draw("E1 >> h1Zoom");
  TF1* myFunc = new TF1 ("myFunc","gaus(0) + pol1(3)",490,530);
  myFunc->SetParameter(0,500);
  myFunc->SetParameter(1,510);
  myFunc->SetParameter(2,10);
  myFunc->SetParameter(3,100);
  myFunc->SetParameter(4,0);
  c3->cd();
  h1Zoom->Draw();
  h1Zoom->Fit("myFunc");
  c3->Modified();
  c3->Update();


  TCanvas* c4 = new TCanvas ("c4", "Correlations");
  TH2D* h4 = new TH2D("h4","h4",4000,0,4000,4000,0,4000);
  myNtuple->Draw("E1:E2 >> h4");
  c4->cd();
  h4->Draw("gcolz");
  c4->Modified();
  c4->Update();


  TCanvas* c5 = new TCanvas ("c5","Event selection");
  TCut cut = "(E1 + E2) < 2625 &&  (E1 + E2) > 2605";
  TH1D* h5 = new TH1D("h5","h5",4000,0,4000);
  myNtuple->Draw("E1+E2 >> h5",cut);
  c5->cd();
  h5->Draw();
  c5->Modified();
  c5->Update();


  TCanvas* c6 = new TCanvas ("c6","Event selection and projection");
  TH1D* h6 = new TH1D("h6","h6",4000,0,4000);
  myNtuple->Draw("E1 >> h6",cut);
  c6->cd();
  h6->Draw();
  c6->Modified();
  c6->Update();


  // ################################
  // # Saving the plots into a file #
  // ################################
  TFile* myFileOut = new TFile(FILEOUT_NAME,"RECREATE");
  myFileOut->cd();
  c1->Write();
  c2->Write();
  c3->Write();
  c4->Write();
  c5->Write();
  c6->Write();
  myFileOut->Close();

  
  myApp->Run();
  return 0;
}
