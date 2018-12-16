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
        if ((f->Eval(xm)+0.5-lkmax)*(f->Eval(min)+0.5-lkmax) < 0){
                return BisezioneRicorsiva(f, min, xm, precision,lkmax);
        }
        else{
                return BisezioneRicorsiva(f, xm, max, precision,lkmax);
        }
}

void intervallomu(double muhat,int nsample,TF1 *floglike,double *interval, double lmin,double lmax){
        double lkmax=floglike->Eval(muhat);
        interval[0]=BisezioneRicorsiva(floglike,lmin,muhat,0.001,lkmax);
        interval[1]=BisezioneRicorsiva(floglike,muhat,lmax,0.001,lkmax);
}
void intervallosigma(double muhat,int nsample,TF1 *floglike,double *interval, double lmin,double lmax){
        double lkmax=floglike->Eval(muhat);
        interval[0]=BisezioneRicorsiva(floglike,lmin,muhat,0.001,lkmax);
        interval[1]=BisezioneRicorsiva(floglike,muhat,lmax,0.001,lkmax);
}


double loglikegaussmu(double * x, double *par){
        //[0] è sigma, [1] è estrazioni,[2]....[n] sono le xi
        //x[0] è mu
        double fval=0;
        for(int i=2;i<par[1];i++){
                fval+=pow(par[i]-x[0],2);
        }
        return -0.5*(par[1]*log(2*M_PI)+par[1]*log(par[0])+fval/(2*pow(par[0],2)));
}
double loglikegausssigma(double * x, double *par){
        //[0] è mu, [1] è estrazioni,[2]....[n] sono le xi
        //x[0] è sigma
        double fval=0;
        for(int i=2;i<par[1];i++){
                fval+=pow(par[i]-par[0],2);
        }
        return -0.5*(par[1]*log(2*M_PI)+par[1]*log(x[0])+fval/(2*pow(x[0],2)));
}
int main(){
        int estrazioni=100;

        //f->SetParameter(0,mu);
        TRandom1 casuale(time(NULL));
        double x;

        //cout << "Ho stimato mu come: "<<somma/estrazioni<<"± "<<sigma<<endl;
        //l'instogramma comprende solo i valori tra + o - 5sigma
        //double min=mu-5*sigma, max=mu+5*sigma;
        /*TApplication * app=new TApplication("ciao",NULL,NULL);
        TCanvas *cnv= new TCanvas("Ciao","Titolo",0,0,700,500);*/
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

        double mu=5, sigma=2.0;
        double muhat,sigmahat, lmin=0,lmax=100;
        TF1* floglike= new TF1("floglike", "-[1]*TMath::Log(x)-[1]/x*[0]",lmin,lmax);
        TF1* floglikeguassianamu= new TF1("floglikeguassianamu",loglikegaussmu,-10,10,2+estrazioni);
        TF1* floglikeguassianasigma= new TF1("floglikeguassianasigma",loglikegausssigma,0,5,2+estrazioni);
        double intervalmu[2],intervalsigma[2];
        double sum=0,sumq=0;
        for(int j=0;j<estrazioni;j++) sum+=casuale.Gaus(mu,sigma);
        muhat=sum/estrazioni;
        for(int j=0;j<estrazioni;j++) sumq+=pow(casuale.Gaus(mu,sigma)-muhat,2);
        sigmahat=sqrt(sumq/(estrazioni-1));
        //devo settare i parametri delle due funzioni floglikeguassianamu e floglikeguassianasigma
        floglikeguassianamu->SetParameter(0,sigmahat);
        floglikeguassianamu->SetParameter(1,estrazioni);
        for(int i=2;i<estrazioni;i++){
                x=casuale.Gaus(mu,sigma);
                floglikeguassianamu->SetParameter(i,x);
        }
        floglikeguassianasigma->SetParameter(0,muhat);
        floglikeguassianasigma->SetParameter(1,estrazioni);
        for(int i=2;i<estrazioni;i++){
                x=casuale.Gaus(mu,sigma);
                floglikeguassianasigma->SetParameter(i,x);
        }
        /*floglikeguassianamu->Draw();
        cnv->cd(2);
        floglikeguassianasigma->Draw();*/


        intervallomu(muhat,estrazioni,floglikeguassianamu,intervalmu,-10,10);
        intervallosigma(sigmahat,estrazioni,floglikeguassianasigma,intervalsigma,0,5);

        //copertura
        double copertura=0;
        int cicli=100;
        for(int i=0;i<cicli;i++){
                sum=0;
                for(int j=0;j<estrazioni;j++) sum+=casuale.Gaus(mu,sigma);
                muhat=sum/estrazioni;
                intervallomu(muhat,estrazioni,floglikeguassianamu,intervalmu,-10,10);
                if(intervalmu[0]<mu&&intervalmu[1]>mu) copertura++;
        }
        /*
        TLine lmedia(muhat,floglike->Eval(lmin),muhat,floglike->Eval(muhat));
        lmedia.SetLineColor(3);
        TLine llmezzi(lmin,floglike->Eval(muhat)-0.5,lmax,floglike->Eval(muhat)-0.5);
        lmedia.SetLineColor(3);
        floglike->Draw();
        lmedia.Draw("same");
        llmezzi.Draw("same");*/

        //cnv->Print("Likelihood(1000).png");
        cout<<"copertura:"<<copertura/cicli<<endl;
        cout <<"Valore di mu cappuccio:"<<muhat<<endl;
        cout << "Intervallo dalla Likelihood:"<<intervalmu[0]<<" mu "<<intervalmu[1]<<endl;
        cout <<"Valore di sigma cappuccio:"<<sigmahat<<endl;
        cout << "Intervallo dalla Likelihood:"<<intervalsigma[0]<<" mu "<<intervalsigma[1]<<endl;
        //app->Run();
        //app->Run();

}
