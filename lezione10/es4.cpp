#include <iostream>
#include <fstream>
#include <string>
#include <TApplication.h>
#include <TF1.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TFitResult.h>
#include <TMatrixDSym.h>
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
  cout << "\nI parametri sono: "<<myFun->GetNpar()<<endl;
  pvalue = TMath::Prob(Chi2,NDF);
}
double dist1(double*  E, double * par){
        return par[0]*pow(E[0],2)*exp(-par[1]*E[0]);
}
double dist2(double*  E, double * par){
        return par[0]*E[0]*exp(-par[1]*E[0]);
}
double dist3(double*  E, double * par){
        return par[0]*pow(E[0],2)*exp(-par[1]*pow(E[0],2));
}
int main(int argc, char ** argv){
        TApplication * app = new TApplication("myApp",NULL,NULL);
        TCanvas* cnv=new TCanvas("myCanv","myCanv",0,0,1200,800);
        double nBins=100,xMin=0, xMax=4;
        TH1D * histo= new TH1D("name","title",nBins, xMin, xMax);
        gStyle->SetOptFit(1111);
        if(!ReadData(argv[1], histo)){
                cout << "Errore";
        }
        cnv->cd();


        TF1 * myFun = new TF1("fun", dist1,xMin,xMax,2);
        myFun->SetParameter(0,1);
        myFun->SetParameter(1,5);
        myFun->SetParName(0,"A");
        myFun->SetParName(1,"B");
        myFun->SetLineColor(2);
        histo->Fit("fun","+");

        TF1 * myFun2 = new TF1("fun2", dist2,xMin,xMax,2);
        myFun2->SetParameter(0,1);
        myFun2->SetParameter(1,5);
        myFun2->SetParName(0,"A");
        myFun2->SetParName(1,"B");
        myFun2->SetLineColor(1);
        histo->Fit("fun2","+");

        TF1 * myFun3 = new TF1("fun3", dist3,xMin,xMax,2);
        myFun3->SetParameter(0,1);
        myFun3->SetParameter(1,5);
        myFun3->SetParName(0,"A");
        myFun3->SetParName(1,"B");
        myFun3->SetLineColor(3);
        histo->Fit("fun3","+");
        histo->Draw();
//vince dist2
//secondo posto dist1
//ultimo dist3
        double chi2, ndf, prob;
        computeChi2(histo,myFun2,chi2,ndf,prob);
        cout << "Il mio chi-quadro: "<<chi2<<"\nIl ridotto: "<<chi2/ndf<<"Il p-value: "<<prob<<endl;
        /*TFitResultPtr r = histo->Fit("fun2","S");
        r->Print("V");
        TMatrixDSym cov = r->GetCovarianceMatrix();
        cout << "\nRetrieved covariance matrix" << endl;
        for (int i = 0; i < myFun2->GetNpar(); i++) {
                for (int j = 0; j < myFun2->GetNpar(); j++) {
                        double sigma_ij = cov(i,j);
                        cout<<" " << sigma_ij;
                }
                cout << endl;
        }
        cout << "I parametri sono\nA: "<<myFun2->GetParameter(0)<<" ± "<<sqrt(cov(0,0))<<endl;
        cout <<"B: "<<myFun2->GetParameter(1)<<" ± "<<sqrt(cov(1,1))<<endl;
        */
        cnv->Modified();
        cnv->Update();
        cnv->Print("es4.png", "png");
        //app->Run();
}
