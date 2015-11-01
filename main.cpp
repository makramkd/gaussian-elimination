#include <iostream>
#include "matrix.hpp"
#include "random_tests.h"

int main() {

    const unsigned minMatrixSize = 3;
    const unsigned maxMatrixSize = 4;
    const int testCount = 15; // 5 tests per size

    test_random_matrices(minMatrixSize, maxMatrixSize, testCount, "random_tests9.txt");

}