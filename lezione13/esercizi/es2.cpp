/*
c++ es2.cpp -o es2 `root-config --cflags --glibs`
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

using namespace std;

int main (int argc, char** argv)
{
        gStyle->SetOptStat(1110);
        TApplication* myApp = new TApplication("myApp",NULL,NULL);
        TFile* myFileIn = new TFile("../Soluzioni_ntuple/hiddenSignal.root","READ");
        TTree* myTree = (TTree*) myFileIn->Get("myTree");

        TCanvas * c1 = new TCanvas("c1","Event selection");
        TH2D * h1 = new TH2D("h1","h1",1000,-6,6,1000,-6,6);
        myTree->Draw("x:y >> h1");
        c1->cd();
        h1->Draw();
        c1->Modified();
        c1->Update();

        TCanvas * c2 = new TCanvas("c2","Event selection");
        TH2D * h2 = new TH2D("h2","h2",1000,-6,6,1000,-6,6);
        myTree->Draw("x:y >> h2", "x*x+y*y>2.2*2.2 && x*x+y*y<3.6*3.6");
        c2->cd();
        h2->Draw();
        c2->Modified();
        c2->Update();

        myApp->Run();

}
