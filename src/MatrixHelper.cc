#include "MatrixHelper.hpp"

double MatrixHelper::InnerProduct(const QubitState &input1, const QubitState &input2) {
    // Calculates
    // sum_i <psi_i | psi'_i >
    std::complex<double> tot(0.0, 0.0);

    for (int i = 0; i < input1.state.size(); i++) {
        tot += (std::conj(input1.state[i]) * input2.state[i]);
    }

    // If all has gone correctly the imaginary part should be zero
    return tot.real();
}
