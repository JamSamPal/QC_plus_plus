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

    QubitState() : state(8, 0.0) {
        for (int i = 0; i < 8; ++i) {
            state[i] = std::complex<double>(0.0, 0.0);
        }
    }
};

#endif /* D670A8F1_C2B1_4FCE_9D6A_1D8D5411A39A */
