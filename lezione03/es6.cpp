#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "lib.h"

double rand(){
        double x;
        x=rand_range(a,b);
        return f(x);
}

int main(){
        srand(time(NULL));
	//stimo l'integrale
	int N=100000;
        double x;
        double a=0, b=10;
        double med=0, var=0;
        for(int i=0;i<N;i++){
                y=rand();
                med+=y;
                var+=y*y;
        }
        med/N;
        var=var/N-med*med;
        double Integral=(b-a)*(med);
        double StdDev=(b-a)*sqrt(var/N);
}
