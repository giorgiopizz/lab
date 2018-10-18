//es4.cpp
#include "lib.h"
#include <iostream>
#include <TCanvas.h>
#include <TH1F.h>

double casuali_medi(int n, double mu){
	double sum=0;
	for(int i = 0; i<n;i++){
		sum+=rand_FCI_Exp(mu);
	}
	return sum/(n*1.);
}

void grafico(int n){
	srand(time(NULL));
	double mu = 0.25;
	int N=10000;
	TH1F pdf ("name", "title", 100, 0, 1);
	for (int i = 0; i< N;i++){
		double numero_casuale = casuali_medi(n,mu);
		std::cout << "Numero casuale: " << numero_casuale << std::endl;
		pdf.Fill(numero_casuale);
	}
	TCanvas cnv;
	pdf.Draw();
	cnv.Print("n50.png","png");
}

int main(){

	int n;
	std::cout << "Inserisci il quanti numeri casuali estrarre: ";
	std::cin >> n;
	grafico(n);
	return 0;
}
