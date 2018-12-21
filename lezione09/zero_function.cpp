#include <iostream>
#include <TH1.h>
#include <TF1.h>
#include <TRandom1.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TLine.h>
using namespace std;
double BisezioneRicorsiva (TF1* f, double min, double max, double precision) {
        double xm = 0.5*(min+max);
        if (max-min<precision){

                return xm;
        }
        if (f->Eval(xm)*f->Eval(min) < 0){
                cout<<min<<xm<<max<<f->Eval(min)<<" "<<f->Eval(xm)<<" "<<"Yeee  "<<f->GetParameter(0)<<" "<<f->GetParameter(1)<<endl;
                return BisezioneRicorsiva(f, min, xm, precision);
        }
        else{
                cout<<min<<xm<<max<<f->Eval(xm)<<" "<<f->Eval(max)<<" "<<"naaa"<<f->GetParameter(0)<<" "<<f->GetParameter(1)<<endl;

                return BisezioneRicorsiva(f, xm, max, precision);
        }
}
double retta(double * x, double * par){
        return x[0]*par[0]+par[1];
}

int main(){
        TApplication * app=new TApplication("ciao",NULL,NULL);
        TCanvas *cnv= new TCanvas("Ciaooo","Titolo",0,0,700,500);
        TF1 * f= new TF1("funzione", retta,-3,2,2);
        f->SetParameter(0,1);
        f->SetParameter(1,2);
        //TLine llmezzi(-3,f->Eval(0)-2,3,f->Eval(0)-2);
        f->Draw();
        //llmezzi.Draw("same");
        //TF1 * f2= new TF1("f2", "funzione+4",-3,3);
        double min=-3;
        double max=2;
        cout << BisezioneRicorsiva(f, min,max,0.0001)<<endl;
        cnv->Modified();
        cnv->Update();
        app->Run();


}
