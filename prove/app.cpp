#include <TStyle.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TF1.h>


double fgaus (double x, double mu, double sigma)
{
  return exp(-0.5*pow((x-mu),2)/(sigma*sigma))/sqrt(2*M_PI*sigma*sigma);
}

double rand_range(double min, double max)
{
  return min + (max - min) * rand() / (1. * RAND_MAX);
}

double rand_TAC_gaus (double mu, double sigma)
{
  double xMin=mu-5*sigma;
  double xMax=mu+5*sigma;
  double yMin=0.;
  double yMax=1./sqrt(2*M_PI*sigma*sigma);
  double x=0., y=0.;
  do
    {
      x = rand_range(xMin, xMax);
      y = rand_range(yMin, yMax);
    } while (y > fgaus(x, mu, sigma));
  return x;
}

double myGauss (double* x, double* par)
{
  return par[0] * exp(-0.5*((x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2])));
}


int main()
{
  int nBins    = 100;
  double xMin  = 0;
  double xMax  = 10;
  int N        = 10000;
  double mean  = 5;
  double sigma = 1;
  
  // Stampa i parametri del fit sull’istogramma,
  // bisogna includere #include <TStyle.h>
  gStyle->SetOptFit(1112);
  
  TApplication* myApp = new TApplication("myApp", NULL, NULL);  
  TCanvas* myCanv = new TCanvas("myCanv","myCanv",0,0,700,500);
  TH1D* myHisto = new TH1D("myHisto","myHisto",nBins,xMin,xMax);

  TF1* myFun = new TF1("myFun",myGauss,0,10,3);
  myFun->SetParameter(0,1);
  myFun->SetParameter(1,mean);
  myFun->SetParameter(2,sigma);

  myFun->SetParName(0,"Ampl");
  myFun->SetParName(1,"Mean");
  myFun->SetParName(2,"Sigma");

  for (unsigned int i = 0; i < N; i++)
    {
      myHisto->Fill(rand_TAC_gaus(mean, sigma));
    }

  myCanv->cd();
  myHisto->Draw();
  myHisto->Fit("myFun");
  
  myCanv->Modified();
  myCanv->Update();

  std::cout << "Reduced Chi-2: ";
  std::cout << myFun->GetChisquare()/myFun->GetNDF() << std::endl;
  std::cout << "p-value: " << myFun->GetProb() << std::endl;
  std::cout << "Number of entries: ";
  std::cout << nBins / (xMax - xMin) * myFun->Integral(xMin, xMax);
  std::cout << std::endl;
  
  myApp->Run();
  return 0;
}
