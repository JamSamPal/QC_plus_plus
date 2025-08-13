#include "Codes.hpp"
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