//es1.cpp

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "lib.h"
#include <TCanvas.h>
#include <TH1F.h>





int main(){
	srand(time(NULL));
	double max= 10., min=0.;
	int M=10000, N=1000;
	double numero_casuale=0.;
	double med;
	double var;
	TH1F pdf ("name", "title", 100, min, max);
	for (int i = 0; i< N;i++){
		for(int  j=0;j<M;j++){
			numero_casuale+=rand_range(min, max);
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
	cnv.Print("istogramma.png","png");
	return 0;
}
