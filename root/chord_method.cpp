#include <iostream>
#include <vector>
#include <cmath>

// Chord method 

constexpr double epsilon = 1e-6;

// tools
int sgn(double x) {
    return (x >= 0 ? 1 : -1);
}

double mod(double x) {
    return (x >= 0 ? x : -x);
}

// get interval where is root
int getStartInterval(double (*f)(double)) {
    int start = 0;

    double y = f(start + 1);
    double prev_y = f(start);

    while (sgn(prev_y) + sgn(y) != 0) {
        start++;

        y = f(start + 1);
        prev_y = f(start);
    }

    return start;
}

double getRoot(double (*f)(double), int start) {
    int count = 0;

    double x0 = start;
    double x1 = x0 + 0.1;
    double x2;

    do {
        double f0 = f(x0);
        double f1 = f(x1);

        if (fabs(f1 - f0) < 1e-10) break;

        x2 = x1 - f1 * (x1 - x0) / (f1 - f0);

        // set prev
        x0 = x1;
        x1 = x2;

        count++;
    } while (fabs(x1 - x0) >= epsilon);

    std::cout << "Iterations count: " << count << "\n";

    return x1;
}

double getRoot(double (*f)(double)) {
    double root = getRoot(f, getStartInterval(f));
    return root;
}
