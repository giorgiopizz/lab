#include <cstdlib>
#include <ctime>
#include <TH1F.h>
#include <TCanvas.h>
#include <iostream>
using namespace std;
double rand_range(double min, double max){
	return min+(max-min)*rand()/(1. * RAND_MAX);
}

int main(){
	int N=10000;
	double mu, sigma,sig;
	double x;
	TH1F isto("Legenda", "Titolo", 100, 0, 10);
	for(int i=0; i<N;i++){
		x=rand_range(0,10);
		isto.Fill(x);
		mu+=x;
		sig+=x*x;
	}
	sig/=N;
	mu/=N;
	sigma=sig-pow((mu),2);
	cout << "La media è: " << mu <<"\nLa deviazione standard: "<<sigma<<endl;
	TCanvas cnv;
	isto.Draw();
	cnv.Print("isto.png","png");
}
	
