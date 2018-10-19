//terzo.cpp

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "lib.h"
/*#include <TCanvas.h>
#include <TH1F.h>*/


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
	double xMin=0., xMax=2*M_PI;
	double yMin=0.,yMax=2.;
	int nHit=0;
	int N=100000;

	for(int i=0;i<N;i++){
		if(HitMiss(xMin, xMax, yMin, yMax)){
			nHit++;
		}
	}
	double Area = (xMax-xMin)*(yMax-yMin);
	double Integral	= Area*nHit/(double)N;
	double p= nHit/(double)N;
	double Var = Area*Area/(double) N * p * (1.-p);
	double StdDev = sqrt(Var);
	std::cout << "L'area è " << Area<<"\nL'integrale: " << Integral << "+-"<< StdDev << std::endl;
	return 0;
}
