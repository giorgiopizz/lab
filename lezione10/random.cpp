//c++ numeri_casuali.cpp lib.cc -o numeri_casuali
#include "lib.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
double f_parabola(double x){
        double a,b,c;
	double c = a*pow(x,2)+b*x+c:;
	return c;
}
double rand_TAC(double xMin, double xMax, double yMin, double yMax){
	//usa il metodo try and catch
	double x=0., y=0.;
	do{
		x=rand_range(xMin,xMax);
		y=rand_range(yMin,yMax);
	} while(y>f_parabola(x));
	return x;
}
int main(){
	srand(time(NULL));
	double min=0;
	double max=100;
	int nEstrazioni=100;
	int N=100000;
	ofstream myfile;
 	myfile.open("data3.txt");

	for (int i = 0; i< N;i++){
		double numero_casuale = rand_CLT(min, max, nEstrazioni);
		std::cout << "Numero casuale: " << numero_casuale << std::endl;
		myfile << numero_casuale<<"\n";
	}
	for (int i = 0; i< N;i++){
		double numero_casuale = rand_FCI_Exp(10);
		std::cout << "Numero casuale: " << numero_casuale << std::endl;
		myfile << numero_casuale<<"\n";
	}
	myfile.close();

	return 0;
}
