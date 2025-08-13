#ifndef D670A8F1_C2B1_4FCE_9D6A_1D8D5411A39A
#define D670A8F1_C2B1_4FCE_9D6A_1D8D5411A39A
class Qubit {
public:
    // The amplitudes of the |0> and |1>
    // states of the qubit
    double alpha;
    double beta;

    Qubit() : alpha(1.0), beta(0.0) {} // default to |0> state
    Qubit(double a, double b) : alpha(a), beta(b) {}
};

#endif /* D670A8F1_C2B1_4FCE_9D6A_1D8D5411A39A */
