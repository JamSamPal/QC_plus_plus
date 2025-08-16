#ifndef EF4B01CA_BAA1_4AED_A5B4_9DFED445F636
#define EF4B01CA_BAA1_4AED_A5B4_9DFED445F636
#include "Helpers.hpp"
#include "Operators.hpp"
#include "Qubit.hpp"
#include <vector>
// Holds all the QEC codes
//
//

enum class CodeMode { BitFlip,
                      PhaseFlip };
class ThreeQubitCode {
public:
    ThreeQubitCode(CodeMode code) : state(c_numQubits), codeMode(code) {};
    QubitState state;
    void EncodeLogical(const std::complex<double> &alpha, const std::complex<double> &beta);
    void MeasureSyndrome();
    void Decode();
    void ApplySyndrome();
    int syndrome1;
    int syndrome2;
    int errorIndex;

private:
    const int c_numQubits = 3;
    CodeMode codeMode;
    PauliX X;
    PauliZ Z;
    Hadamard H;
    MatrixHelper M;
    static const int lookup[2][2];
};

#endif /* EF4B01CA_BAA1_4AED_A5B4_9DFED445F636 */
