#include "Codes.hpp"
#include "Operators.hpp"
#include "Qubit.hpp"
void ThreeQubitCode::EncodeLogical(const std::complex<double> &alpha, const std::complex<double> &beta) {
    state.state[0] = alpha;
    state.state[7] = beta;

    if (codeMode == CodeMode::PhaseFlip) {
        // Apply Hadamards to all qubits to go into |+++> / |--->
        for (int q = 0; q < c_numQubits; q++) {
            H.ApplyH(state, q, c_numQubits);
        }
    }
}

void ThreeQubitCode::MeasureSyndrome() {
    // Performs stabiliser measurements
    // to calculate syndromes
    double s_1 = 0.0;
    double s_2 = 0.0;
    if (codeMode == CodeMode::BitFlip) {
        // Z1*Z2
        QubitState Z0Z1(c_numQubits);
        Z0Z1 = state;
        Z.ApplyZ(Z0Z1, 0, c_numQubits);
        Z.ApplyZ(Z0Z1, 1, c_numQubits);
        s_1 = M.InnerProduct(state, Z0Z1);

        // Z2*Z3
        QubitState Z1Z2(c_numQubits);
        Z1Z2 = state;
        Z.ApplyZ(Z1Z2, 1, c_numQubits);
        Z.ApplyZ(Z1Z2, 2, c_numQubits);
        s_2 = M.InnerProduct(state, Z1Z2);

    } else if (codeMode == CodeMode::PhaseFlip) {
        // X1*X2
        QubitState X0X1(c_numQubits);
        X0X1 = state;
        X.ApplyX(X0X1, 0, c_numQubits);
        X.ApplyX(X0X1, 1, c_numQubits);
        s_1 = M.InnerProduct(state, X0X1);

        // X2*X3
        QubitState X1X2(c_numQubits);
        X1X2 = state;
        X.ApplyX(X1X2, 1, c_numQubits);
        X.ApplyX(X1X2, 2, c_numQubits);
        s_2 = M.InnerProduct(state, X1X2);
    }

    syndrome1 = (s_1 < 0) ? 1 : 0;
    syndrome2 = (s_2 < 0) ? 1 : 0;
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
        if (codeMode == CodeMode::BitFlip) {
            X.ApplyX(state, errorIndex, c_numQubits);
        } else if (codeMode == CodeMode::PhaseFlip) {
            Z.ApplyZ(state, errorIndex, c_numQubits);
            // Return to computational basis
            for (int q = 0; q < c_numQubits; q++) {
                H.ApplyH(state, q, c_numQubits);
            }
        }
    }
}