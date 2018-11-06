#include <iostream>
#include "analyzer.h"
#include <TApplication.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TH1D.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TMath.h>
int main(){
        analyzer Oggetto;
        Oggetto.setData("data1.txt", "counts");
        TApplication * app = new TApplication("myApp",NULL,NULL);
        TCanvas* cnv=new TCanvas("myCanv","myCanv",0,0,700,500);
        TH1D * histo=Oggetto.getHisto();
        cnv->cd();
        histo->Draw();

        cnv->Modified();
        cnv->Update();
        app->Run();

        return 0;
}
