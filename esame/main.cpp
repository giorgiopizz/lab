/*
c++ main.cpp matrix2D.cc -o main
*/

#include "matrix2D.h"
using namespace std;
int main(){
	matrix2D m1(1,2,3,4),m2(5,6,7,8);
	matrix2D ris;
	//sommo
	ris=m1+m2;
	ris.print();
	//sottraggo
	ris=m1-m2;
	ris.print();
	//moltiplico due matrici
	ris=m1*m2;
	ris.print();
	//moltiplico per scalare
	ris=m1*3.14159265;
	ris.print();
	//calcolo la matrice inversa
	ris=m1.inv();
	ris.print();
	//moltiplico la prima matrice per la sua inversa
	ris=m1*m1.inv();
	ris.print();
	//calcolo il determinante della prima, anche se non richiesto
	cout << "Det:"<<m1.det()<< endl;
}
