#include "Operators.hpp"
#include "Qubit.hpp"
#include <algorithm>

void PauliX::ApplyX(QubitState &psi, const int &index, const int &numQubits) {
    // Pauli X matrix simply changes |0> -> |1> and |1> -> |0>
    // modifying the state.
    //
    // If we wish to flip the first qubit, e.g. take
    // alpha |000> + beta |111> into alpha |100> + beta |011>
    // then we simply need to swap the values of the state vector psi
    // at 0 and 4 and 7 and 3.
    //
    // flip_bit is the bit that is getting operated on by X
    int flipBit = 1 << (numQubits - 1 - index);
    for (int i = 0; i < psi.state.size(); i++) {
        // XOR flips the bit
        int j = i ^ flipBit;
        // Ensure we swap each pair only once
        if (i < j) {
            std::swap(psi.state[i], psi.state[j]);
        }
    }
}

void PauliZ::ApplyZ(QubitState &psi, const int &index, const int &numQubits) {
    // Pauli Z matrix acting on bit at index = index
    // Z |0> = +1 |0>
    // Z |1> = -1 |1>
    //
    // create an int which has binary form 00x0000
    // where x =1 is the position of the bit we apply
    // the z operator to
    int parity_bit = 1 << (numQubits - 1 - index);
    for (int i = 0; i < psi.state.size(); i++) {
        // If the bit isn't set then masking will return 0
        // otherwise it will be non-zero
        int isBitSet = i & parity_bit;

        // A set bit results in a -1 eigenvalue
        if (isBitSet != 0) {
            psi.state[i] *= -1.0;
        }
    }
}