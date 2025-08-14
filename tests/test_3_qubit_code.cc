// test_3_qubit.cc
#include "../src/Codes.hpp"
#include "../src/Operators.hpp"
#include "../src/Qubit.hpp"
#include <gtest/gtest.h>

TEST(Qubit3CodeTest, Encode) {
    ThreeQubitCode TQC;
    std::complex<double> alpha(1.0, 1.0);
    std::complex<double> beta(1.0, 1.0);
    TQC.EncodeLogical(alpha, beta);

    EXPECT_DOUBLE_EQ(TQC.state.state[0].real(), alpha.real());
    EXPECT_DOUBLE_EQ(TQC.state.state[0].imag(), alpha.imag());

    EXPECT_DOUBLE_EQ(TQC.state.state[7].real(), beta.real());
    EXPECT_DOUBLE_EQ(TQC.state.state[7].imag(), beta.imag());
}

TEST(Qubit3CodeTest, MeasureSyndrome) {

    ThreeQubitCode TQC;
    std::complex<double> alpha(1.0, 1.0);
    std::complex<double> beta(1.0, 1.0);
    TQC.EncodeLogical(alpha, beta);

    // Flip the leftmost bit taking
    // alpha |000> + beta |111> to
    // alpha |100> + beta |011>
    PauliX X;
    X.ApplyX(TQC.state, 0);

    // Find syndromes
    TQC.MeasureSyndrome();
    EXPECT_EQ(TQC.syndrome1, 1);
    EXPECT_EQ(TQC.syndrome2, 0);
}

TEST(Qubit3CodeTest, Decode) {

    ThreeQubitCode TQC;
    std::complex<double> alpha(1.0, 1.0);
    std::complex<double> beta(1.0, 1.0);
    TQC.EncodeLogical(alpha, beta);

    // Flip the leftmost bit taking
    // alpha |000> + beta |111> to
    // alpha |100> + beta |011>
    PauliX X;
    X.ApplyX(TQC.state, 0);

    // Find syndromes
    TQC.MeasureSyndrome();
    TQC.Decode();
    EXPECT_EQ(TQC.errorIndex, 0);
}

TEST(Qubit3CodeTest, ApplySyndrome) {

    ThreeQubitCode TQC;
    std::complex<double> alpha(1.0, 1.0);
    std::complex<double> beta(1.0, 1.0);
    TQC.EncodeLogical(alpha, beta);

    // Flip the leftmost bit taking
    // alpha |000> + beta |111> to
    // alpha |100> + beta |011>
    PauliX X;
    X.ApplyX(TQC.state, 0);

    // Find syndromes
    TQC.MeasureSyndrome();
    TQC.Decode();
    TQC.ApplySyndrome();

    // Should be returned to old state
    EXPECT_DOUBLE_EQ(TQC.state.state[0].real(), alpha.real());
    EXPECT_DOUBLE_EQ(TQC.state.state[0].imag(), alpha.imag());
    EXPECT_DOUBLE_EQ(TQC.state.state[7].real(), beta.real());
    EXPECT_DOUBLE_EQ(TQC.state.state[7].imag(), beta.imag());
}