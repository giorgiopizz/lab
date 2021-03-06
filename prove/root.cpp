#include <iostream>
#include <cstdlib>
#include <ctime>
#include <TH1F.h>
#include <TCanvas.h>
#include <TApplication.h>

using namespace std;

double rand_range(double min, double max){
	return min +(max-min) *rand()/(1. * RAND_MAX);
}
double rand_CLT(double xMin, double xMax, int tries){
	double x= 0.;
	for(int i=0;i<tries;i++){
		x+=rand_range(xMin, xMax);
	}
	return x/tries;
}
int main(){
	double x;
	srand(time(NULL));
	TApplication * app = new TApplication("ciao", NULL,NULL);
	TCanvas * cnv = new TCanvas("myCanv","myCanv",0,0,700,500);
	TH1D * isto=new TH1D("il mio istogramma", "Isto", 100, 0 , 10);
	for(int i=0; i<10000;i++){
		x=rand_CLT(0, 10, 10);
		cout << x<< endl;
		isto->Fill(x);
	}
	cnv->cd();
  	isto->Draw();
  	isto->Fit("gaus");
  	cnv->Modified();
  	cnv->Update();
	
	app->Run();
}
