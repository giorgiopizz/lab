/*
c++ -o Mandelbrot Mandelbrot.cpp complesso.cc `root-config --glibs --cflags`
*/

#include <iostream>
#include <cmath>
#include <string>

#include "TStyle.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TH2F.h"
#include "TAxis.h"

#include "complesso.h"

#define PIXELSIZE 0.005

using namespace std;

int main()
{
  TApplication* myApp = new TApplication("myApp", NULL, NULL);

  // Crea un istogramma in 2D inserendo i range e i bin sull'asse delle x e sull'asse delle y
  double xmin = -2., xmax = 1.;
  double ymin = -1., ymax = 1.;
  int NbinX = (int)((xmax-xmin)/PIXELSIZE); 
  int NbinY = (int)((ymax-ymin)/PIXELSIZE); 
  int M = 100;

  TH2F* histo2d = new TH2F ("isto_name","histo_title", NbinX, xmin, xmax, NbinY, ymin, ymax);
	
  for (int i = 1; i <= NbinX; i++)
    {
      for (int j = 1; j <= NbinY; j++)
	{
	  complesso c(histo2d->GetXaxis()->GetBinCenter(i), histo2d->GetYaxis()->GetBinCenter(j));
	  complesso z1(0,0);
	  complesso z2;
	  int n;
	  for (n = 0; n < M; n++)
	    {
	      z2 = z1*z1 + c;
	      if(z2.Mod() > 2) break;
	      else z1 = z2;
	    }
	  histo2d->Fill(c.Re(),c.Im(),n);
	}
    }

  TCanvas* c1 = new TCanvas ("c1","Mandelbrot",0,0,900,600);
  c1->cd();
  gStyle->SetOptStat(0); // Non fa comparire il riquadro delle statistiche dell'istogramma
  histo2d->Draw("COLZ");
  c1->Modified();
  c1->Update();

  myApp->Run();
  return 0;
}
