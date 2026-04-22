#include <iostream>
#include <vector>
#include <cmath>

constexpr double epsilon = 1e-6;

// tools
int sgn(double x) {
    return (x >= 0 ? 1 : -1);
}

double mod(double x) {
    return (x >= 0 ? x : -x);
}

double derivative(double (*f)(double), double x) {
    return (f(x + epsilon) - f(x)) / epsilon;
}

// get all intervals
// std::vector<int> getAllStartingInterval(double (*f)(double)) {
// }
    
// get interval where is root
int getStartInterval(double (*f)(double)) {
    int start = 0;

    int y = f(start+1);
    int prev_y = f(start);

    while (sgn(prev_y) + sgn(y) != 0) {
        start++;

        y = f(start+1);
        prev_y = f(start);
    }

    return start;
}

double getRoot(double (*f)(double), int start) {
    int count = 0;

    double root = start;
    double prev;
    double d;

    do {
        prev = root;
        d = derivative(f, root);
        if (mod(d) < 1e-10) break;
        root = root - f(root)/d;

        count++;
    } while (mod(root - prev) >= epsilon);

    std::cout << "Iterations count: " << count << "\n";

    return root;
}

double getRoot(double (*f)(double)) {
    double root = getRoot(f, getStartInterval(f));
    return root;
}