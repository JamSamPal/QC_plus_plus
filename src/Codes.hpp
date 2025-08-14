#ifndef EF4B01CA_BAA1_4AED_A5B4_9DFED445F636
#define EF4B01CA_BAA1_4AED_A5B4_9DFED445F636
#include "MatrixHelper.hpp"
#include "Operators.hpp"
#include "Qubit.hpp"
#include <vector>
// Holds all the QEC codes
//
//
class ThreeQubitCode {
public:
    const int c_numQubits = 3;
    ThreeQubitCode() : state(c_numQubits) {};
    QubitState state;
    void EncodeLogical(const std::complex<double> &alpha, const std::complex<double> &beta);
    void MeasureSyndrome();
    void Decode();
    void ApplySyndrome();
    int syndrome1;
    int syndrome2;
    int errorIndex;
    PauliX X;
    PauliZ Z;
    MatrixHelper M;

private:
    double ExpectationZZ(const int &indexA, const int &indexB);
    static const int lookup[2][2];
};

#endif /* EF4B01CA_BAA1_4AED_A5B4_9DFED445F636 */
