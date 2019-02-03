#ifndef VETT2D_H
#define VETT2D_H

#include <iostream>
#include <cmath>

class vett2d
{
public:
  // Default ctor
  vett2d ();
  
  // Ctor
  vett2d (double x, double y);
  
  // Copy ctor
  vett2d (const vett2d &original);
	
  // Operators
  vett2d & operator= (const vett2d & original);
  vett2d operator+ (const vett2d & vec2);
  vett2d operator- (const vett2d & vec2);

  // Memeber functions
  vett2d scalar_prod (double k); // Moltiplicazione di un vettore per uno scalare
  double mod         ();         // Modulo del vettore
  void   print       ();
  void   norm        ();         // Metodo che rinormalizza il vettore a 1
  double getx        ();
  double gety        ();	

  // Data members
private:
  double x_p;
  double y_p;
};

#endif
