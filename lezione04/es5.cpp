//es5.cpp

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "lib.h"


double f_gaus(double x,double sigma){
	double x0=0;
	return exp(-pow(x-x0,2)/(2*pow(sigma,2)))/(sqrt(2*M_PI*pow(sigma,2)));
}
bool HitMiss(double xMin, double xMax, double yMin, double yMax,double sigma){
	double x=0., y=0.;

	x=rand_range(xMin, xMax);
	y=rand_range(yMin, yMax);
	//std::cout << x <<"	"<<y<<"\n";
	if(y<f_gaus(x,sigma)) return true;
	else return false;

}
int main(){
        srand(time(NULL));
	double max= 10., min=0.;
	//stimo l'integrale
	int N=100000;
	int nHit=0;
	double xMin = -5, xMax = 3.49;
  	double yMin = 0., yMax = 1/sqrt(2*M_PI*pow(1,2));
	for(int i=0;i<N;i++){
		if(HitMiss(xMin, xMax, yMin,yMax, 1)==true){
			nHit++;
		}
	}
	double Area= (xMax-xMin)*(yMax-yMin);
	double Integral = nHit*Area/(double)N;
	double p= nHit/(double)N;
	double Var= Area*Area/(double)N * p * (1.-p);
	double StdDev= sqrt(Var);
	std::cout<< Integral<<std::endl;
}
