#include "Operators.hpp"
#include "Qubit.hpp"
#include <algorithm>

void PauliX::ApplyX(QubitState &psi, const int &index, const int &numQubits) {
    // Pauli X matrix simply changes |0> -> |1> and |1> -> |0>
    // modifying the state
    // if we wish to flip the first qubit, e.g. take
    // alpha |000> + beta |111> into alpha |100> + beta |011>
    // then we simply need to swap the values of the state vector psi
    // at 0 and 4 and 7 and 3.
    // This value is how far apart the states we swap are, for the example
    // above this would be 4 because index = 0
    int flip_bit = 1 << (numQubits - 1 - index);
    for (int i = 0; i < psi.state.size(); i++) {
        int j = i ^ flip_bit; // XOR flips the bit at position `index`
        if (i < j) {          // swap each pair only once
            std::swap(psi.state[i], psi.state[j]);
        }
    }
}