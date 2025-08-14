#include "MatrixHelper.hpp"

double MatrixHelper::ExpectationValue(const QubitState &input) {
    // Calculates expectation value of quantum state
    // sum_i e_i <psi_i | psi_i >
    double tot = 0.0;

    for (int i = 0; i < input.state.size(); i++) {
        tot += input.currentEigenvalues[i] * std::norm(input.state[i]);
    }

    return tot;
}