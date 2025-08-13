#include "Operators.hpp"
#include "Qubit.hpp"
#include <algorithm>

void PauliX::ApplyX(Qubit &q) {
    // Pauli X matrix simply changes |0> -> |1> and |1> -> |0>
    // It modifies the state
    std::swap(q.alpha, q.beta);
}

Qubit PauliZ::ApplyZ(const Qubit &q) {
    // This will be used to get the syndrome and so
    // doesn't modify the state
    return {q.alpha, -q.beta};
}