// test_visualise_bloch.cc
#include "../src/Helpers.hpp"
#include "../src/Qubit.hpp"
#include <complex>
#include <gtest/gtest.h>

TEST(BlochTest, Draw) {
    QubitState q(1);
    double invSqrt2 = 1.0 / std::sqrt(2.0);
    std::complex<double> alpha(invSqrt2, 0.0);
    std::complex<double> beta(invSqrt2, 0.0);
    q.state[0] = alpha;
    q.state[1] = beta;

    BlochSphere BS;
    BlochVector BV = BS.GetBlochVector(q, 0);
    BS.DrawBlochSphere(BV);
}