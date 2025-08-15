#include "Helpers.hpp"
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

BlochVector BlochSphere::GetBlochVector(const QubitState &state, const int &index) {
    // Gets the bloch vector for the qubit in state at the given index
    // x = <X> where X is the pauli X matrix
    // y = <Y>
    // z = <Z>
    // Calculating these for the state \alpha|0> + \beta|1> gives
    // the following
    BlochVector v;
    v.x = 2.0 * std::real(std::conj(state.state[0]) * state.state[1]);
    v.y = 2.0 * std::imag(std::conj(state.state[0]) * state.state[1]);
    v.z = std::norm(state.state[0]) - std::norm(state.state[1]);
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