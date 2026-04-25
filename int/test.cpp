#include <gtest/gtest.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "int.hpp"

constexpr int epsilon = 1e-6;

typedef std::pair<double (*)(double), double (*)(double)> functionsPair;

class RootTest : public ::testing::TestWithParam<functionsPair> {};

int mod(int x) {
    return (x > 0 ? x : -x);
}

double f1(double x) { return x*x*x*x - 16*x - 64; }
double F1(double x) { return x*x*x*x*x/5 - 8*x*x - 64*x; }

void test(double (*f)(double), double (*F)(double)) {
    double root = integral_sympson(f, 0, 1);
    double actual_root = F(1) - F(0);
    double diff = mod(actual_root - root);

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
        functionsPair(f1, F1)
    )
);
