/*

*/
#include <iostream>
#include <fstream>
#include <string>
#include <TApplication.h>
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
void computeChi2(TH1D* myHisto, TF1* myFun, double& Chi2, double& NDF, double& pvalue)
{
  double result = 0;
  NDF = 0.;
  for (unsigned int i = 1; i <= myHisto->GetNbinsX(); i++)
    {
      if (myHisto->GetBinContent(i) != 0.)
	{
	  result += pow((myHisto->GetBinContent(i) - myFun->Eval(myHisto->GetBinCenter(i))),2.) / myHisto->GetBinContent(i);
	  NDF++;
	}
    }

  Chi2   = result;
  NDF   -= myFun->GetNpar();
  pvalue = TMath::Prob(Chi2,NDF);
}
double gauss(double * x, double * par){
        double gauss =par[0]*exp(-0.5*pow(((x[0]-par[1])/par[2]),2));
        return gauss;
}
double exponential(double * x, double * par){
        //double parabola = par[3]+par[4]*x[0]+par[5]*pow(x[0],2);
        double expo = par[1]*exp(par[0]*x[0]);
        return expo;
}
double sumgauss(double * x, double * par){
        return par[0]*exp(-0.5*pow(((x[0]-par[1])/par[2]),2))+par[3]*exp(-0.5*pow(((x[0]-par[4])/par[5]),2));
}
double fun(double * x, double * par){
        return gauss(x,&par[0])+gauss(x,&par[3])+exponential(x,&par[6]);
}
double fun2(double * x, double * par){
         return par[0]*exp(-0.5*pow(((x[0]-par[1])/par[2]),2))+par[3]*exp(-0.5*pow(((x[0]-par[4])/par[5]),2))+exp(par[6]*x[0])*par[7];
}
int main(int argc, char ** argv){
        TApplication * app = new TApplication("myApp",NULL,NULL);
        TCanvas* cnv=new TCanvas("myCanv","myCanv",0,0,1200,800);
        double nBins=150,xMin=0, xMax=200;
        TH1D * histo= new TH1D("name","2 gaus exp",nBins, xMin, xMax);
        gStyle->SetOptFit(1111);
        //[p0]*exp(-0.5*pow(((x-[p1])/[p2]),2))+[p3]*exp(-0.5*pow(((x-[p4])/[p5]),2))+exp([p6]*x)*[p7]
        TF1 * myFun = new TF1("fun", fun2,0,200,8);
        myFun->SetParameter(0,1);
        myFun->SetParameter(1,135);
        myFun->SetParameter(2,2.545);
        myFun->SetParameter(4,170);
        myFun->SetParameter(5,-2.665);
        myFun->SetParameter(6,-0.01);
        myFun->SetParameter(7,2284);
        myFun->SetParName(0,"Ampl1");
        myFun->SetParName(1,"Mean1");
        myFun->SetParName(2,"Sigma1");
        myFun->SetParName(3,"Ampl2");
        myFun->SetParName(4,"Mean2");
        myFun->SetParName(5,"Sigma2");
        if(!ReadData(argv[1], histo)){
                cout << "Errore";
        }
        cnv->cd();
        histo->Draw("same");
        histo->Fit("fun");
        cout<< myFun->GetChisquare()/myFun->GetNDF()<<endl;
        cout << "Il chi-quadro di ROOT: "<<myFun->GetChisquare()<<"\nIl ridotto: "<<myFun->GetChisquare()/myFun->GetNDF()<<"Il p-value: "<<myFun->GetProb()<<endl;
        double chi2, ndf, prob;
        computeChi2(histo,myFun,chi2,ndf,prob);
        cout << "Il mio chi-quadro: "<<chi2<<"\nIl ridotto: "<<chi2/ndf<<"Il p-value: "<<prob<<endl;
        TF1* mySignal = new TF1("mySignal", sumgauss, xMin, xMax, 6);
        mySignal->SetLineColor(kBlack);
        mySignal->SetParameter(0,myFun->GetParameter(0));
        mySignal->SetParameter(1,myFun->GetParameter(1));
        mySignal->SetParameter(2,myFun->GetParameter(2));
        mySignal->SetParameter(3,myFun->GetParameter(3));
        mySignal->SetParameter(4,myFun->GetParameter(4));
        mySignal->SetParameter(5,myFun->GetParameter(5));
        cout << "\nNumber of entries for the signal (i.e. Gaussian): ";
        cout << nBins / (xMax - xMin) * mySignal->Integral(xMin, xMax);
        cout << endl;

        // Compute number of entries for the background (i.e. Parabola)
        TF1* myBackground = new TF1("myBackground", exponential, xMin, xMax, 3);
        myBackground->SetLineColor(kBlue);
        myBackground->SetParameter(0,myFun->GetParameter(6));
        myBackground->SetParameter(1,myFun->GetParameter(7));
        cout << "Number of entries for the background (i.e. Esponenziale): ";
        cout << nBins / (xMax - xMin) * myBackground->Integral(xMin, xMax)<<endl;
        cout << endl;
        mySignal->Draw("same");
        myBackground->Draw("same");
        cnv->Modified();
        cnv->Update();
        //cnv->Print("es3.png","png");
        app->Run();

}
