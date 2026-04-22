#include <gtest/gtest.h>
#include <iostream>
#include <iomanip>
#include "lib.hpp"

class RootTest : public ::testing::TestWithParam<double(*)(double)> {};

double f1(double x) { return x*x*x*x - 16*x - 64; }
double f2(double x) { return x*x*x*x - 4*x - 16; }

void test(double (*f)(double)) {
    double root = getRoot(f);
    double value = f(root);

    ASSERT_TRUE(value >= -2 * epsilon && value <= 2 * epsilon);

    std::cout << root << ": " << value << "\n";
}

TEST_P(RootTest, FindsRoot) {
    auto f = GetParam();

    std::cout << std::fixed << std::setprecision(8);

    test(f);
}

// List of functions to test
INSTANTIATE_TEST_SUITE_P(
    FunctionTests,
    RootTest,
    ::testing::Values(f1, f2)
);