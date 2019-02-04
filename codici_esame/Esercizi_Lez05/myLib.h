#ifndef MYLIB_H
#define MYLIB_H

bool   HitMiss       (double xMin, double xMax, double yMin, double yMax);
double fsin          (double x);
double fgaus         (double x, double mu, double sigma);
double rand_TAC_gaus (double mu, double sigma);
bool   HitMiss_Gaus  (double xMin, double xMax, double yMin, double yMax);
double Crude_MC_gaus (double xMin, double xMax);

double rand_range    (double min, double max);
double rand_TAC      (double xMin, double xMax, double yMin, double yMax);
double fCauchy       (double x);
double rand_FCI_Exp  (double mu);

double rand_CLT      (double xMin, double xMax, int tries);

// ###############################################
// # Linear Congruential Generator               #
// # for the generation of pseudo-random numbers #
// ###############################################
#define M 2147483647
#define A 214013
#define C 2531011
long int genLinCong (long int Xn);

#endif