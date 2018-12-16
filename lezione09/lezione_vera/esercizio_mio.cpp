#include <iostream>
#include <TH1.h>
#include <TF1.h>
#include <TRandom1.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TLine.h>
#include <cstdlib>
#include <ctime>

using namespace std;

double rand_range(double min,double max){
        return min + (max-min) * (1. * rand()) / (1. * RAND_MAX);
}
double f_exp(double x){
        double mu=2.5;
        return 1/mu*exp(-x/mu);
}
double rand_TAC(double xmin,double xmax,double ymin, double ymax){
        double x=0,y=0;
        do{
                x=rand_range(xmin,xmax);
                y=rand_range(ymin,xmax);
        }while(y>f_exp(x));
        return x;
}

double BisezioneRicorsiva (TF1* f, double min, double max, double precision,double lkmax) {
        double xm = 0.5*(min+max);
        if (max-min<precision){

                return xm;
        }
        if ((f->Eval(xm))*(f->Eval(min)) < 0){
                cout<<min<<" "<<xm<<" "<<max<<" "<<f->Eval(min)<<" "<<f->Eval(xm)<<" "<<"Yeee  "<<f->GetParameter(0)<<" "<<f->GetParameter(1)<<endl;
                return BisezioneRicorsiva(f, min, xm, precision,lkmax);
        }
        else{
                cout<<min<<" "<<xm<<" "<<max<<" "<<f->Eval(xm)<<" "<<f->Eval(max)<<" "<<"naaa"<<f->GetParameter(0)<<" "<<f->GetParameter(1)<<endl;

                return BisezioneRicorsiva(f, xm, max, precision,lkmax);
        }
}
void intervallo(double muhat,int nsample,TF1 *floglike,double *interval, double lmin,double lmax){
        floglike->SetParameters(muhat,nsample);
        //floglike->Draw();
        double lkmax=floglike->Eval(muhat);
        //TF1 *func=new TF1("func", "-[1]*TMath::Log(x)-[1]/x*[0]+0.5-[2]",lmin,lmax);
        TF1 *func=new TF1("func", "floglike+0.5-[2]",lmin,lmax);
        func->SetParameters(muhat,nsample,lkmax);
        cout << lkmax<<endl;
        //func->SetParameter(2,lkmax);
        interval[0]=BisezioneRicorsiva(func,lmin,muhat,0.001,-lkmax);
        interval[1]=BisezioneRicorsiva(func,muhat,lmax,0.001,-lkmax);
}


int main(){
        int estrazioni=1000;
        double minimo=0;
        double massimo=30;
        double mu=2.5;
        TF1 * f= new TF1("pdf","1/[0]*exp(-x/[0])",minimo,massimo);
        //f->SetParameter(0,mu);
        TRandom1 casuale(time(NULL));
        int bin=100;
        double x;
        srand(time(NULL));
        //calcolo l'errore su x medio
        double s,somma=0, sommaq=0;
        double sigma=mu/sqrt(estrazioni);

        //cout << "Ho stimato mu come: "<<somma/estrazioni<<"± "<<sigma<<endl;
        //l'instogramma comprende solo i valori tra + o - 5sigma
        double min=mu-5*sigma, max=mu+5*sigma;
        TApplication * app=new TApplication("ciao",NULL,NULL);
        TCanvas *cnv= new TCanvas("Ciao","Titolo",0,0,700,500);
        //TH1F *histo = new TH1F("hmedia","pdf esponenziale",100,minimo,massimo);
        /*TH1F *hmedia = new TH1F("hmedia","pdf numerica per lo stimatore",bin,min,max);

        double sum;

        int esperimenti=10000;

        for(int i=0;i<esperimenti;i++){
                sum=0;
                for(int j=0;j<estrazioni;j++){
                        //provo ad estrarre dalla esponenziale con il metodo tradizionale
                        x=rand_TAC(minimo,massimo,0,1/mu);
                        //histo->Fill(x);
                        sum+=x;
                        //sum+=casuale.Exp(mu);
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
        fgamma->Draw("same");*/
        /*
        //Mostro che la distribuzione data da rand_tac è uguale alla funzione f
        histo->Draw();
        for(int i=0;i<100;i++){
                Double_t num = histo->GetBinContent(i);
                Double_t den = histo->GetBinWidth(i);
                Double_t value = 0;
                if (den!=0)
                {
                        value = num/(estrazioni*den);
                        histo->SetBinContent(i,value);
                }
        }
        histo->Fit(f);*/



        //parte sulla Likelihood
        double muhat, lmin=min,lmax=max;
        TF1* floglike= new TF1("floglike", "-[1]*TMath::Log(x)-[1]/x*[0]",lmin,lmax);
        double interval[2];
        double sum;
        //copertura
        double copertura=0;
        int cicli=1000;
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
        //cnv->Print("Likelihood(1000).png");
        cout<<"copertura:"<<copertura/cicli<<endl;
        cout <<"Valore di mu cappuccio:"<<muhat<<endl;
        cout << "Intervallo dalla Likelihood:"<<interval[0]<<" mu "<<interval[1]<<endl;
        cnv->Modified();
        cnv->Update();
        app->Run();
        //app->Run();

}
