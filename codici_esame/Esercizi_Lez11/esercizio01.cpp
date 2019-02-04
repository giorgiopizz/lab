/*
c++ -o esercizio01 esercizio01.cpp `root-config --cflags --glibs`
*/

#include <iostream>

#include "TApplication.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TAxis.h"

using namespace std;

int main(int argc, char** argv)
{
  if (argc < 2)
    {
      cout << "Not enough parameters: ./esercizio01 filename.txt" << endl;
      return 1;
    }
  
  gStyle->SetOptFit(1112);

  TApplication* myApp = new TApplication("myApp", NULL, NULL);
  TCanvas* myC = new TCanvas("myC","myC",0,0,700,500);
  TGraphErrors* myGraph = new TGraphErrors(argv[1]);
  myGraph->SetMarkerStyle(20);
  myGraph->SetTitle("Capacitor charge");
  myGraph->GetXaxis()->SetTitle("t [seconds]");
  myGraph->GetYaxis()->SetTitle("V(t) [Volt]");
  
  TF1* myFun = new TF1 ("myFun","[0] * (1 - exp(-x/[1]))");
  myFun->SetParName(0,"Ampli");
  myFun->SetParName(1,"tau");
  myFun->SetParameter(0,8);
  myFun->SetParameter(1,0.004);

  myC->cd();
  myGraph->Draw("AP");
  myGraph->Fit("myFun");   
  myC->Modified();
  myC->Update();

  cout << "\nThe result of the fit with the model V(t) = V0 * [1 - exp(-t/tau)] is:" << endl;
  cout << "V0 = " << myFun->GetParameter(0) << " +/- " << myFun->GetParError(0) << endl;
  cout << "RC = " << myFun->GetParameter(1) << " +/- " << myFun->GetParError(1) << endl;
    
  myApp->Run();
  return 0;
}
