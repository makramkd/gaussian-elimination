//
// Created by Makram Kamaleddine on 11/1/15.
//

#ifndef MATRIX_RANDOM_TESTS_H
#define MATRIX_RANDOM_TESTS_H

#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <iomanip>
#include "matrix.hpp"

double generate_double()
{
    return ((1.0)*((double)std::rand()/RAND_MAX));
}

matrix<double> generate_random_matrix(unsigned N, unsigned M)
{
    std::vector<double> vec(N * M);
    std::generate(vec.begin(), vec.end(), generate_double);
    return matrix<double>(N, M, vec);
}

nvector<double> generate_rhs_vector(unsigned N)
{
    nvector<double> res(N);
    for (unsigned i = 0; i < N; ++i)
    {
        res[i] = generate_double();
    }
    return res;
}

nvector<double> generate_x_vector(unsigned N)
{
    nvector<double> res(N);
    for (unsigned i = 0; i < N; ++i)
    {
        res[i] = std::pow(-1.0, i + 1);
    }
    return res;
}

void test_random_matrices(unsigned minMatrixSize, unsigned maxMatrixSize,
                          int testCount, std::string fileName = "random_test.txt")
{
    std::ofstream file;
    file.open(fileName.c_str(), std::ios::out | std::ios::app);
    file << std::scientific << std::setprecision(15);
    file << "Testing random matrices with min matrix size of " << minMatrixSize << std::endl;
    file << "and max matrix size of " << maxMatrixSize << ": " << testCount << " tests total" << std::endl;
    for (unsigned i = minMatrixSize; i <= maxMatrixSize; ++i)
    {
        file << "BEGIN tests on size: " << i << std::endl;
        for (int j = 0; j < testCount; ++j)
        {
            auto matrix = generate_random_matrix(i, i);
            auto vector = generate_rhs_vector(i);

            auto no_piv = gaussian_no_pivoting(matrix, vector);
            auto p_piv = gaussian_partial_pivoting(matrix, vector);
            auto c_piv = gaussian_complete_pivoting(matrix, vector);

            file << "Test #:" << j + 1 << std::endl;
            file << "Input matrix:" << std::endl;
            file << matrix << std::endl;
            file << "Input RHS:" << std::endl;
            file << vector << std::endl;
            file << "Result from No pivoting:" << std::endl;
            file << no_piv << std::endl;
            file << "Result from Partial Pivoting:" << std::endl;
            file << p_piv << std::endl;
            file << "Result from Complete pivoting:" << std::endl;
            file << c_piv << std::endl;
        }
        file << "END tests on size: " << i << std::endl;
    }
    file << "END Tests;" << std::endl;
    file.close();
}

#endif //MATRIX_RANDOM_TESTS_H
