/*
c++ es1.cpp -o es1 `root-config --cflags --glibs`
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
//#include "myLib.h"

#define FILE_NAME "myTree.root"
#define NENTRIES 10000

using namespace std;

int main (int argc, char** argv)
{
        gStyle->SetOptStat(1110);
        TApplication* myApp = new TApplication("myApp",NULL,NULL);
        TFile* myFileIn = new TFile("../Soluzioni_ntuple/data.root","READ");
        TNtuple* myNtuple = (TNtuple*) myFileIn->Get("myNtuple");

        TCanvas * c1 = new TCanvas("c1","Event selection");
        TH1D * h1 = new TH1D("h1","h1",4000,0,4000);
        myNtuple->Draw("E1 >> h1");
        c1->cd();
        h1->Draw();
        c1->Modified();
        c1->Update();

        TCanvas * c2 = new TCanvas("c2","Event selection");
        TH1D * h2 = new TH1D("h2","h2",4000,0,4000);
        myNtuple->Draw("E2 >> h2");
        c2->cd();
        h2->Draw();
        c2->Modified();
        c2->Update();

        TCanvas * c3 = new TCanvas("c3","Event selection");
        TH1D * h3 = new TH1D("h3","h3",100,500,520);
        myNtuple->Draw("E1 >> h3","E1<515 && E1>505");
        c3->cd();

        TF1 * f1 = new TF1("funzione", "pol1+gaus(2)",505,515);
        f1->SetParameter(2,92);
        f1->SetParameter(3,510);
        f1->SetParameter(4,2.8);
        h3->Fit(f1);
        h3->Draw();
        c3->Modified();
        c3->Update();

        TCanvas * c4 = new TCanvas("c4","Event selection");
        TH2D * h4 = new TH2D("h4","h4",4000,0,4000,4000,0,4000);
        myNtuple->Draw("E1:E2 >> h4");
        c4->cd();
        h4->Draw("gcolz");
        c4->Modified();
        c4->Update();

        TCanvas * c5 = new TCanvas("c5","Event selection");
        TH2D * h5 = new TH2D("h5","h5",4000,0,4000,4000,0,4000);
        myNtuple->Draw("E1:E2 >> h5","(E1+E2)<2625&& (E1+E2)>2605");
        c5->cd();
        h5->Draw("gcolz");
        c5->Modified();
        c5->Update();

        TCanvas * c6 = new TCanvas("c6","Event selection");
        TH1D * h6 = new TH1D("h6","h6",500,0,4000);
        myNtuple->Draw("E1 >> h6","(E1+E2)<2625&& (E1+E2)>2605");
        c6->cd();
        h6->Draw();
        c6->Modified();
        c6->Update();

        TFile * fileout = new TFile("graphs.root", "RECREATE");
        c1->Write();
        c2->Write();
        c3->Write();
        c4->Write();
        c5->Write();
        c6->Write();


        fileout->Close();

        myApp->Run();
        return 0;

}
