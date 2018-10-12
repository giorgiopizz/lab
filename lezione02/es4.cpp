#include <iostream>
#include <cmath>
bool solve2ndDegree(double * par, double * x);

bool solve2ndDegree(double * par, double * x){
	double delta = (*(par+1))*(*(par+1))-4*(*par)*(*(par+2));
	if(delta>=0){
		//trovo le soluzioni
		if(delta == 0){
			//x = new double(round((-*(par+1))/(2*(*par))));
			x[0] = (-*(par+1))/(2*(*par));
			x[1] = (-*(par+1))/(2*(*par));
			std::cout << *x;
		}
		else{
			//x = new double[2];
			x[0] = (-*(par+1)+sqrt(delta))/(2*(*par));
			x[1] = (-*(par+1)-sqrt(delta))/(2*(*par));
		}	
		return true;
	}
	else{
		return false;
	}
}
//funzione che restituisce il segno di un numero
char segno(double val){
	if(val>=0){
		return '+';
	}
	else{
		return '-';
	}
}
int main(){
	double * par = new double[3];
	double * x = new double[2];
	std::cout << "Inserire i coefficienti dell'equazione di secondo grado";
	for(int i=0;i<3;++i){	
		std::cin >> *(par+i);
	}
	if(solve2ndDegree(par, x)){
		//double n=sizeof(x[])/sizeof(double)
		std::cout << "\nSono state trovate  soluzioni\n";
		std::cout << "La prima soluzione è " << *x << "\nLa seconda è " <<*(x+1) << std::endl;
		std::cout << "La scomposizione è (x"<<segno(-*x)<<std::abs(*x)<<")(x"<<segno(-*(x+1))<<std::abs(*(x+1))<<")\n";
	}
	else{
		std::cout << "\nNon sono state trovate soluzioni\n";
	}
}
