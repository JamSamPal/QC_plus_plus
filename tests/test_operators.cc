// test_operators.cc
#include "../src/Codes.hpp"
#include "../src/Operators.hpp"
#include "../src/Qubit.hpp"
#include <gtest/gtest.h>

TEST(OperatorTest, Pauli_X) {
    QubitState q(3);
    std::complex<double> alpha(0.0, 1.0);
    std::complex<double> beta(1.0, 1.0);
    q.state[0] = alpha;
    q.state[7] = beta;

    // Flip the leftmost bit taking
    // alpha |000> + beta |111> to
    // alpha |100> + beta |011>
    PauliX X;
    X.ApplyX(q, 0, 3);
    // Previous state should now be zero
    EXPECT_DOUBLE_EQ(q.state[0].real(), 0.0);
    EXPECT_DOUBLE_EQ(q.state[0].imag(), 0.0);
    EXPECT_DOUBLE_EQ(q.state[7].real(), 0.0);
    EXPECT_DOUBLE_EQ(q.state[7].imag(), 0.0);

    // New state should equal alpha, beta
    EXPECT_DOUBLE_EQ(q.state[4].real(), alpha.real());
    EXPECT_DOUBLE_EQ(q.state[4].imag(), alpha.imag());
    EXPECT_DOUBLE_EQ(q.state[3].real(), beta.real());
    EXPECT_DOUBLE_EQ(q.state[3].imag(), beta.imag());
}

TEST(OperatorTest, Pauli_Z) {
    QubitState q(3);
    std::complex<double> alpha(0.0, 1.0);
    std::complex<double> beta(1.0, 1.0);
    // Construct a state of
    // alpha |000> + beta |100>
    q.state[0] = alpha;
    q.state[4] = beta;

    // Pauli Z_0 should take this state to
    // alpha |000> - beta |100>
    PauliZ Z;
    Z.ApplyZ(q, 0, 3);
    EXPECT_DOUBLE_EQ(q.currentEigenvalues[0], 1.0);
    EXPECT_DOUBLE_EQ(q.currentEigenvalues[4], -1.0);
}