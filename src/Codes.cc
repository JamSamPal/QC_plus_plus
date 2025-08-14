#include "Codes.hpp"
#include "Operators.hpp"
#include "Qubit.hpp"
void ThreeQubitCode::EncodeLogical(const std::complex<double> &alpha, const std::complex<double> &beta) {
    state.state[0] = alpha;
    state.state[7] = beta;
}

double ThreeQubitCode::ExpectationZZ(const int &indexA, const int &indexB) {
    // Calculates expectation value of Z_A * Z_B
    double exp = 0.0;
    double zA = 0.0;
    double zB = 0.0;
    for (int i = 0; i < 8; i++) {
        // Find the bits at index A and B
        // Shift them into the LSB position
        // and then mask to just extract the bit
        int bitA = (i >> (2 - indexA)) & 1;
        int bitB = (i >> (2 - indexB)) & 1;

        // If bit is a zero then applying Z operator:
        // Z |0> = +1|0>
        // Else it's a one
        // Z |1> = -1|1>
        if (bitA == 0) {
            zA = 1;
        } else {
            zA = -1;
        }

        if (bitB == 0) {
            zB = 1;
        } else {
            zB = -1;
        }

        // The expectation value is given by the sum over
        // <\psi_i | Z_A Z_B |\psi_i> for all states
        // Calculating the eigenvalues this is then simply
        // zA*zB multiplied by the sum over <\psi_i |\psi_i>.
        // Of course, our usual entangled state we start with
        // has \psi_0, \psi_7 != 0 and the rest equal to 0.
        exp += zA * zB * std::norm(state.state[i]);
    }

    return exp;
}

void ThreeQubitCode::MeasureSyndrome() {
    // Expectation values of syndrome operators:
    // Z1*Z2 and Z2*Z3
    double s_1 = ExpectationZZ(0, 1);
    double s_2 = ExpectationZZ(1, 2);

    if (s_1 < 0) {
        syndrome1 = 1;
    } else {
        syndrome1 = 0;
    }

    if (s_2 < 0) {
        syndrome2 = 1;
    } else {
        syndrome2 = 0;
    }
}
const int ThreeQubitCode::lookup[2][2] = {
    {-1, 2}, // s1=0
    {0, 1}   // s1=1
};

void ThreeQubitCode::Decode() {
    errorIndex = lookup[syndrome1][syndrome2];
}

void ThreeQubitCode::ApplySyndrome() {
    if (errorIndex >= 0) {
        X.ApplyX(state, errorIndex, 3);
    }
}