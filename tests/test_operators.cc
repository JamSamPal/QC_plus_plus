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
    EXPECT_DOUBLE_EQ(q.state[0].real(), alpha.real());
    EXPECT_DOUBLE_EQ(q.state[0].imag(), alpha.imag());
    EXPECT_DOUBLE_EQ(q.state[4].real(), -beta.real());
    EXPECT_DOUBLE_EQ(q.state[4].imag(), -beta.imag());
}

TEST(OperatorTest, Hadamard_Gate) {
    QubitState q(3);
    std::complex<double> alpha(0.0, 1.0);
    std::complex<double> beta(1.0, 1.0);

    // alpha |000> + beta |100>
    q.state[0] = alpha;
    q.state[4] = beta;

    // Apply Hadamard to qubit 0
    Hadamard H;
    H.ApplyH(q, 0, 3);

    // Expected transformation:
    // |000> → (|000> + |100>) / sqrt(2)
    // |100> → (|000> - |100>) / sqrt(2)
    //
    // So final state:
    // ((alpha + beta) / sqrt(2))|000>
    // ((alpha - beta) / sqrt(2))|100>

    double invSqrt2 = 1.0 / std::sqrt(2.0);
    std::complex<double> expected000 = (alpha + beta) * invSqrt2;
    std::complex<double> expected100 = (alpha - beta) * invSqrt2;

    EXPECT_DOUBLE_EQ(q.state[0].real(), expected000.real());
    EXPECT_DOUBLE_EQ(q.state[0].imag(), expected000.imag());
    EXPECT_DOUBLE_EQ(q.state[4].real(), expected100.real());
    EXPECT_DOUBLE_EQ(q.state[4].imag(), expected100.imag());
}

TEST(OperatorTest, CNOT_Gate) {
    QubitState q(2);
    std::complex<double> alpha(0.0, 1.0);
    std::complex<double> beta(1.0, 1.0);
    // Create state:
    // alpha |00> + beta |10>
    q.state[0] = alpha;
    q.state[2] = beta;

    // Apply CNOT gate from first to
    // second bit. This should take us
    // to state:
    // alpha |00> + beta |11>
    CNOT CN;
    CN.ApplyCN(q, 0, 1, 2);

    EXPECT_DOUBLE_EQ(q.state[0].real(), alpha.real());
    EXPECT_DOUBLE_EQ(q.state[0].imag(), alpha.imag());
    // Previous state should now be zero
    EXPECT_DOUBLE_EQ(q.state[2].real(), 0.0);
    EXPECT_DOUBLE_EQ(q.state[2].imag(), 0.0);

    // New state should equal beta
    EXPECT_DOUBLE_EQ(q.state[3].real(), beta.real());
    EXPECT_DOUBLE_EQ(q.state[3].imag(), beta.imag());
}