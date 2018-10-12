#include "classe.h"
#include <iostream>
#include <cmath>

complesso::complesso(double reale, double ima){
	real=reale;
	imm=ima;
}
complesso::~complesso(){
	std::cout<< "Ho distrutto l'oggetto\n";
}
double complesso::modulo(){
	return sqrt(pow(real,2)+pow(imm,2));
}
