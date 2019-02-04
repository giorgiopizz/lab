/*
c++ -o testAnalyzer testAnalyzer.cpp Analyzer.cc `root-config --cflags --glibs`
*/

#include <iostream>

#include "TApplication.h"
#include "TCanvas.h"

#include "Analyzer.h"

using namespace std;

double myExp (double* x, double* par)
{
  return par[0] * (1 - exp(-x[0]/par[1]));	
}	

int main (int argc, char** argv) 
{    
  double chi2 = 0, pvalue = 0;
  int    NDF  = 0;
  
  if (argc != 3)
    {
      cout << "The number of arguments shoul be exactly 2: ./testAnalyzer dataFileName.txt [counts/measurements]" << endl;
      return 1;
    }

  gStyle->SetOptFit(1112);
  
  analyzer myAnalyzer = analyzer();
  if (myAnalyzer.setData(argv[1],argv[2]) == true)
    cout << "Data file read successfully!\n" << endl;
  else
    {
      cout << "Error from [analyzer::setData]" << endl;
      return 1;
    }
  
  TApplication app("app", NULL, NULL);
  TCanvas* c1 = new TCanvas ("c1","c1",0,0,700,500);
  c1->cd();


  // ######################################
  // # Choose between counts/measurements #
  // ######################################
  // TH1D* histo = myAnalyzer.getHisto();
  // histo->Draw();
  TGraphErrors* graph = myAnalyzer.getGraph();
  graph->Draw("AP");

  
  double mean, stdDev, meanError;
  mean      = myAnalyzer.getMeanX();
  stdDev    = myAnalyzer.getStdDevX();
  meanError = myAnalyzer.getMeanError();
  cout << "MeanX: " << mean <<  " stdDevX: " << stdDev << " meanError: " << meanError << "\n" << endl;

  vector<double>* xMeas = myAnalyzer.getxMeas();
  vector<double>* xErr  = myAnalyzer.getxErr();
  myAnalyzer.computeMomenta (xMeas, xErr, mean, stdDev, meanError);
  cout << "MeanX: " << mean <<  " stdDevX: " << stdDev << " meanError: " << meanError << "\n" << endl;


  // ######################################
  // # Choose between counts/measurements #
  // ######################################
  // TF1* fitFunc = new TF1 ("fitFunc","gaus(0) + pol2(3)");
  // gaus(0): use coefficients starting from index '0'
  // pol2(3): use coefficients starting from index '3', gaus needs 3 coefficients, from '0' to '2'
  // fitFunc->SetParameter(1,histo->GetMean());
  // fitFunc->SetParameter(2,histo->GetRMS());
  TF1* fitFunc = new TF1 ("fitFunc",myExp,myAnalyzer.getMinX(),myAnalyzer.getMaxX(),2);    
  fitFunc->SetParameter(1,1e-3);


  myAnalyzer.fitData(fitFunc,myAnalyzer.getMinX(),myAnalyzer.getMaxX());
  myAnalyzer.computeChi2(fitFunc,chi2,NDF,pvalue);

  cout << "chi2: " << chi2 <<  " NDF: " << NDF << " p-value: " << pvalue << endl;

  c1->Modified();
  c1->Update();

  TCanvas * c2 = new TCanvas ("c2","c2",10,10,700,500);
  c2->cd();


  // ######################################
  // # Choose between counts/measurements #
  // ######################################
  // TGraph* contourPlot = myAnalyzer.computeContour(fitFunc,1,1,2);
  TGraph* contourPlot = myAnalyzer.computeContour(fitFunc,1,0,1);

  
  contourPlot->SetTitle("Contour plot");
  contourPlot->GetXaxis()->SetTitle("parA");
  contourPlot->GetYaxis()->SetTitle("parB");
  contourPlot->SetMarkerStyle(20);
  contourPlot->SetMarkerSize(0.5);
  contourPlot->Draw("AP");

  c2->Modified();
  c2->Update();

  double meas1 = myAnalyzer.getMeanX(), err1 = myAnalyzer.getStdDevX();
  double meas2 = 5.0, err2 = 0.0;
  double significance = 0.05;
  double n1 = myAnalyzer.getDataNumber();
  if (myAnalyzer.testCompatibility(pvalue, meas1, err1, meas2, err2, significance, "tStudent", n1) == true)
    cout << "\nThe two measurements are compatible ";
  else
    cout << "\nThe two measurements are NOT compatible ";
  cout << "and the p-value is " << pvalue << endl;

  app.Run();
  return 0;
}
