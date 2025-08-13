#include "Codes.hpp"
#include "MatrixHelpers.hpp"
#include "Operators.hpp"
#include "Qubit.hpp"
void ThreeQubitCode::EncodeLogical(const int &logical) {
    Qubit q;
    if (logical == 1) {
        q.alpha = 0.0; // |1>
        q.beta = 1.0;
    } else {
        q.alpha = 1.0; // |0>
        q.beta = 0.0;
    }
    state[0] = q;
    state[1] = q;
    state[2] = q;
}

void ThreeQubitCode::ApplySyndrome() {
    // Expectation values of Z1, Z2 and Z3 operators
    Qubit q_0, q_1, q_2;
    q_0 = Z.ApplyZ(state[0]);
    q_1 = Z.ApplyZ(state[1]);
    q_2 = Z.ApplyZ(state[2]);

    MatrixHelpers M;
    double e_0 = M.InnerProduct(state[0], q_0);
    double e_1 = M.InnerProduct(state[1], q_1);
    double e_2 = M.InnerProduct(state[2], q_2);

    // Calculate syndromes, e.g. the expectation of Z1*Z2 and Z2*Z3
    // As state factorises this is just the product of
    // the expectation values of Z1 and Z2, and Z2 and Z3
    double s_1 = e_0 * e_1;
    double s_2 = e_1 * e_2;

    if (s_1 < 0 && s_2 < 0) {
        // Error is in second bit
        X.ApplyX(state[1]);
    } else if (s_1 < 0 && s_2 > 0) {
        // Error is in first bit
        X.ApplyX(state[0]);
    } else if (s_1 > 0 && s_2 < 0) {
        // Error is in third bit
        X.ApplyX(state[2]);
    }
}