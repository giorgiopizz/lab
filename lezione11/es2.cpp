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
        TGraphErrors *g=new TGraphErrors("ese02Extr.txt");
        TApplication * app=new TApplication("c",NULL,NULL);
        TCanvas * cnv=new TCanvas("ci","cia",700,500);
        TF1 * f= new TF1("func","pol2");

        cnv->cd();

        TFitResultPtr r = g->Fit("func","S");
        TMatrixDSym cov = r->GetCovarianceMatrix();
        cout << "I parametri sono\nA: "<<f->GetParameter(0)<<" ± "<<sqrt(cov(0,0))<<endl;
        cout <<"B: "<<f->GetParameter(1)<<" ± "<<sqrt(cov(1,1))<<endl;
        cout <<"C: "<<f->GetParameter(2)<<" ± "<<sqrt(cov(2,2))<<endl;

        g->Draw();
        double xp=32.;
        double err=sqrt(cov(0,0)+pow(xp,2)*cov(1,1)+pow(xp,4)*cov(2,2)+2.*(xp*cov(0,1)+pow(xp,2)*cov(0,2)+pow(xp,3)*cov(1,2)));
        cout << "La y è:"<<f->Eval(xp)<<" l'errore:"<<err<<endl;
        cnv->Modified();
        cnv->Update();
        app->Run();
}
