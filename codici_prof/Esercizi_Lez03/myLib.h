#ifndef MYLIB_H
#define MYLIB_H

double rand_range   (double min, double max);
double rand_TAC     (double xMin, double xMax, double yMin, double yMax);
double fCauchy      (double x);
double rand_FCI_Exp (double mu);

// ###############################################
// # Linear Congruential Generator               #
// # for the generation of pseudo-random numbers #
// ###############################################
#define M 2147483647
#define A 214013
#define C 2531011
long int genLinCong (long int Xn);

#endif
