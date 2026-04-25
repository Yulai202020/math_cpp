#include <iostream>
#include <vector>
#include <cmath>

constexpr double epsilon = 1e-6;

// tools
int sgn(double x);
double mod(double x);
double derivative(double (*f)(double), double x);

// get interval where is root
int getStartInterval(double (*f)(double));

double getRoot(double (*f)(double), double start);
double getRoot(double (*f)(double));