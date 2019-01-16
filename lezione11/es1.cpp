#include <iostream>
#include <TCanvas.h>
#include <TApplication.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TFitResult.h>
#include <TMatrixDSym.h>
#include <cmath>
#include <fstream>
using namespace std;

int main(){
        TGraphErrors *g=new TGraphErrors("ese01Fit.txt");
        TApplication * app=new TApplication("c",NULL,NULL);
        TCanvas * cnv=new TCanvas("ci","cia",700,500);
        TF1 * f= new TF1("func","[0]*(1-TMath::Exp(-x/[1]))");
        f->SetParameter(0,10);
        f->SetParameter(1,0.0002);
        /*ifstream InFile("ese01Fit.txt");
        vector<double> x, y, xerr, yerr;
        double val, i=0;
        while(true){
                InFile >> val;
                i++;
                cout<<"ciao"<<endl;
                if(i==1) y.push_back(val);
                else if(i==2) x.push_back(val);
                else if(i==3) yerr.push_back(val);
                else if(i==4){
                        xerr.push_back(val);
                        i=0;
                }
                if(InFile.eof()==true)
                        break;
        }
        for(int i=0;i<x.size();i++){
                cout<<"x:"<<x.at(g.GetN())<<"y:"<<y.at(g.GetN())<<endl;
                g.SetPoint(g.GetN(),x.at(g.GetN()),y.at(g.GetN()));
                g.SetPointError(g.GetN()-1,xerr.at(g.GetN()-1),yerr.at(g.GetN()-1));
        }*/
        //gStyle->SetOptFit(1112)
        cnv->cd();

        TFitResultPtr r = g->Fit("func","S");
        TMatrixDSym cov = r->GetCovarianceMatrix();
        cout << "I parametri sono\nA: "<<f->GetParameter(0)<<" ± "<<sqrt(cov(0,0))<<endl;
        cout <<"B: "<<f->GetParameter(1)<<" ± "<<sqrt(cov(1,1))<<endl;
g->Draw();
        cnv->Modified();
        cnv->Update();
        app->Run();
}
