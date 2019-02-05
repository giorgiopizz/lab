#ifndef MATRIX2D_h
#define MATRIX2D_h

#include <iostream>

class matrix2D
{
public:
  matrix2D() {
	m11_p=0;
	m12_p=0;
	m21_p=0;
	m22_p=0;
}; // Default constructor
  matrix2D(double m11, double m12, double m21, double m22) :
    m11_p(m11), m12_p(m12), m21_p(m21), m22_p(m22) {}; // Constructor
    
  // Operazione di assegnazione tra matrici
  matrix2D& operator=(const matrix2D& original);
  // Operazione di addizione tra matrici
  matrix2D  operator+(const matrix2D& original);
  // Operazione di sottrazione tra matrici
  matrix2D  operator-(const matrix2D& original);
  // Operazione di prodotto tra matrici
  matrix2D  operator*(const matrix2D& original);
  // Operazione di prodotto per uno scalare
  matrix2D  operator*(const double val);
  // Operazione di divisione per uno scalare
  matrix2D  operator/(const double val);
    
  matrix2D inv(); // Calcolo dell'inversa della matrice
  double det();   // Calcolo del determinante della matrice
  void print();   // Stampa a schermo i 4 elemeti della matrice
    
private:
  double m11_p, m12_p, m21_p, m22_p;
};
#endif
