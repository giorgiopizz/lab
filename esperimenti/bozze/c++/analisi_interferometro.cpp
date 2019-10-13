//c++ analisi_interferometro.cpp -o analisi_interferometro `root-config --cflags --glibs`
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

double relazione_due(double * x, double * par){
        //theta in funzione di N con d parametro libero(par[0])
        //par[1] è lambda e par[2] è delta_r
        //(probabilmente anche delta_r è libero)
        return TMath::ACos((par[1]*x[0])/(par[0]*2)-(par[1]*par[2])\
        /(M_PI*4*par[0]));
}
int main(int argc,char ** argv){
        TApplication * app = new TApplication("App", NULL, NULL);
        TCanvas * cnv = new TCanvas("canvas", "canvas", 750,600);
        //il tgraph è costruito a partire dal file
        TGraphErrors* graf = new TGraphErrors(argv[1]);
        TF1 * f= new TF1("func",relazione_due, -10,10,3);
        //lambda
        f->SetParameter(1,0);
        //delta_r
        f->SetParameter(2,0);
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
