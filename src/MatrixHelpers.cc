#include "MatrixHelpers.hpp"

double MatrixHelpers::InnerProduct(const Qubit &q_1, const Qubit &q_2) {
    return q_1.alpha * q_2.alpha + q_1.beta * q_2.beta;
}