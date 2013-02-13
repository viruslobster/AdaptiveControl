#ifndef MATH_H
#define MATH_H

#define PI 3.14159265358979323846
#include <cstdlib>  // For srand() and rand()
#include <cmath>

double randn_notrig(double mu = 0.0, double sigma = 1.0);
double randn_trig(double mu = 0.0, double sigma = 1.0);
double mapValues(double, double, double, double, double);

#endif // MATH_H
