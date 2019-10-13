/*
c++ -o esercizio02 esercizio02.cpp myLib.cc `root-config --cflags --glibs`
*/

#include <iostream>
#include <fstream>

#include "TStyle.h"
#include "TApplication.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"

//#include "myLib.h"

#define FILE_NAME "hiddenSignal.root"
#define NENTRIES 100000

using namespace std;

int main (int argc, char** argv)
{
  gStyle->SetOptStat(1110);
  TApplication* myApp = new TApplication("myApp",NULL,NULL);
  double x, y;


  // ########################
  // # Producing the signal #
  // ########################
  // std::ofstream outFile ("myNtuple.txt",std::ios::out);
  // TFile* myFileOut = new TFile(FILE_NAME,"RECREATE");
  // TTree* myTreeOut = new TTree("myTree","A simple Tree with simple variables");
  // myTreeOut->Branch("x",&x,"x/D");
  // myTreeOut->Branch("y",&y,"y/D");
  // for (unsigned int j = 0; j < NENTRIES; j++)
  //   {
  //     x = rand_range(-5,5);
  //     y = rand_range(-5,5);
  //     outFile << x << "\t" << y << std::endl;
  //     myTreeOut->Fill();
  //   }
  // for (unsigned int i = 0; i < NENTRIES/10; i++)
  //   {
  //     double r = fabs(rand_TAC_gaus(3,0.5));
  //     double theta = rand_range(0,2*M_PI);
  //     x = r*cos(theta);
  //     y = r*sin(theta);
  //     outFile << x << "\t" << y << std::endl;
  //     myTreeOut->Fill();
  //   }
  // outFile.close();
  // myTreeOut->Write();
  // myFileOut->Close();


  // ##############################################
  // # Defining the tree and ceating the branches #
  // ##############################################
  TFile* myFileIn = new TFile(FILE_NAME,"READ");
  TTree* myTreeIn = (TTree*) myFileIn->Get("myTree");

  myTreeIn->SetBranchAddress("x",&x);
  myTreeIn->SetBranchAddress("y",&y);


  TCanvas* c1 = new TCanvas ("c1","c1");
  TCanvas* c2 = new TCanvas ("c2","c2");
  TCanvas* c3 = new TCanvas ("c3","c3");
  TH2D* h1 = new TH2D("h1","Scatter plot",100,-5,5,100,-5,5);
  TH2D* h2 = new TH2D("h2","Signal",100,-5,5,100,-5,5);
  TH1D* h3 = new TH1D("h3","Signal",100,0,5);


  // ##################################################
  // # Reading all entries and filling the histograms #
  // ##################################################
  unsigned int nEntries = myTreeIn->GetEntries();
  for (unsigned int i = 0; i < nEntries; i++)
    {
      myTreeIn->GetEntry(i);
      h1->Fill(x,y);

      // ###################
      // # Event selection #
      // ###################
      if ((x*x + y*y > 2) && (x*x + y*y < 16))
	{
	  h2->Fill(x,y);
	  h3->Fill(sqrt(x*x + y*y),1./sqrt(x*x + y*y));
	  // Events must be weighted by the inverse of the
	  // radius to preserve the probability density
	}
    }

  c1->cd();
  h1->Draw("gcolz");
  c1->Modified();
  c1->Update();

  c2->cd();
  h2->Draw("gcolz");
  c2->Modified();
  c2->Update();

  c3->cd();
  h3->Draw();
  c3->Modified();
  c3->Update();


  myApp->Run();
  return 0;
}
