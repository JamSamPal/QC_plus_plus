// test_3_qubit.cc
#include "../src/Codes.hpp"
#include "../src/Operators.hpp"
#include "../src/Qubit.hpp"
#include <gtest/gtest.h>

TEST(Qubit3CodeTestBF, Encode) {
    ThreeQubitCode TQC(CodeMode::BitFlip);
    std::complex<double> alpha(1.0, 1.0);
    std::complex<double> beta(1.0, 1.0);
    TQC.EncodeLogical(alpha, beta);

    EXPECT_DOUBLE_EQ(TQC.state.state[0].real(), alpha.real());
    EXPECT_DOUBLE_EQ(TQC.state.state[0].imag(), alpha.imag());

    EXPECT_DOUBLE_EQ(TQC.state.state[7].real(), beta.real());
    EXPECT_DOUBLE_EQ(TQC.state.state[7].imag(), beta.imag());
}

TEST(Qubit3CodeTestBF, MeasureSyndrome) {

    ThreeQubitCode TQC(CodeMode::BitFlip);
    std::complex<double> alpha(1.0, 1.0);
    std::complex<double> beta(1.0, 1.0);
    TQC.EncodeLogical(alpha, beta);

    // Flip the leftmost bit taking
    // alpha |000> + beta |111> to
    // alpha |100> + beta |011>
    PauliX X;
    X.ApplyX(TQC.state, 0, 3);

    // Find syndromes
    TQC.MeasureSyndrome();
    EXPECT_EQ(TQC.syndrome1, 1);
    EXPECT_EQ(TQC.syndrome2, 0);
}

TEST(Qubit3CodeTestBF, Decode) {

    ThreeQubitCode TQC(CodeMode::BitFlip);
    std::complex<double> alpha(1.0, 1.0);
    std::complex<double> beta(1.0, 1.0);
    TQC.EncodeLogical(alpha, beta);

    // Flip the leftmost bit taking
    // alpha |000> + beta |111> to
    // alpha |100> + beta |011>
    PauliX X;
    X.ApplyX(TQC.state, 0, 3);

    // Find syndromes
    TQC.MeasureSyndrome();
    TQC.Decode();
    EXPECT_EQ(TQC.errorIndex, 0);
}

TEST(Qubit3CodeTestBF, ApplySyndrome) {

    ThreeQubitCode TQC(CodeMode::BitFlip);
    std::complex<double> alpha(1.0, 1.0);
    std::complex<double> beta(1.0, 1.0);
    TQC.EncodeLogical(alpha, beta);

    // Flip the leftmost bit taking
    // alpha |000> + beta |111> to
    // alpha |100> + beta |011>
    PauliX X;
    X.ApplyX(TQC.state, 0, 3);

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

TEST(Qubit3CodeTestPF, Encode) {
    ThreeQubitCode TQC(CodeMode::PhaseFlip);
    std::complex<double> alpha(1.0, 1.0);
    std::complex<double> beta(1.0, 1.0);
    TQC.EncodeLogical(alpha, beta);

    // Expected: alpha|+++\rangle + beta|---\rangle
    // We'll just check two amplitudes explicitly for sanity:
    // |000> amplitude = (alpha + beta) / sqrt(8)
    // |111> amplitude = (alpha - beta) / sqrt(8)
    double invSqrt8 = 1.0 / std::sqrt(8.0);
    std::complex<double> expected000 = (alpha + beta) * invSqrt8;
    std::complex<double> expected111 = (alpha - beta) * invSqrt8;

    EXPECT_DOUBLE_EQ(TQC.state.state[0].real(), expected000.real());
    EXPECT_DOUBLE_EQ(TQC.state.state[0].imag(), expected000.imag());
    EXPECT_DOUBLE_EQ(TQC.state.state[7].real(), expected111.real());
    EXPECT_DOUBLE_EQ(TQC.state.state[7].imag(), expected111.imag());
}

TEST(Qubit3CodeTestPF, MeasureSyndrome) {
    ThreeQubitCode TQC(CodeMode::PhaseFlip);
    std::complex<double> alpha(1.0, 1.0);
    std::complex<double> beta(1.0, 1.0);
    TQC.EncodeLogical(alpha, beta);

    // Apply a phase flip (Z) to the leftmost qubit
    PauliZ Z;
    Z.ApplyZ(TQC.state, 0, 3);

    // Find syndromes (now measuring X-basis parities)
    TQC.MeasureSyndrome();
    EXPECT_EQ(TQC.syndrome1, 1);
    EXPECT_EQ(TQC.syndrome2, 0);
}

TEST(Qubit3CodeTestPF, Decode) {
    ThreeQubitCode TQC(CodeMode::PhaseFlip);
    std::complex<double> alpha(1.0, 1.0);
    std::complex<double> beta(1.0, 1.0);
    TQC.EncodeLogical(alpha, beta);

    // Apply a phase flip (Z) to the leftmost qubit
    PauliZ Z;
    Z.ApplyZ(TQC.state, 0, 3);

    // Find syndromes
    TQC.MeasureSyndrome();
    TQC.Decode();
    EXPECT_EQ(TQC.errorIndex, 0); // should identify qubit 0
}

TEST(Qubit3CodeTestPF, ApplySyndrome) {
    ThreeQubitCode TQC(CodeMode::PhaseFlip);
    std::complex<double> alpha(1.0, 1.0);
    std::complex<double> beta(1.0, 1.0);
    TQC.EncodeLogical(alpha, beta);

    // Apply a phase flip (Z) to the leftmost qubit
    PauliZ Z;
    Z.ApplyZ(TQC.state, 0, 3);

    // Find and correct error
    TQC.MeasureSyndrome();
    TQC.Decode();
    TQC.ApplySyndrome();

    // Should be returned to original |000> and |111> amplitudes
    EXPECT_DOUBLE_EQ(TQC.state.state[0].real(), alpha.real());
    EXPECT_DOUBLE_EQ(TQC.state.state[0].imag(), alpha.imag());
    EXPECT_DOUBLE_EQ(TQC.state.state[7].real(), beta.real());
    EXPECT_DOUBLE_EQ(TQC.state.state[7].imag(), beta.imag());
}