#include "Codes.hpp"
#include "Operators.hpp"
#include "Qubit.hpp"
void ThreeQubitCode::EncodeLogical(const std::complex<double> &alpha, const std::complex<double> &beta) {
    state.state[0] = alpha;
    state.state[7] = beta;
}

void ThreeQubitCode::MeasureSyndrome() {
    // Expectation values of syndrome operators:
    // Z1*Z2
    QubitState Z0Z1(c_numQubits);
    Z0Z1 = state;
    Z.ApplyZ(Z0Z1, 0, c_numQubits);
    Z.ApplyZ(Z0Z1, 1, c_numQubits);
    double s_1 = M.InnerProduct(state, Z0Z1);
    // Z2*Z3
    QubitState Z1Z2(c_numQubits);
    Z1Z2 = state;
    Z.ApplyZ(Z1Z2, 1, c_numQubits);
    Z.ApplyZ(Z1Z2, 2, c_numQubits);
    double s_2 = M.InnerProduct(state, Z1Z2);

    // If less than 1 then an error has occurred
    // (a bit flip of either the first or second bit)
    if (s_1 < 0) {
        syndrome1 = 1;
    } else {
        syndrome1 = 0;
    }

    // If less than 1 then an error has occurred
    // (a bit flip of either the second or third bit)
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
        X.ApplyX(state, errorIndex, c_numQubits);
    }
}