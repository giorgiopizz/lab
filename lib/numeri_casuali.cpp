//c++ numeri_casuali.cpp lib.cc -o numeri_casuali
#include "lib.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(){
	srand(time(NULL));
	double min=0;
	double max=10;
	int nEstrazioni=1000;
	int N=10000;
	ofstream myfile;
 	myfile.open("data4.txt");

	for (int i = 0; i< N;i++){
		double numero_casuale = rand_CLT(min, max, nEstrazioni);
		std::cout << "Numero casuale: " << numero_casuale << std::endl;
		myfile << numero_casuale<<"\n";
	}
	myfile.close();

	return 0;
}
