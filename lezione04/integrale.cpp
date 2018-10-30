//integrale per analisi

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "lib.h"
using namespace std;

double f_gaus(double x){
	cout << acos(x)<<endl;
	return acos(x);
}
bool HitMiss(double xMin, double xMax, double yMin, double yMax){
	double x=0., y=0.;

	x=rand_range(xMin, xMax);
	y=rand_range(yMin, yMax);
	//std::cout << x <<"	"<<y<<"\n";
	if(y<f_gaus(x)) return true;
	else return false;
}
int main(){
	srand(time(NULL));
	double max= 10., min=0.;
	//stimo l'integrale
	int N=100000;
	int nHit=0;
	double xMin = -1, xMax = 1;
	double yMin = 0., yMax = M_PI;
	for(int i=0;i<N;i++){
		if(HitMiss(xMin, xMax, yMin,yMax)==true){
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
