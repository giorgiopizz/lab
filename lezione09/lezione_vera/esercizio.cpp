#include <iostream>
#include <TH1.h>
#include <TF1.h>
#include <TRandom1.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TLine.h>
/*#include <cstlib>
#include <time>*/

using namespace std;

double BisezioneRicorsiva (TF1* f, double min, double max, double precision) {
        double xm = 0.5*(min+max);
        if (max-min<precision){
                return xm;
        }
        if (f->Eval(xm)*f->Eval(min) < 0){
                return BisezioneRicorsiva(f, min, xm, precision);
        }
        else{
                return BisezioneRicorsiva(f, xm, max, precision);
        }
}
void intervallo(double muhat,int nsample,TF1 *floglike,double *interval, double lmin,double lmax){
        floglike->SetParameters(muhat,nsample);
        floglike->Draw();
        double lkmax=floglike->Eval(muhat);
        TF1 *func=new TF1("func", "floglike+0.5",lmin,lmax);
        interval[0]=BisezioneRicorsiva(func,lmin,muhat,0.00001);
        interval[1]=BisezioneRicorsiva(func,muhat,lmax,0.00001);
}
int main(){
        int estrazioni=1000;
        double minimo=0;
        double massimo=30;
        double mu=5;
        TF1 * f= new TF1("pdf","1/[0]*exp(-x/[0])",minimo,massimo);
        f->SetParameter(0,mu);
        TRandom1 casuale(time(NULL));
        int bin=100;
        double sigma=mu/sqrt(estrazioni);
        //l'instogramma comprende solo i valori tra + o - 5sigma
        double min=mu-5*sigma, max=mu+5*sigma;
        //TApplication * app=new TApplication("ciao",NULL,NULL);
        TCanvas *cnv= new TCanvas("Ciao","Titolo",0,0,700,500);
        /*TH1F *hmedia = new TH1F("hmedia","pdf numerica per lo stimatore",bin,min,max);
        double sum;
        double x;
        int esperimenti=10000;
        for(int i=0;i<esperimenti;i++){
                sum=0;
                srand(time(NULL));
                for(int j=0;j<estrazioni;j++){
                        sum+=casuale.Exp(mu);
                }
                hmedia->Fill(sum/estrazioni);
        }
        cnv->cd();
        hmedia->Draw();
        TF1 * fgaus=new TF1("FGaus","gaus",min,max);
        hmedia->Fit(fgaus);
        fgaus->Draw("same");
        TF1 * fgamma=new TF1("FGammaDistribution","[2]*TMath::GammaDist(x,[0],0,[1])",min,max);
        fgamma->SetParameters(mu*sqrt(estrazioni),1/sqrt(estrazioni),.1);
        hmedia->Fit(fgamma,"LR+");
        fgamma->SetLineColor(4);
        fgamma->Draw("same");
        */
        //parte sulla Likelihood
        double muhat, lmin=min,lmax=max;
        TF1* floglike= new TF1("floglike", "-[1]*TMath::Log(x)-[1]/x*[0]",lmin,lmax);
        double interval[2];
        double sum;
        //copertura
        double copertura=0;
        int cicli=10000;
        for(int i=0;i<cicli;i++){
                sum=0;
                for(int j=0;j<estrazioni;j++) sum+=casuale.Exp(mu);
                muhat=sum/estrazioni;
                intervallo(muhat,estrazioni,floglike,interval,lmin,lmax);
                if(interval[0]<mu&&interval[1]>mu) copertura++;
        }
        TLine lmedia(muhat,floglike->Eval(lmin),muhat,floglike->Eval(muhat));
        lmedia.SetLineColor(3);
        TLine llmezzi(lmin,floglike->Eval(muhat)-0.5,lmax,floglike->Eval(muhat)-0.5);
        lmedia.SetLineColor(3);
        floglike->Draw();
        lmedia.Draw("same");
        llmezzi.Draw("same");
        cnv->Modified();
        cnv->Update();
        cnv->Print("Likelihood(1000).png");
        //app->Run();
        cout<<"copertura:"<<copertura/cicli<<endl;
        cout <<"Valore di mu cappuccio:"<<muhat<<endl;
        cout << "Intervallo dalla Likelihood:"<<interval[0]<<" mu "<<interval[1]<<endl;
}
