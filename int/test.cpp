#include <gtest/gtest.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "int.hpp"

constexpr double epsilon = 1e-4;

typedef std::pair<double (*)(double), double (*)(double)> functionsPair;

class RootTest : public ::testing::TestWithParam<functionsPair> {};

double f1(double x) { return x*x*x*x - 16*x - 64; }
double F1(double x) { return x*x*x*x*x/5 - 8*x*x - 64*x; }

double f2(double x) { return sin(x); }
double F2(double x) { return -cos(x); }

double f3(double x) { return sin(5*x) - 3*x*x; }
double F3(double x) { return -cos(5*x)/5 - x*x*x; }

double f4(double x) { return x*x*x - 16*x + 5; }
double F4(double x) { return x*x*x*x/4 - 8*x*x + 5*x; }

double f5(double x) { return -x*x+x; }
double F5(double x) { return -x*x*x/3+x*x/2; }

void test(double (*f)(double), double (*F)(double)) {
    double root = integral_trapezoid(f, 0, 1);
    double actual_root = F(1) - F(0);

    double diff = std::abs(actual_root - root);

    ASSERT_TRUE(diff <= epsilon);

    std::cout << root << " " << actual_root << "\n";
}

TEST_P(RootTest, FindsRoot) {
    auto funcs = GetParam();
    auto f = funcs.first;
    auto F = funcs.second;

    std::cout << std::fixed << std::setprecision(8);

    test(f, F);
}

INSTANTIATE_TEST_SUITE_P(
    FunctionTests,
    RootTest,
    ::testing::Values(
        functionsPair(f1, F1),
        functionsPair(f2, F2),
        functionsPair(f3, F3),
        functionsPair(f4, F4),
        functionsPair(f5, F5)
    )
);
