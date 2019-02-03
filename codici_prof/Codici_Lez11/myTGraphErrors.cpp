/*
c++ -o myTGraphErrors myTGraphErrors.cpp `root-config --cflags --glibs`
*/

#include <iostream>
#include <cmath>

#include "TApplication.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TAxis.h"

using namespace std;

int main(int argc, char** argv)
{
  if (argc < 2)
    {
      cout << "Not enough parameters: ./myTGraphErrors filename.txt" << endl;
      return 1;
    }
  
  TApplication* myApp = new TApplication("myApp", NULL, NULL);
  TCanvas* myC = new TCanvas("myC","myC",0,0,700,500);

  // TGraphErrors default constructor and SetPoint method
  double x,y;
  int nPoints   = 40;
  double period = 10;
  double errX   = period / nPoints;
  double errY   = 0.05;
  TGraphErrors myGraph0;
  for (int i = 0; i < nPoints; i++)
    {
      x = static_cast<double>(i) / nPoints * period;
      y = sin(2.*3.14/period * x);
      myGraph0.SetPoint(myGraph0.GetN(),x,y);
      myGraph0.SetPointError(myGraph0.GetN()-1,errX,errY);
    }
  myGraph0.GetXaxis()->SetTitle("x (units)");
  myGraph0.GetYaxis()->SetTitle("y (units)");
  myGraph0.SetMarkerStyle(20);
  myGraph0.SetMarkerSize(0.5);

  // TGraphErrors constructor from file
  TGraphErrors myGraph1(argv[1]);
  myGraph1.SetMarkerStyle(21);
  myGraph1.SetMarkerSize(0.5);
  myGraph1.SetMarkerColor(kRed);

  myC->cd();
  myGraph0.Draw("AP");
  myGraph1.Draw("P same");
  myC->Modified();
  myC->Update();

  myApp->Run();
  return 0;
}
