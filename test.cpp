#include <gtest/gtest.h>
#include "lib.hpp"

double f(double x) {
    return x*x*x*x - 16*x - 64;
}

TEST(AdditionTest, HandlesPositiveNumbers) {
    double root = getRoot(f);
    double value = f(root);

    ASSERT_TRUE(value >= -2 * epsilon && value <= 2 * epsilon);
}