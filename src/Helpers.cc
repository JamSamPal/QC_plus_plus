#include "Helpers.hpp"
#include <algorithm>
#include <complex>
#include <iostream>
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

DensityMatrix MatrixHelper::GetDensityMatrix(const QubitState &state) {
    // Gets the density matrix of a given state
    DensityMatrix output(state.state.size());

    for (int i = 0; i < state.state.size(); i++) {
        // DM is Hermitian so we can cut this loop in half
        for (int j = 0; j <= i; j++) {
            output.densityMatrix[i][j] = state.state[i] * std::conj(state.state[j]);
            output.densityMatrix[j][i] = std::conj(state.state[i]) * state.state[j];
        }
    }

    return output;
}

DensityMatrix MatrixHelper::GetReducedDensityMatrix(const DensityMatrix &dM, const int &qubitToKeep, const int &numQubits) {
    // Calculates the partial trace over all qubits except the one indicated
    //
    // The density matrix of a single qubit will always be dimension 2x2
    DensityMatrix reduced(2);

    auto toBinary = [numQubits](int n) -> std::string {
        std::string result;
        for (int i = 0; i < numQubits; i++) {
            if (n & 1) {
                result.push_back('1');
            } else {
                result.push_back('0');
            }
            n >>= 1;
        }
        // reverse so that most significant bit comes first
        std::reverse(result.begin(), result.end());
        return result;
    };

    for (int i = 0; i < dM.densityMatrix.size(); i++) {
        for (int j = 0; j < dM.densityMatrix.size(); j++) {
            bool traceOutMatch = true;
            std::string iBin = toBinary(i);
            std::string jBin = toBinary(j);

            // The only pieces of the density matrix we care about
            // are when the two states match on the qubits
            // we wish to trace out. E.g. If we were considering a
            // two qubit state and were tracing out the first qubit
            // then we would want to consider |10><11| (or dM[2][3])
            // as the first qubit matches. This would then contribute to
            // |0><1| in the reduced state.
            for (int k = 0; k < numQubits; ++k) {
                if (k != qubitToKeep && iBin[k] != jBin[k]) {
                    traceOutMatch = false;
                    break;
                }
            }

            if (traceOutMatch) {
                int iReduced = iBin[qubitToKeep] - '0';
                int jReduced = jBin[qubitToKeep] - '0';

                reduced.densityMatrix[iReduced][jReduced] += dM.densityMatrix[i][j];
            }
        }
    }

    return reduced;
}

BlochVector
BlochSphere::GetBlochVector(const DensityMatrix &DM) {
    // Gets the bloch vector from a reduced density matrix
    // x = <X> where X is the pauli X matrix
    // y = <Y>
    // z = <Z>
    // The density matrix can be written as 0.5*(I + X + Y + Z)
    // Working through gives the x,y,z values below
    BlochVector v;
    v.x = 2.0 * DM.densityMatrix[1][0].real();
    v.y = 2.0 * DM.densityMatrix[1][0].imag();
    v.z = 2.0 * DM.densityMatrix[0][0].real() - 1;
    return v;
}

void BlochSphere::DrawBlochSphere(const BlochVector &bloch) {
    // The bloch sphere is depicted as a projection onto
    // the x-z and y-z planes
    int nShades = shades.size() - 1;
    auto draw_projection = [&](char axis1, char axis2) {
        for (int i = -size; i <= size; ++i) {
            for (int j = -size - 2; j <= size + 2; ++j) {
                double r = std::sqrt(i * i + j * j) / size;
                if (r > 1.0) {
                    std::cout << ' ';
                } else {
                    int a = std::round((axis1 == 'x' ? bloch.x : axis1 == 'y' ? bloch.y
                                                                              : bloch.z) *
                                       size);
                    int b = std::round((axis2 == 'x' ? bloch.x : axis2 == 'y' ? bloch.y
                                                                              : bloch.z) *
                                       size);

                    if (i == -b && j == a) {
                        // state marker
                        std::cout << '*';
                    } else {
                        // 3rd axis depth with shading creating the illusion of this depth
                        double depth = std::sqrt(1.0 - r * r);
                        int shadeIdx = std::round(depth * nShades);
                        std::cout << shades[shadeIdx];
                    }
                }
            }
            std::cout << '\n';
        }
    };

    std::cout << "====================\n BLOCH SPHERE \n====================\n\n * = STATE \n\n";
    // X–Z projection
    std::cout << "==== x-z Projection ==== \n";
    draw_projection('x', 'z');
    std::cout << "\n\n";
    // Y–Z projection
    std::cout << "==== y-z Projection ====\n";
    draw_projection('y', 'z');
}