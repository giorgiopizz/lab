//es3.cpp
#include "lib.h"
#include <iostream>
#include <TCanvas.h>
#include <TH1F.h>

int main(){
	srand(time(NULL));
	double mu = 0.25;
	int N=10000;

	TH1F pdf ("name", "title", 100, 0, 3);
	for (int i = 0; i< N;i++){
		double numero_casuale = rand_FCI_Exp(mu);
		std::cout << "Numero casuale: " << numero_casuale << std::endl;
		pdf.Fill(numero_casuale);
	}
	TCanvas cnv;
	pdf.Draw();
	pdf.Fit("gaus");
	cnv.Print("istogramma.png","png");
	
	return 0;
}
