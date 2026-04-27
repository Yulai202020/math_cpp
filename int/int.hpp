#include <iostream>

constexpr int slice_count = 10000;

double integral_method_trapezoid(double start, double (*f)(double), double dist);
double integral_method_avg(double start, double (*f)(double), double dist);
double integral_method_start(double start, double (*f)(double), double dist);
double integral_method_end(double start, double (*f)(double), double dist);

double integral(double (*f)(double), double start, double end, double (*integral_method)(double, double (*)(double), double));
double integral_trapezoid(double (*f)(double), double start, double end);
double integral_sympson(double (*f)(double), double start, double end);