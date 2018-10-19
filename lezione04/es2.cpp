//es.cpp

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "lib.h"
#include <TCanvas.h>
#include <TH1F.h>

double f_gaus(double x){
	double x0=5.;
	double sigma=1;
	return exp(-pow(x-x0,2)/(2*pow(sigma,2)))/(sqrt(2*M_PI*pow(sigma,2)));
}
double HitMiss(double xMin, double xMax, double yMin, double yMax){
	double x=0., y=0.;
        do{
	       x=rand_range(xMin, xMax);
	       y=rand_range(yMin, yMax);
       }while(y>f_gaus(x));
       return x;
}
//std dev va come 1/sqrt(M)
int main(){
        srand(time(NULL));
	double max= 10., min=0.;
	int M=100, N=1000;
	double numero_casuale=0.;
	double med;
	double var;
	TH1F pdf ("name", "title", 100, min, max);
	for (int i = 0; i< N;i++){
		for(int  j=0;j<M;j++){
			numero_casuale+=HitMiss(min, max,0.,1/sqrt(2*M_PI*pow(1,2)));
		}
		numero_casuale/=M;
		med+=numero_casuale;
		var+=numero_casuale*numero_casuale;
		std::cout << "Numero casuale: " << numero_casuale << std::endl;
		pdf.Fill(numero_casuale);
	}
	med/=N;
	var=var/N-med*med;
	std::cout << "La media è " <<med<<"\nMentre la varianza "<<var<<"\n";
	TCanvas cnv;
	pdf.Draw();
	cnv.Print("istogramma2.png","png");
	return 0;
}
