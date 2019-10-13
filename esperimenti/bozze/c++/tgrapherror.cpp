//c++ tgrapherror.cpp -o tgrapherror `root-config --cflags --glibs`
//eseguire passando il nome del file
#include <iostream>
#include <TApplication.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TMath.h>
#include <TFitResult.h>
#include <TMatrixDSym.h>
using namespace std;

double funzione(double * x, double * par){
        return par[0]*TMath::Exp(par[1]*x[0]);
}
int main(int argc,char ** argv){
        TApplication * app = new TApplication("App", NULL, NULL);
        TCanvas * cnv = new TCanvas("canvas", "canvas", 750,600);
        //il tgraph è costruito a partire dal file
        TGraphErrors* graf = new TGraphErrors(argv[1]);
        TF1 * f= new TF1("func",funzione, -10,10,2);
        f->SetParameter(0,3);
        f->SetParameter(1,-3);
        cnv->cd();
        graf->Draw("AP");
        TFitResultPtr r=graf->Fit(f,"s");
        cout << "\nReduced Chi-2: " << f->GetChisquare()/f->GetNDF() << endl;
        cout << "p-value: " << f->GetProb() << endl;
        TMatrixDSym cov=r->GetCovarianceMatrix();
        cov.Print();
        cnv->Modified();
        cnv->Update();
        app->Run();
}
