#include <iostream>
#include <fstream>
#include <string>
#include <TApplication.h>
#include "TFitResult.h"
#include <TF1.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TStyle.h>
using namespace std;
bool ReadData(char * fileName, TH1D*  myHisto){
        string file = fileName;
        ifstream InFile(file.c_str());
        if(InFile.good()==0)
                return false;

        double x;
        while(true){
                InFile >> x;
                myHisto->Fill(x);
                if(InFile.eof()==true)
                        break;
        }
        return true;
}
int main(int argc, char ** argv){
        TApplication * app = new TApplication("myApp",NULL,NULL);
        TCanvas* cnv=new TCanvas("myCanv","myCanv",0,0,800,500);
        TH1D * histo= new TH1D("name","title",100,0,100);
        gStyle->SetOptFit(111);
        TF1 * Fun = new TF1("fun", "gaus",0,25);
        TF1 * mFun = new TF1("fun", "gaus",40,60);
        if(!ReadData(argv[1], histo)){
                cout << "Errore";
        }
        TFitResultPtr r1 = histo->Fit("gaus","S","",0,20);  // first fit
        TFitResultPtr r2 = histo->Fit("gaus","S","",40,60);
        TF1 * f1 = new TF1("fun", "gaus(0)+gaus(3)",0,100);
        f1->SetParameter(0,r1->Parameter(0));
        f1->SetParameter(1,r1->Parameter(1));
        f1->SetParameter(2,r1->Parameter(2));
        // parameters of second gaussian
        f1->SetParameter(3,r2->Parameter(0));
        f1->SetParameter(4,r2->Parameter(1));
        f1->SetParameter(5,r2->Parameter(2));
        cnv->cd();
        histo->Draw();
        histo->Fit("fun");
        cout<< f1->GetChisquare()/f1->GetNDF()<<endl;
        cnv->Modified();
        cnv->Update();
        cnv->Print("istogramma_fittato.png", "png");
        app->Run();
}
