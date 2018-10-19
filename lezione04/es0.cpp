//terzo.cpp

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "lib.h"
#include <TCanvas.h>
#include <TH1F.h>


double f_sin(double x){
	return 1.+sin(x);
}

bool HitMiss(double xMin, double xMax, double yMin, double yMax){
	double x=0., y=0.;
	x=rand_range(xMin, xMax);
	y=rand_range(yMin, yMax);
	if(y<f_sin(x)) return true;
	else return false;
}
int main(){
	srand(time(NULL));
	double max= 10., min=0.;
	int M=10000, N=1000;
	double numero_casuale=0.;

	TH1F pdf ("name", "title", 100, min, max);
	for (int i = 0; i< N;i++){
		for(int  j=0;j<M;j++){
			numero_casuale+=rand_range(min, max);
		}
		numero_casuale/=M;
		std::cout << "Numero casuale: " << numero_casuale << std::endl;
		pdf.Fill(numero_casuale);
	}
	TCanvas cnv;
	pdf.Draw();
	pdf.Fit("gaus");
	cnv.Print("istogramma.png","png");
	return 0;
}
