/*
c++ -o esempio01 esempio01.cpp `root-config --cflags --glibs`
*/

#include <iostream>
#include <fstream>

#include "TStyle.h"
#include "TApplication.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TF1.h"

#define FILE_NAME "ntuple.txt"

using namespace std;

int main (int argc, char** argv)
{
  double a,b;
  TNtuple* myNtuple = new TNtuple ("myNtuple","myNtuple","x:y");

  gStyle->SetOptStat(1110);
  TApplication* myApp = new TApplication("myApp",NULL,NULL);


  // ####################
  // # Reading the data #
  // ####################
  ifstream in (FILE_NAME, ios::in);
  if (in.good() == false)
    {
      cout << "Error opening the file " << FILE_NAME << endl;
      exit(1);
    }

  while (!in.eof())
  {
    in >> a >> b;

    if (in.eof() == true)
      break;

    myNtuple->Fill(a,b);
  }
  in.close();
  myNtuple->Scan();


  // #####################
  // # Plotting the data #
  // #####################
  TCanvas* c1 = new TCanvas ("c1","Marginal distribution of x");
  TH1D* h1 = new TH1D("h1","h1",100,0,20);
  myNtuple->Draw("x >> h1");
  c1->cd();
  h1->Draw();
  c1->Modified();
  c1->Update();


  TCanvas* c2 = new TCanvas ("c2","Marginal distribution of y");
  TH1D* h2 = new TH1D("h2","h2",100,0,20);
  myNtuple->Draw("y >> h2");
  c2->cd();
  h2->Draw();
  c2->Modified();
  c2->Update();


  TCanvas* c3 = new TCanvas ("c3","Joint distribution");
  // TGraph* myGraph = new TGraph(myNtuple->GetSelectedRows(),myNtuple->GetV2(),myNtuple->GetV1());
  TH2D* h3 = new TH2D("h3","h3",100,0,20,100,0,20);
  myNtuple->Draw("x:y >> h3");
  c3->cd();
  h3->Draw("gcolz");
  // myGraph->Draw();
  c3->Modified();
  c3->Update();


  TCanvas* c4 = new TCanvas ("c4","Event selection");
  TH1D* h4 = new TH1D("h4","h4",100,0,20);
  myNtuple->Draw("x >> h4","(y-8)*(y-8) + (x-8)*(x-8) < 2");
  c4->cd();
  h4->Draw();

  TF1* myFunc = new TF1("myFunc","gaus",0,20);
  h4->Fit("myFunc");

  c4->Modified();
  c4->Update();


  myApp->Run();
  return 0;
}
