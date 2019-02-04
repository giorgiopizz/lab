/*
c++ -o esercizio02 esercizio02.cpp `root-config --cflags --glibs`
*/

#include <iostream>

#include "TApplication.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TFitResult.h"
#include "TMatrixDSym.h"

using namespace std;

int main(int argc, char** argv)
{
  // Local variables
  const int nPar = 3;

  double x_p = 32;
  double y_p;
	
  double* a = new double [nPar];
  double err = 0;
  double sigma_i;
  double sigma_ij;

  if (argc < 2)
    {
      cout << "Not enough parameters: ./esercizio02 filename.txt" << endl;
      return 1;
    }

  gStyle->SetOptFit(1112);

  TApplication* myApp = new TApplication("myApp", NULL, NULL);
  TCanvas* myC = new TCanvas("myC","myC",0,0,700,500);
  
  TGraphErrors* myGraph = new TGraphErrors(argv[1]);
  myGraph->SetMarkerStyle(20);
  myGraph->SetMarkerSize(0.2);

  myC->cd();
  myGraph->Draw("AP");
  myC->Modified();
  myC->Update();

  TFitResultPtr r = myGraph->Fit("pol2","S");
  r->Print("V");
  TMatrixDSym cov = r->GetCovarianceMatrix();
	
  TF1* myFun = myGraph->GetFunction("pol2");
  y_p = myFun->Eval(x_p);
  
  for (int i = 0; i < nPar; i++)
    {
      a[i] = pow (x_p, i);
      cout << "a[" << i << "] = " << a[i] << endl;
      sigma_i = r->ParError(i);
      cout << "ParError(" << i << ") = " << sigma_i << endl;
      err += pow((sigma_i*a[i]),2);
    }
  cout << "Error WITHOUT correlations: " << sqrt(err) << endl;

  for (int i = 0; i < nPar; i++)
    {
      for (int j = 0; j < nPar; j++)
	{
	  if (i < j)
	    {
	      sigma_ij = cov(i,j);
	      cout << "Cov(" << i << "," << j << ") = " << sigma_ij << endl;
	      err += 2*(sigma_ij*a[i]*a[j]);
	    }
	  else continue;
	}		
    }  
  cout << "Error WITH correlations: " << sqrt(err) << endl;
  
  myC->cd();
  int NPoint = myGraph->GetN();
  myGraph->SetPoint(NPoint, x_p, y_p);
  myGraph->SetPointError(NPoint, 0., sqrt(err));
  myGraph->Draw("P same");
  myC->Modified();
  myC->Update();

  myApp->Run();
  return 0;
}
