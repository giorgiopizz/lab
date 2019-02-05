#include "matrix2D.h"
using namespace std;

// Operazione di assegnazione tra matrici
matrix2D& matrix2D::operator=(const matrix2D& original){
	m11_p=original.m11_p;
	m12_p=original.m12_p;
	m21_p=original.m21_p;
	m22_p=original.m22_p;
	return *this;
}
// Operazione di addizione tra matrici
matrix2D  matrix2D::operator+(const matrix2D& original){
	matrix2D Sum(original);
	Sum.m11_p+=m11_p;
	Sum.m12_p+=m12_p;
	Sum.m21_p+=m21_p;
	Sum.m22_p+=m22_p;
	return Sum;
}
// Operazione di sottrazione tra matrici
matrix2D  matrix2D::operator-(const matrix2D& original){
	matrix2D Sub;
	Sub.m11_p=m11_p-original.m11_p;
	Sub.m12_p=m12_p-original.m12_p;
	Sub.m21_p=m21_p-original.m21_p;
	Sub.m22_p=m22_p-original.m22_p;
	return Sub;
}
// Operazione di prodotto tra matrici
matrix2D  matrix2D::operator*(const matrix2D& original){
	matrix2D Prod;
	Prod.m11_p=m11_p*original.m11_p+m12_p*original.m21_p;
	Prod.m12_p=m11_p*original.m12_p+m12_p*original.m22_p;
	Prod.m21_p=m21_p*original.m11_p+m22_p*original.m21_p;
	Prod.m22_p=m21_p*original.m12_p+m22_p*original.m22_p;
	return Prod;
}
// Operazione di prodotto per uno scalare
matrix2D  matrix2D::operator*(const double val){
	matrix2D Scal;
	Scal.m11_p=m11_p*val;
	Scal.m12_p=m12_p*val;
	Scal.m21_p=m21_p*val;
	Scal.m22_p=m22_p*val;
	return Scal;
}
// Operazione di divisione per uno scalare
matrix2D  matrix2D::operator/(const double val){
	matrix2D Div;
	Div.m11_p=m11_p/val;
	Div.m12_p=m12_p/val;
	Div.m21_p=m21_p/val;
	Div.m22_p=m22_p/val;
	return Div;
}
// Calcolo della matrice inversa
matrix2D matrix2D::inv(){
	matrix2D inversa(m22_p,-m12_p,-m21_p,m11_p);
	return inversa/(this->det());
}
//Calcolo del determinante
double matrix2D::det(){
	return m11_p*m22_p-m12_p*m21_p;
}
//Stampa a schermo della matrice
void matrix2D::print(){
	cout <<"*******\n"<<m11_p<<" "<<m12_p<<"\n"<<m21_p<<" "<<m22_p<<endl;
}
