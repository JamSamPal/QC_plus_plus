// test_visualise_bloch.cc
#include "../src/Helpers.hpp"
#include "../src/Qubit.hpp"
#include <complex>
#include <gtest/gtest.h>

TEST(BlochTest, Draw) {
    // Manually create a reduced density matrix
    // We choose a maximally entangled state
    DensityMatrix rDMManual(2);
    rDMManual.densityMatrix[0][0] = 0.5;
    rDMManual.densityMatrix[1][1] = 0.5;

    // Form the same reduced density matrix, starting from a state
    // (the Bell state) and forming the density matrix and then
    // forming the reduced density matrix on the first qubit.
    QubitState q(2);
    double invSqrt2 = 1.0 / std::sqrt(2.0);
    std::complex<double> alpha(invSqrt2, 0.0);
    std::complex<double> beta(invSqrt2, 0.0);
    q.state[0] = alpha;
    q.state[3] = beta;
    MatrixHelper M;
    DensityMatrix dMTest(4);
    DensityMatrix rDMTest(2);
    dMTest = M.GetDensityMatrix(q);
    rDMTest = M.GetReducedDensityMatrix(dMTest, 0, 2);

    // Check the dm is as expected
    EXPECT_DOUBLE_EQ(dMTest.densityMatrix[0][0].real(), 0.5);
    EXPECT_DOUBLE_EQ(dMTest.densityMatrix[0][3].real(), 0.5);
    EXPECT_DOUBLE_EQ(dMTest.densityMatrix[3][0].real(), 0.5);
    EXPECT_DOUBLE_EQ(dMTest.densityMatrix[3][3].real(), 0.5);

    // Check the two rdm's are the same
    EXPECT_DOUBLE_EQ(rDMManual.densityMatrix[0][0].real(), rDMTest.densityMatrix[0][0].real());
    EXPECT_DOUBLE_EQ(rDMManual.densityMatrix[0][1].real(), rDMTest.densityMatrix[0][1].real());
    EXPECT_DOUBLE_EQ(rDMManual.densityMatrix[1][0].real(), rDMTest.densityMatrix[1][0].real());
    EXPECT_DOUBLE_EQ(rDMManual.densityMatrix[1][1].real(), rDMTest.densityMatrix[1][1].real());

    // Confirm the plotting is correct
    // As this is the maximally entangled state it should lie
    // at the centre of the bloch sphere (the more mixed the
    // state the closer to the centre of the sphere it is, with
    // pure states lying on the surface)
    BlochSphere BS;
    BlochVector BVManual = BS.GetBlochVector(rDMManual);
    BS.DrawBlochSphere(BVManual);
    BlochVector BVTest = BS.GetBlochVector(rDMTest);
    BS.DrawBlochSphere(BVTest);
}