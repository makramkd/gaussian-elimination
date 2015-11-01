//
// Created by Makram Kamaleddine on 11/1/15.
//

#ifndef MATRIX_RANDOM_TESTS_H
#define MATRIX_RANDOM_TESTS_H

#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include "matrix.hpp"

double generate_double()
{
    std::mt19937 rng;
    std::uniform_real_distribution<double> u(0.0, 1.0);
    return u(rng);
}

matrix<double> generate_random_matrix(unsigned N, unsigned M)
{
    std::vector<double> vec(N * M);
    std::generate(vec.begin(), vec.end(), generate_double);
    return matrix(N, M, vec);
}

nvector<double> generate_rhs_vector(unsigned N)
{
    nvector<double> res(N);
    for (unsigned i = 0; i < N; ++i)
    {
        res[i] = std::pow(-1.0, i + 1);
    }
    return res;
}

void test_random_matrices(int minMatrixSize, int maxMatrixSize, int testCount)
{
    
}

#endif //MATRIX_RANDOM_TESTS_H
