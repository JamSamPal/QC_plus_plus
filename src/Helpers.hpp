#ifndef FF54B531_4A55_41D5_87E3_85ACF6806CDE
#define FF54B531_4A55_41D5_87E3_85ACF6806CDE
#include "Qubit.hpp"
#include <vector>
// Holds general vector/matrix manipulations and plotting
//
//
class MatrixHelper {
public:
    double InnerProduct(const QubitState &input1, const QubitState &input2);
};

struct BlochVector {
    double x, y, z;
};

class BlochSphere {
public:
    // Plotting looks best at this size
    BlochSphere() : size(7) {};
    BlochSphere(const int &size) : size(size) {};
    void DrawBlochSphere(const BlochVector &bloch);
    BlochVector GetBlochVector(const QubitState &state, const int &index);

private:
    int size;
    std::string shades = " .:-=+#";
};

#endif /* FF54B531_4A55_41D5_87E3_85ACF6806CDE */
