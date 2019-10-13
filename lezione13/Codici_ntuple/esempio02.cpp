/*
c++ -o esempio02 esempio02.cpp myLib.cc `root-config --cflags --glibs`
*/

#include <iostream>

#include "TStyle.h"
#include "TApplication.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"

#include "myLib.h"

#define FILE_NAME "myTree.root"
#define NENTRIES 10000

using namespace std;

int main (int argc, char** argv)
{
  gStyle->SetOptStat(1110);
  TApplication* myApp = new TApplication("myApp",NULL,NULL);
  TFile* myFileOut = new TFile(FILE_NAME,"RECREATE");


  // ##############################################
  // # Defining the tree and ceating the branches #
  // ##############################################
  TTree* myTreeOut = new TTree("myTree","A simple Tree with simple variables");

  double px, py, random;
  int ev;

  myTreeOut->Branch("px",     &px,     "px/D");
  myTreeOut->Branch("py",     &py,     "py/D");
  myTreeOut->Branch("random", &random, "random/D");
  myTreeOut->Branch("ev",     &ev,     "ev/I");


  // ###############################
  // # Filling and saving the tree #
  // ###############################
  for (unsigned int i = 0; i < NENTRIES; i++)
    {
      px = rand_TAC_gaus(0,1);
      py = rand_TAC_gaus(0,1);
      random = rand_range(2,3);
      ev = i;
      myTreeOut->Fill();
    }
  myTreeOut->Scan();
  myTreeOut->Write();
  myFileOut->Close();


  // ##############################################
  // # Defining the tree and creating the branches #
  // ##############################################
  TFile* myFileIn = new TFile(FILE_NAME,"READ");
  TTree* myTreeIn = (TTree*) myFileIn->Get("myTree");

  myTreeIn->SetBranchAddress("px",     &px);
  myTreeIn->SetBranchAddress("py",     &py);
  myTreeIn->SetBranchAddress("random", &random);
  myTreeIn->SetBranchAddress("ev",     &ev);


  TCanvas* c1 = new TCanvas ("c1","c1");
  TCanvas* c2 = new TCanvas ("c2","c2");
  TH1D* h1 = new TH1D("h1","Uniform distribution",100,0,10);
  TH2D* h2 = new TH2D("hpxpy","py vs px",30,-3,3,30,-3,3);


  // ##################################################
  // # Reading all entries and filling the histograms #
  // ##################################################
  unsigned int nEntries = myTreeIn->GetEntries();
  for (unsigned int i = 0; i < nEntries; i++)
    {
      myTreeIn->GetEntry(i);


      // ###################
      // # Event selection #
      // ###################
      if ((random > 0.5) && (ev > 10))
	{
	  h1->Fill(random);
	  h2->Fill(px,py);
	}
    }

  c1->cd();
  h1->Draw();
  c1->Modified();
  c1->Update();

  c2->cd();
  h2->Draw("gcolz");
  c2->Modified();
  c2->Update();


  myApp->Run();
  return 0;
}
