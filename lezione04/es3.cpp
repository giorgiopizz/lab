//es3.cpp

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "lib.h"
#include <TCanvas.h>
#include <TH1F.h>

double f_gaus(double x,double sigma){
	double x0=5.;
	return exp(-pow(x-x0,2)/(2*pow(sigma,2)))/(sqrt(2*M_PI*pow(sigma,2)));
}
double HitMiss(double xMin, double xMax, double yMin, double yMax,double sigma){
	double x=0., y=0.;
        do{
	       x=rand_range(xMin, xMax);
	       y=rand_range(yMin, yMax);
       }while(y>f_gaus(x,sigma));
       return x;
}
//std dev va come 1/sqrt(M)
int main(){
        srand(time(NULL));
	double max= 10., min=0.;
	int N=1000;
	double numero_casuale=0.;
	double sigma=0.5;
	TH1F pdf ("name", "title", 100, min, max);
	for (int i = 0; i< N;i++){
			numero_casuale=HitMiss(min, max,0.,1/sqrt(2*M_PI*pow(sigma,2)),sigma);
			std::cout << "Numero casuale: " << numero_casuale << std::endl;
			pdf.Fill(numero_casuale);
	}
	sigma=2;
	for (int i = 0; i< N;i++){
			numero_casuale=HitMiss(min, max,0.,1/sqrt(2*M_PI*pow(sigma,2)),sigma);
			std::cout << "Numero casuale: " << numero_casuale << std::endl;
			pdf.Fill(numero_casuale);
	}

	TCanvas cnv;
	pdf.Draw();
	cnv.Print("istogramma3.png","png");
	return 0;
}
