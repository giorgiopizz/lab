/*
c++ -o fitTGraphErrors fitTGraphErrors.cpp `root-config --cflags --glibs`
*/

#include <iostream>
#include <cmath>

#include "TStyle.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TFitResult.h"
#include "TMatrixDSym.h"
#include "TMath.h"

using namespace std;
double computeChi2(TGraphErrors* myData, TF1* myFun){
        double result = 0;
        for (int i = 0; i < myData->GetN(); i++)
        {
                result += pow(myData->GetY()[i] - myFun->Eval(myData->GetX()[i]),2.) /(pow(myData->GetErrorY(i),2.) + pow(myFun->Derivative(myData->GetX()[i])*myData->GetErrorX(i),2.));
        }

        return result;
}
TGraph * computeContour(TGraphErrors* myData,TF1* myFun, double delta){
        TGraph* grafico=new TGraph();
        TFitResultPtr r = myData->Fit(myFun,"S");
        TMatrixDSym cov = r->GetCovarianceMatrix();
        double constO=myFun->GetParameter(0);
        double scaleO=myFun->GetParameter(1);
        double min=computeChi2(myData,myFun);
        double constErr=sqrt(cov(0,0));
        double scaleErr=sqrt(cov(1,1));
        double constIncr=4*constErr/300;
        double scaleIncr=4*scaleErr/300;
        //vector<double> const,scale;
        for(int i=0;i<300;i++){
                double dmin=99999999;
                int jmin[2]={-1,-1};
                double prec;
                bool cresc=false;
                for(int j=0;j<300;j++){
                        double x=constO-2*constErr+j*constIncr;
                        double y=scaleO-2*scaleErr+i*scaleIncr;
                        myFun->SetParameter(0,x);
                        myFun->SetParameter(1,y);
                        //cout<<computeChi2(myData,myFun)-min<<endl;
                        double eps=0.1;
                        double newChi2=computeChi2(myData,myFun);
                        if(sqrt(pow(newChi2-min+delta,2))>prec && !cresc){
                                dmin=9999999;
                                cresc=true;
                        }
                        prec=sqrt(pow(newChi2-min+delta,2));
                        cout<<i<<" "<< newChi2<<" "<< min << " "<<dmin<<"  "<<sqrt(pow(newChi2-min+delta,2))<<endl;

                        if(sqrt(pow(newChi2-min-delta,2))<dmin){
                                if(newChi2-min-delta<eps){
                                        jmin[cresc]=j;
                                        dmin=sqrt(pow(newChi2-min-delta,2));
                                }
                        }

                        /*if(newChi2-min<(delta+eps)&&newChi2-min>(delta-eps)){
                                grafico->SetPoint(grafico->GetN(),constO-2*constErr+j*constIncr,scaleO-2*scaleErr+i*scaleIncr);
                        }*/
                }

                for (int b=0;b<2;b++) if(jmin[b]>0) grafico->SetPoint(grafico->GetN(),constO-2*constErr+jmin[b]*constIncr,scaleO-2*scaleErr+i*scaleIncr);
        }
        return grafico;
}


double cauchy(double* x, double* par)
{
  double val = par[0] + par[1]/(x[0]*x[0]);
  // ### Test fit pathologies ###
  // double val = par[0] + 1000*log(par[1])/(x[0]*x[0]);
  // double val = par[0]*par[1] + 8023/(x[0]*x[0]);
  // ############################
  return val;
}




int main(int argc, char** argv)
{
  if (argc < 2)
    {
      cout << "Not enough parameters: ./fitTGraphErrors filename.txt" << endl;
      return 1;
    }

  gStyle->SetOptFit(1112);

  TApplication* myApp = new TApplication("myApp", NULL, NULL);


  // ########################################
  // # Choice of the minimization algorithm #
  // ########################################
  // Use numerical minimization algorithm: MIGRAD
  TF1* myFun = new TF1("myFun",cauchy,400,1000,2);
  // For linear models (i.e. linear as a function of the parameters)
  // the minimization corresponds to a simple matrix inversion (i.e.
  // no need to call MIGRAD)
  // TF1* myFun = new TF1("myFun","1 ++ 1/(x*x)",400,1000);


  myFun->SetParameter(0,1.6);
  myFun->SetParameter(1,8e3);
  myFun->SetParName(0,"Const");
  myFun->SetParName(1,"Scale");

  // TGraphErrors constructor from file
  TGraphErrors* myGraph = new TGraphErrors(argv[1]);
  /*myGraph->GetXaxis()->SetTitle("lambda (nm)");
  myGraph->GetYaxis()->SetTitle("Refractive index");
  myGraph->SetMarkerStyle(20);
  myGraph->SetMarkerSize(0.4);

  myC0->cd();
  myGraph->Draw("AP");
  TFitResultPtr r = myGraph->Fit("myFun","S");
  myC0->Modified();
  myC0->Update();*/
/*
  cout << "\nReduced Chi-2: " << myFun->GetChisquare()/myFun->GetNDF() << endl;
  cout << "p-value: " << myFun->GetProb() << endl;

  double Chi2, NDF, pvalue;
  computeChi2(myGraph,myFun,Chi2,NDF,pvalue);
  cout << "\nMy Chi-2: " << Chi2 << endl;
  cout << "My NDF: " << NDF << endl;
  cout << "My reduced Chi-2: " << Chi2/NDF << endl;
  cout << "My p-value: " << pvalue << endl;

  r->Print("V");

*/
  TCanvas* myC1 = new TCanvas("myC1","myC1",10,10,700,500);
  TGraph* least2Contour2D = computeContour(myGraph,myFun,1.);
  myC1->cd();
  least2Contour2D->SetMarkerStyle(20);

  least2Contour2D->Draw("AP");
  myC1->Modified();
  myC1->Update();

  myApp->Run();
  return 0;
}
