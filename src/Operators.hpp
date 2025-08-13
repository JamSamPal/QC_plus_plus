#ifndef DDFFC357_B156_4108_B576_06019B4A3A44
#define DDFFC357_B156_4108_B576_06019B4A3A44
#include "Qubit.hpp"
// Holds the possible operators on a Qubit or state
//
//
class PauliX {
public:
    PauliX() {};
    Qubit ApplyX(const Qubit &q);
};
#endif /* DDFFC357_B156_4108_B576_06019B4A3A44 */
