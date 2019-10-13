/*
c++ -o esercizio03 esercizio03.cpp myNtuple.cc `root-config --cflags --glibs`
*/

#include <iostream>

#include "TApplication.h"
#include "TCanvas.h"
#include "TH2D.h"

#include "myNtuple.h"

#define FIELDS 2

int main (int argc, char** argv)
{
  std::string fileIn;
  std::string fileOut;
  
  if (argc < 3)
    {
      std::cout << "Not enough parameters: .\esercizio03 input_file_name output_file_name" << std::endl;
      return 1;
    }
  
  fileIn  = argv[1];
  fileOut = argv[2];
  
  TApplication* myApp = new TApplication("myApp",&argc,argv);
  
  myNtuple* myNin  = new myNtuple(FIELDS);
  myNtuple* myNout = new myNtuple(FIELDS);

  myNin->LoadFromFile(fileIn);

  std::vector<double*>* ptr = myNin->GetNtuplePtr();
  for (unsigned int i = 0; i < myNin->GetEntries(); i++)
    {
      if (((*ptr)[i][0]*(*ptr)[i][0] + (*ptr)[i][1]*(*ptr)[i][1] > 2) && ((*ptr)[i][0]*(*ptr)[i][0] + (*ptr)[i][1]*(*ptr)[i][1] < 16))
	myNout->AddEntry((*ptr)[i]);
    }
  myNout->Write2File(fileOut);

  TCanvas* c0 = new TCanvas("c0","c0",0,0,700,500);
  TH2D* histo = new TH2D("histo","histo",100,-5,5,100,-5,5);
  myNout->Fill2DHisto(0,1,histo);
  c0->cd();
  histo->Draw("gcolz");
  c0->Modified();
  c0->Update();

  delete myNin;
  delete myNout;

  myApp->Run();
  return 0;
}
