#ifndef MATRIX2D_h
#define MATRIX2D_h

#include <iostream>
using namespace std;

//tipo di dato assumibile dagli elementi della matrice, dagli scalari per cui si può moltiplicare la matrice
template<class T>

class matrix2D
{
public:
	matrix2D() {
		m11_p=0;
		m12_p=0;
		m21_p=0;
		m22_p=0;
	}; // Default constructor
	matrix2D(T m11, T m12, T m21, T m22) :
	  m11_p(m11), m12_p(m12), m21_p(m21), m22_p(m22) {}; // Constructor

	// Operazione di assegnazione tra matrici
	matrix2D& operator=(const matrix2D& original){
		m11_p=original.m11_p;
		m12_p=original.m12_p;
		m21_p=original.m21_p;
		m22_p=original.m22_p;
		return *this;
	}
	// Operazione di addizione tra matrici
	matrix2D  operator+(const matrix2D& original){
		matrix2D Sum(original);
		Sum.m11_p+=m11_p;
		Sum.m12_p+=m12_p;
		Sum.m21_p+=m21_p;
		Sum.m22_p+=m22_p;
		return Sum;
	}
	// Operazione di sottrazione tra matrici
	matrix2D  operator-(const matrix2D& original){
		matrix2D Sub;
		Sub.m11_p=m11_p-original.m11_p;
		Sub.m12_p=m12_p-original.m12_p;
		Sub.m21_p=m21_p-original.m21_p;
		Sub.m22_p=m22_p-original.m22_p;
		return Sub;
	}
	// Operazione di prodotto tra matrici
	matrix2D  operator*(const matrix2D& original){
		matrix2D Prod;
		Prod.m11_p=m11_p*original.m11_p+m12_p*original.m21_p;
		Prod.m12_p=m11_p*original.m12_p+m12_p*original.m22_p;
		Prod.m21_p=m21_p*original.m11_p+m22_p*original.m21_p;
		Prod.m22_p=m21_p*original.m12_p+m22_p*original.m22_p;
		return Prod;
	}
	// Operazione di prodotto per uno scalare, lo scalare deve essere dello stesso tipo degli elementi della matrice
	matrix2D  operator*(const T val){
		matrix2D Scal;
		Scal.m11_p=m11_p*val;
		Scal.m12_p=m12_p*val;
		Scal.m21_p=m21_p*val;
		Scal.m22_p=m22_p*val;
		return Scal;
	}
	// Operazione di divisione per uno scalare, lo scalare deve essere dello stesso tipo degli elementi della matrice
	matrix2D operator/(const T val){
		matrix2D Div;
		Div.m11_p=m11_p/val;
		Div.m12_p=m12_p/val;
		Div.m21_p=m21_p/val;
		Div.m22_p=m22_p/val;
		return Div;
	}
	    
	matrix2D inv(){
		matrix2D inversa(m22_p,-m12_p,-m21_p,m11_p);
		return inversa/(this->det());
	}
	T det(){
		return m11_p*m22_p-m12_p*m21_p;
	}
	void print(){
		cout <<"*******\n"<<m11_p<<" "<<m12_p<<"\n"<<m21_p<<" "<<m22_p<<endl;
	}
    
private:
	//uso T come tipo per gli elementi della matrice
  	T m11_p, m12_p, m21_p, m22_p;
};
#endif
