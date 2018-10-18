//quarto.cpp
#include "lib.h"
#include <iostream>
#include <TCanvas.h>
#include <TH1F.h>

int main(){
	srand(time(NULL));
	double min=-5;
	double max=5;
	int nEstrazioni=10;
	int N=10000;

	TH1F pdf ("name", "title", 100, min, max);
	for (int i = 0; i< N;i++){
		double numero_casuale = rand_TAC(min, max, 0., 1/M_PI);
		std::cout << "Numero casuale: " << numero_casuale << std::endl;
		pdf.Fill(numero_casuale);
	}
	TCanvas cnv;
	pdf.Draw();
	pdf.Fit("gaus");
	cnv.Print("istogramma.png","png");
	
	return 0;
}
