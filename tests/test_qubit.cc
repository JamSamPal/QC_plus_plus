// test_qubit.cc
#include "../src/Qubit.hpp"
#include <complex>
#include <gtest/gtest.h>

TEST(QubitTest, Constructor) {
    QubitState q(3);
    std::complex<double> alpha(0.0, 1.0);
    std::complex<double> beta(1.0, 1.0);
    q.state[0] = alpha;
    q.state[7] = beta;

    EXPECT_DOUBLE_EQ(q.state[0].real(), alpha.real());
    EXPECT_DOUBLE_EQ(q.state[0].imag(), alpha.imag());
    EXPECT_DOUBLE_EQ(q.state[7].real(), beta.real());
    EXPECT_DOUBLE_EQ(q.state[7].imag(), beta.imag());
}