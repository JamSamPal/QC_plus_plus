// test_operators.cc
#include "../src/Codes.hpp"
#include "../src/Operators.hpp"
#include "../src/Qubit.hpp"
#include <gtest/gtest.h>

TEST(OperatorTest, Pauli_X) {
    Qubit q;
    EXPECT_DOUBLE_EQ(q.alpha, 1.0);
    EXPECT_DOUBLE_EQ(q.beta, 0.0);

    PauliX X;
    X.ApplyX(q);
    EXPECT_DOUBLE_EQ(q.alpha, 0.0);
    EXPECT_DOUBLE_EQ(q.beta, 1.0);
}

TEST(OperatorTest, Pauli_Z) {
    Qubit q_in(0.0, 1.0);

    PauliZ Z;
    Qubit q_out;
    q_out = Z.ApplyZ(q_in);
    EXPECT_DOUBLE_EQ(q_out.alpha, 0.0);
    EXPECT_DOUBLE_EQ(q_out.beta, -1.0);
}