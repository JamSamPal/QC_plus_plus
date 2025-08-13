# QEC-Codes
Project that explores QEC codes.

- Uses OOP, passing semantics and CI best practises

## Background
Quantum Error Correcting codes, like their classical counterparts seek to make information robust to error by cleverly encoding it. Unlike in the classical case operations like copying the data or examining individual (qu)bits directly are not available due to the no-cloning theorem and wavefunction collapse respectively. Thus QEC codes present a substantial challenge - how can we prevent errors if we can't just copy the data a bunch of times? And how do we detect errors if we can't measure a qubit directly?

The solution is to use entanglement to duplicate the information and special operators/measurements (stabilisers) to probe the state.

In the simplest case, we assume at most one bit flip occurs. This is the equivalent of multiplying a qubit by the Pauli X matrix [[0,1],[1,0]] where the qubit state:

q = a*|0> + b*|1> = a*[1,0] + b*[0,1], for a,b complex in the representation |0> = [1,0] and |1> = [0,1]. Note the phase of a qubit's state is preserved in this type of error.

Let us solve the first of our problems and duplicate information not by cloning the state but by entangling it with other qubits. We assume we wish to encode the logical bit |0> and so form the state

q = a*|000> + b*|111> 

by entangling with two other qubits.

After this duplication we assume a bit flip occurs, e.g.:

q = a*|010> + b*|101>

We may now consider the action of the Pauli Z matrix [[1,0],[0,-1]] on the ith qubit. This gives +1 if the qubit is ∣0> and −1 if it is |1>. One can see that the expectation value of this operator will be +1 if there is no flip and -1 if there is 1. 

This operator is problematic as it can be used to determine the ith bit exactly, destroying the superposition.

By combining two operators A = Z_1 * Z_2 however we only find out about the state |b_1,b_2>: it will equal +1 if there are no flips in the first two bits and -1 otherwise. Because it doesn't tell us about the individual bits it preserves the quantum state and doesn't collapse it which is what we wanted. Forming the operator B = Z_2 * Z_3 we have the same thing for the second and third bits. Thus:

A = 1, B = 1 -> No error
A = 1, B =-1 -> Error in third bit
A =-1, B = 1 -> Error in first bit
A =-1, B =-1 -> Error in second bit

And thus we can identify the location of the error by performing measurements that do not destory the quantum state, exactly as we desired.


