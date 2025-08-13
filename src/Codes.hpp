#ifndef EF4B01CA_BAA1_4AED_A5B4_9DFED445F636
#define EF4B01CA_BAA1_4AED_A5B4_9DFED445F636
#include "Operators.hpp"
#include "Qubit.hpp"
#include <vector>
// Holds all the QEC codes
//
//
class ThreeQubitCode {
public:
    ThreeQubitCode() : state(3) {}
    void EncodeLogical(const int &logical);
    std::vector<Qubit> state;
    void ApplySyndrome();
    PauliX X;
    PauliZ Z;
};
#endif /* EF4B01CA_BAA1_4AED_A5B4_9DFED445F636 */
