#ifndef D670A8F1_C2B1_4FCE_9D6A_1D8D5411A39A
#define D670A8F1_C2B1_4FCE_9D6A_1D8D5411A39A
#include <complex>
#include <vector>
class QubitState {
public:
    int numQubits;
    int numStates;
    // The amplitudes of the |0> and |1>
    // states of the qubit (which is put in an entangled state)
    // state[0] = |000>
    // state[1] = |001>
    // ...
    // state[7] = |111>
    std::vector<std::complex<double>> state;
    QubitState(const int &numQubits) : numQubits(numQubits), numStates(GetNumStates(numQubits)), state(numStates) {
    }
    constexpr static int GetNumStates(const int &numQubits);
};

constexpr int QubitState::GetNumStates(const int &numQubits) {
    return 1 << numQubits;
}

class DensityMatrix {
public:
    DensityMatrix(const int &size) : densityMatrix(size, std::vector<std::complex<double>>(size, {0.0, 0.0})) {};
    std::vector<std::vector<std::complex<double>>> densityMatrix;
};

#endif /* D670A8F1_C2B1_4FCE_9D6A_1D8D5411A39A */
