#ifndef D670A8F1_C2B1_4FCE_9D6A_1D8D5411A39A
#define D670A8F1_C2B1_4FCE_9D6A_1D8D5411A39A
#include <complex>
#include <vector>
class QubitState {
public:
    // The amplitudes of the |0> and |1>
    // states of the qubit (which is put in an entangled state)
    // state[0] = |000>
    // state[1] = |001>
    // ...
    // state[7] = |111>
    std::vector<std::complex<double>> state;
    int numQubits;
    int numStates;
    QubitState(const int &numQubits) : numQubits(numQubits) {
        numStates = 1 << numQubits;
        state.resize(numStates);
    }
};

#endif /* D670A8F1_C2B1_4FCE_9D6A_1D8D5411A39A */
