#include "Operators.hpp"
#include "Qubit.hpp"

Qubit PauliX::ApplyX(const Qubit &q) {
    // Pauli X matrix simply changes |0> -> |1> and |1> -> |0>
    return {q.beta, q.alpha};
}