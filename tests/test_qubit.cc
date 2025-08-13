// test_qubit.cc
#include "../src/Qubit.hpp"
#include <gtest/gtest.h>

TEST(QubitTest, DefaultConstructor) {
    Qubit q;
    EXPECT_DOUBLE_EQ(q.alpha, 1.0);
    EXPECT_DOUBLE_EQ(q.beta, 0.0);
}

TEST(QubitTest, ParameterConstructor) {
    Qubit q(0.0, 1.0);
    EXPECT_DOUBLE_EQ(q.alpha, 0.0);
    EXPECT_DOUBLE_EQ(q.beta, 1.0);
}