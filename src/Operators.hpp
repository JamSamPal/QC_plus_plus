#ifndef DDFFC357_B156_4108_B576_06019B4A3A44
#define DDFFC357_B156_4108_B576_06019B4A3A44
#include "Qubit.hpp"
// Holds the possible operators on a Qubit or state
//
//
class PauliX {
public:
    PauliX() {};
    void ApplyX(QubitState &psi, const int &index, const int &numQubits);
};

class PauliZ {
public:
    PauliZ() {};
    void ApplyZ(QubitState &psi, const int &index, const int &numQubits);
};

class Hadamard {
public:
    Hadamard() {};
    void ApplyH(QubitState &psi, const int &index, const int &numQubits);
};

class CNOT {
public:
    CNOT() {};
    void ApplyCN(QubitState &psi, const int &source, const int &target, const int &numQubits);
};

#endif /* DDFFC357_B156_4108_B576_06019B4A3A44 */
