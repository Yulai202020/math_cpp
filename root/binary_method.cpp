#include <iostream>
#include <vector>
#include <cmath>

// I call it binary method (simulary to binary search)

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

double getRoot(double (*f)(double), int start_p) {
    int count = 0;

    double start = start_p;
    double end = start_p+1;
    double mid = (start+end)/2;

    while (mod(f(mid)) < epsilon || mod(end - start) > epsilon) {
        if (mod(f(mid)) < epsilon) {
            return mid;
        } else if (sgn(f(mid)) + sgn(f(start)) == 0) {
            end = mid;
        } else {
            start = mid;
        }

        mid = (start+end)/2;
        count++;
    }

    mid = (start + end) / 2;

    std::cout << "Iterations count: " << count << "\n";

    return mid; // return updated mid
}

double getRoot(double (*f)(double)) {
    double root = getRoot(f, getStartInterval(f));
    return root;
}
