#include <iostream>
#include "int.hpp"

// linear
double integral_method_avg(double start, double (*f)(double), double dist) {
    return f(start + dist/2) * dist;
}

double integral_method_start(double start, double (*f)(double), double dist) {
    return f(start) * dist;
}

double integral_method_end(double start, double (*f)(double), double dist) {
    return f(start + dist) * dist;
}

// sub linear
double integral_method_trapezoid(double start, double (*f)(double), double dist) {
    return (f(start) + f(start + dist)) / 2.0 * dist;
}

// funcs
double integral(double (*f)(double), double start, double end, double (*integral_method)(double, double (*)(double), double)) {
    double eps = (end-start)/slice_count;
    double root = 0;
    double x;

    for (int i = 0; i < slice_count; i ++) {
        x = start + i*eps;
        root += integral_method(x, f, eps);
    }

    return root;
}

double integral_trapezoid(double (*f)(double), double start, double end) {
    if (end < start) {
        return 0.0;
    }

    double root = integral(f, start, end, integral_method_trapezoid);

    return root;
}

// non linear
double integral_sympson(double (*f)(double), double start, double end) {
    double eps = (end-start)/slice_count;
    double root = 0;
    double k;

    for (int i = 1; i <= slice_count; i ++) {
        k = 2 + 2*(i % 2);
        root += k*f(start + i*eps);
    }

    root *= eps/3;

    return root;
}