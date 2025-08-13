// test_3_qubit.cc
#include "../src/Codes.hpp"
#include "../src/Operators.hpp"
#include "../src/Qubit.hpp"
#include <gtest/gtest.h>

TEST(Qubit3CodeTest, Logical0Qubit) {
    int logical_bit = 0;
    ThreeQubitCode TQC;
    TQC.EncodeLogical(logical_bit);

    EXPECT_DOUBLE_EQ(TQC.state[0].alpha, 1.0);
    EXPECT_DOUBLE_EQ(TQC.state[0].beta, 0.0);

    EXPECT_DOUBLE_EQ(TQC.state[1].alpha, 1.0);
    EXPECT_DOUBLE_EQ(TQC.state[1].beta, 0.0);

    EXPECT_DOUBLE_EQ(TQC.state[2].alpha, 1.0);
    EXPECT_DOUBLE_EQ(TQC.state[2].beta, 0.0);
}

TEST(Qubit3CodeTest, Logical1Qubit) {
    int logical_bit = 1;
    ThreeQubitCode TQC;
    TQC.EncodeLogical(logical_bit);

    EXPECT_DOUBLE_EQ(TQC.state[0].alpha, 0.0);
    EXPECT_DOUBLE_EQ(TQC.state[0].beta, 1.0);

    EXPECT_DOUBLE_EQ(TQC.state[1].alpha, 0.0);
    EXPECT_DOUBLE_EQ(TQC.state[1].beta, 1.0);

    EXPECT_DOUBLE_EQ(TQC.state[2].alpha, 0.0);
    EXPECT_DOUBLE_EQ(TQC.state[2].beta, 1.0);
}

TEST(Qubit3CodeTest, bitflip) {
    int logical_bit = 1;
    ThreeQubitCode TQC;
    TQC.EncodeLogical(logical_bit);

    // Flip the second qubit
    PauliX X;
    X.ApplyX(TQC.state[1]);

    EXPECT_DOUBLE_EQ(TQC.state[0].alpha, 0.0);
    EXPECT_DOUBLE_EQ(TQC.state[0].beta, 1.0);

    EXPECT_DOUBLE_EQ(TQC.state[1].alpha, 1.0);
    EXPECT_DOUBLE_EQ(TQC.state[1].beta, 0.0);

    EXPECT_DOUBLE_EQ(TQC.state[2].alpha, 0.0);
    EXPECT_DOUBLE_EQ(TQC.state[2].beta, 1.0);

    // Restore bit using syndromes
    TQC.ApplySyndrome();

    EXPECT_DOUBLE_EQ(TQC.state[0].alpha, 0.0);
    EXPECT_DOUBLE_EQ(TQC.state[0].beta, 1.0);

    EXPECT_DOUBLE_EQ(TQC.state[1].alpha, 0.0);
    EXPECT_DOUBLE_EQ(TQC.state[1].beta, 1.0);

    EXPECT_DOUBLE_EQ(TQC.state[2].alpha, 0.0);
    EXPECT_DOUBLE_EQ(TQC.state[2].beta, 1.0);
}