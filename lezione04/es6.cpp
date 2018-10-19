#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "lib.h"
double f_gaus(double x){
	double x0=0;
	double sigma=1;
	return exp(-pow(x-x0,2)/(2*pow(sigma,2)))/(sqrt(2*M_PI*pow(sigma,2)));
}
double rand(double a, double b){
        double x;
        x=rand_range(a,b);
        return f_gaus(x);
}

int main(){
        srand(time(NULL));
	//stimo l'integrale
	int N=100000;
        double x;
        double a=-5, b=1;
        double med=0, var=0;
        double y;
        for(int i=0;i<N;i++){
                y=rand(a,b);
                //std::cout <<y<<"\n";
                med+=y;
                var+=y*y;
        }
        med/=N;
        var=var/N-med*med;
        double Integral=(b-a)*(med);
        double StdDev=(b-a)*sqrt(var/N);
        std::cout << Integral<<"\n";
}
