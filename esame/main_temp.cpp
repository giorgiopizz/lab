/*
c++ main_temp.cpp -o main_temp
*/

#include "matrix2D_temp.h"
using namespace std;

int main(){
	//tipizzazione con gli int
	matrix2D<int> m1(1,2,3,4),m2(5,6,7,8);
	matrix2D<int> ris;
	cout << "Uso gli int:" << endl;
	ris=m1+m2;
	ris.print();
	ris=m1-m2;
	ris.print();
	ris=m1*m2;
	ris.print();
	ris=m1*3;
	ris.print();
	ris=m1.inv();
	ris.print();
	ris=m1*m1.inv();
	/*come si può notare il risultato non è la matrice identità, questo perché non sempre la matrice inversa appartiene
	allo stesso spazio di matrici della matrice di partenza. Presa una matrice definita su N, non è detto(e questo caso
	ne è la prova) che la sua inversa sia definita sullo stesso campo*/
	ris.print();
	std::cout << "Det:"<<m1.det()<<std::endl;
	//tipizzazione con i float
	matrix2D<float> M1(1,2,3,4),M2(5,6,7,8);
	matrix2D<float> Ris;
	cout << "Uso i float:" << endl;
	Ris=M1+M2;
	Ris.print();
	Ris=M1-M2;
	Ris.print();
	Ris=M1*M2;
	Ris.print();
	Ris=M1*3.14159265;
	Ris.print();
	Ris=M1.inv();
	Ris.print();
	Ris=M1*M1.inv();
	Ris.print();
	cout << "Det:"<<M1.det()<< endl;
}
