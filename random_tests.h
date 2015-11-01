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
            auto xstar = generate_x_vector(i); // the solution we want: xstar
            auto rhs = matrix * xstar; // the rhs of the system

            auto xbar_nopiv = gaussian_no_pivoting(matrix, rhs);
            auto xbar_pp = gaussian_partial_pivoting(matrix, rhs);
            auto xbar_cp = gaussian_complete_pivoting(matrix, rhs);

            auto rel_res_nopiv = relative_residual(matrix, rhs, xbar_nopiv);
            auto rel_err_nopiv = relative_error(xbar_nopiv, xstar);

            auto rel_res_pp = relative_residual(matrix, rhs, xbar_pp);
            auto rel_err_pp = relative_error(xbar_pp, xstar);

            auto rel_res_cp = relative_residual(matrix, rhs, xbar_cp);
            auto rel_err_cp = relative_error(xbar_cp, xstar);

            file << "Test #:" << j + 1 << std::endl;
            file << "Input matrix:" << std::endl;
            file << matrix << std::endl;
            file << "Input RHS:" << std::endl;
            file << rhs << std::endl;
            file << "Result from No pivoting:" << std::endl;
            file << xbar_nopiv << std::endl;
            file << "Relative residual:" << rel_res_nopiv << std::endl;
            file << "Relative error:" << rel_err_nopiv << std::endl;
            file << "Result from Partial Pivoting:" << std::endl;
            file << xbar_pp << std::endl;
            file << "Relative residual:" << rel_res_pp << std::endl;
            file << "Relative error:" << rel_err_pp << std::endl;
            file << "Result from Complete pivoting:" << std::endl;
            file << xbar_cp << std::endl;
            file << "Relative residual:" << rel_res_cp << std::endl;
            file << "Relative error:" << rel_err_cp << std::endl;
        }
        file << "END tests on size: " << i << std::endl;
    }
    file << "END Tests;" << std::endl;
    file.close();
}

#endif //MATRIX_RANDOM_TESTS_H
