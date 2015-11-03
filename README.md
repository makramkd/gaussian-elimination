# Gaussian Elimination

Gaussian elimination impl in C++. We present an implementation of Gaussian elimination with three variations on the traditional algorithm:

1. Gaussian elimination with no pivoting: this algorithm is the "textbook" way to solve linear systems that are completely determined, and
uses no form of pivoting. 
2. Gaussian elimination with partial pivoting: this algorithm adds the idea of pivoting to the core elimination procedure, which 
theoretically is supposed to give us more accurate results.
3. Gaussian elimination with complete/total pivoting: this algorithm extends the idea of partial pivoting and provides a slower but more
accurate algorithm in order to solve completely determined linear systems of any kind (at least theoretically).

In addition to the above algorithms, we have for each algorithm a different back-substitution procedure. We also have a templated matrix
class and a templated vector class, that were done in as simplistic a fashion as possible so as not to complicate the implementation
of the elimination algorithm, as that is the purpose of this project.

