/*
c++ -o LikVSChi2 Likelihood_vs_Chi2.cpp `root-config --cflags --glibs`
*/

#include <iostream>
#include <fstream>

#include "TApplication.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1D.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TMath.h"

using namespace std;


void computeChi2 (TH1D* histo, double mean)
{
  int nbin = histo->GetNbinsX();
  double nbinpieni = 0;
  double chi1 = 0, chi2 = 0;

  for (int i = 1; i <= nbin; i++)
    {      
      if (histo->GetBinContent(i) > 0)
	{
	  chi1 += pow((histo->GetBinContent(i) - mean),2) / pow(histo->GetBinError(i),2);
	  chi2 += 2.*(mean - histo->GetBinContent(i) + histo->GetBinContent(i)*log(histo->GetBinContent(i)/mean));
	  nbinpieni++;
	}
      else chi2 += 2.*mean;
    }
  
  cout << "  Chi-2 per fit con i minimi quadrati (bin a 0 NON contati) " << chi1 << " Chi-2 ridotto " << chi1 / (nbinpieni-1) << " p-value " << TMath::Prob(chi1,nbinpieni-1) << endl;
  cout << "  Chi-2 per fit con likelihood (bin a 0 contati) "            << chi2 << " Chi-2 ridotto " << chi2 / (nbin-1)      << " p-value " << TMath::Prob(chi2,nbin-1) << endl;
}


int main (int argc, char** argv)
{
  TApplication* myApp = new TApplication("myApp", NULL, NULL);
  gStyle->SetOptFit(1111);


  // ###########################
  // # Verify calling sequence #
  // ###########################
  if (argc < 2)
    {
      cout << "Digitare i nomi dei file da riga di comando" << endl;
      cout << "\t./LikVSChi2 [datiL.txt/datiS.txt]" << endl;
      return 1;
    }
  
  TCanvas* c1 = new TCanvas("c1","My Canvas");
  c1->Divide(2,1);
  
  double min  = 0, max = 10;
  int Neventi = 0;
  int nbin    = max - min;
  double myrand;
  TH1D* histoMin2 = new TH1D("histoMin2","histoMin2",nbin,min,max);
  TH1D* histoLike = new TH1D("histoLike","histoLike",nbin,min,max);


  // #######################
  // # Read data from file #
  // #######################
  ifstream inF(argv[1]);
  if (inF.good() == false)
    {
      cout << "Error opening the file: " << argv[1] << endl;
      exit(1);
    }
  int nc = 0;
  while(true)
    {
      inF >> myrand;
      if (inF.eof() == true) break;
      histoMin2->Fill(myrand);
      histoLike->Fill(myrand);
      nc++;
    }
  
  cout << "Number of events: " << nc << endl;
  Neventi = nc;
  inF.close();
  
  double atteso = Neventi / (max - min);
  cout << "Expected value: " << atteso << endl;

  
  // #############################################
  // # Coss-check ROOT error assigned to the bin #
  // #############################################
  double valore, errore;
  cout << "\nBin content and error" << endl;
  for (int i = 1; i <= nbin; i++)
    {
      valore = histoMin2->GetBinContent(i);
      errore = histoMin2->GetBinError(i);
      cout << i << ") " << valore << " +/- " << errore << endl;
      cout << "   " << errore - sqrt(valore) << endl;
    }

  
  c1->cd(1);
  histoMin2->Draw();
  c1->cd(2);
  histoLike->Draw();


  TF1* funzione = new TF1("pol0","pol0",0,10);
  double meanMin2, errMin2, chiMin2, ndfMin2;
  double meanLike, errLike, chiLike, ndfLike;

  
  // #############
  // # Chi-2 fit #
  // #############
  histoMin2->Fit("pol0");
  meanMin2 = funzione->GetParameter(0);
  errMin2  = funzione->GetParError(0);
  chiMin2  = funzione->GetChisquare();
  ndfMin2  = funzione->GetNDF();

  cout << "\nFit minimi quadrati " << meanMin2 << " errore " << errMin2 << " chiq " << chiMin2 << " chiq/ndf " << chiMin2/ndfMin2 << endl;
  cout << "  Numero di deviazioni dal valore atteso " << fabs(meanMin2 - atteso) / errMin2 << "\n" << endl;

  
  // ##################
  // # Likelihood fit #
  // ##################
  TFitResultPtr resultL = histoLike->Fit("pol0","S L");
  meanLike = funzione->GetParameter(0);
  errLike  = funzione->GetParError(0);
  chiLike  = 2. * resultL->MinFcnValue(); // Correct way to compute inference with a likelihood fit
  ndfLike  = funzione->GetNDF();

  cout << "\nFit likelihood " << meanLike << " errore " << errLike << " chiq " << chiLike << " chiq/ndf " << chiLike/ndfLike << endl;
  cout << "  Numero di deviazioni dal valore atteso " << fabs(meanLike - atteso) / errLike << endl;


  // #################
  // # Compute Chi-2 #
  // #################
  cout << "\nCHIQUADRO FIT OPZIONE Min2 " << endl;
  computeChi2(histoMin2, meanMin2);
  cout << "\nCHIQUADRO FIT OPZIONE Likelihood " << endl;
  computeChi2(histoLike, meanLike);

  
  c1->Modified();
  c1->Update();
  
  myApp->Run();
  return 0;
}
