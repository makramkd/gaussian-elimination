//
//  matrix.hpp
//  matrix
//
//  Created by Makram Kamaleddine on 10/18/15.
//  Copyright © 2015 Makram Kamaleddine. All rights reserved.
//

#ifndef matrix_hpp
#define matrix_hpp

#include <vector>
#include <algorithm>
#include "nvector.h"

template<class T>
class matrix {
public:
    matrix()
    :array(nullptr),
    rows(0),
    cols(0),
    arr_size(0)
    {
        
    }
    
    ~matrix()
    {
    }
    
    matrix(int rowcols)
    : array(rowcols * rowcols),
    rows(rowcols),
    cols(rowcols),
    arr_size(rowcols * rowcols)
    {
        
    }
    
    matrix(int rows, int cols)
    : array(rows * cols),
    rows(rows),
    cols(cols),
    arr_size(rows * cols)
    {
        
    }
    
    matrix(int rows, int cols, const std::vector<T>& filler)
    : array(rows * cols),
    rows(rows),
    cols(cols),
    arr_size(rows * cols)
    {
        std::copy(filler.begin(), filler.end(), array.begin());
    }
    
    matrix(int rows, int cols, T fill)
    : array(rows * cols),
    rows(rows),
    cols(cols),
    arr_size(rows * cols)
    {
        std::fill(array.begin(), array.end(), fill);
    }
    
    matrix(const matrix& other)
    : array(other.rows * other.cols),
    rows(other.rows),
    cols(other.cols),
    arr_size(other.arr_size)
    {
        std::copy(other.array.begin(), other.array.end(), array.begin());
    }
    
    const T& operator()(int i, int j) const
    {
        return array[j + i * rows];
    }
    
    T& operator()(int i, int j)
    {
        return array[j + i * rows];
    }
    
    void set(int i, int j, T value)
    {
        array[j + i * rows] = value;
    }
    
    int rowCount() const
    {
        return rows;
    }
    
    int colCount() const
    {
        return cols;
    }
    
    std::vector<T> data()
    {
        return array;
    }
    
    int arraySize() const
    {
        return arr_size;
    }
    
private:
    std::vector<T> array;
    int rows;
    int cols;
    int arr_size;
};

template<class T>
nvector<T> backsub(const matrix<T>& U, const nvector<T>& b)
{
    nvector<T> solution(b.size());
    
    const auto n = U.rowCount();
    for (int i = n - 1; i >= 0; --i) {
        solution[i] = b[i];
        for (int j = i + 1; j < n; ++j) {
            solution[i] = solution[i] - U(i, j) * solution[j];
        }
        solution[i] /= U(i, i);
    }
    
    return solution;
}

template<class T>
nvector<T> gaussian_no_pivoting(const matrix<T>& A, nvector<T> b)
{
    matrix<T> partial(A); // to row reduce to upper triangular
    
    // code here
    const auto nMinus1 = partial.colCount() - 1;
    const auto n = partial.rowCount();
    for (int i = 0; i < nMinus1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // calculate the ratio
            auto below = partial(j, i);
            auto diag = partial(i, i);
            auto ratio = partial(j, i) / partial(i, i);
            for (int k = i; k < n; ++k) {
                // modify matrix entry
                auto pjk = partial(j, k);
                auto pik = partial(i, k);
                partial(j, k) = partial(j, k) - ratio * partial(i, k);
            }
            
            // modify result vector
            auto rj0 = b[j];
            auto bi0 = b[i];
            b[j] = b[j] - ratio * b[i];
            auto rjAfter = b[j];
        }
    }
    
    return backsub(partial, b);
}

template<class T>
nvector<T> gaussian_partial_pivoting(const matrix<T>& A, nvector<T> b)
{
    matrix<T> partial(A); // to row reduce to upper triangular form
    std::vector<int> piv(A.rowCount()); // pivot vector

    // init the pivot vector with the default (no pivots)
    for (int i = 0; i < piv.size(); ++i) {
        piv[i] = i + 1;
    }

    const auto nMinus1 = partial.colCount() - 1;
    const auto n = partial.rowCount();
    for (int i = 0; i < nMinus1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // do the pivot
            auto maxvalue = partial(j, i);
            int pivotIndex = -1;
            for (int k = j + 1; k < n; ++k) {
                if (partial(k, i) > maxvalue) {
                    pivotIndex = k;
                    maxvalue = partial(k, i);
                }
            }

            if (pivotIndex != -1) {
                // do the swap
                std::swap(piv[j], piv[pivotIndex]);
            }

            // calculate the ratio
            auto below = partial(piv[j], i);
            auto diag = partial(piv[i], i);
            auto ratio = partial(piv[i], i) / partial(piv[i], i);
            for (int k = i; k < n; ++k) {
                // modify matrix entry
                auto pjk = partial(piv[j], k);
                auto pik = partial(piv[i], k);
                partial(piv[j], k) = partial(piv[j], k) - ratio * partial(piv[i], k);
            }

            // modify result vector
            auto rj0 = b[j];
            auto bi0 = b[i];
            b[piv[j]] = b[piv[j]] - ratio * b[piv[i]];
            auto rjAfter = b[j];
        }
    }

    return backsub(partial, b);
}

template<class T>
matrix<T> gaussian_complete_pivoting(const matrix<T>& A, const matrix<T>& b)
{
    matrix<T> partial(A); // to row reduce
    matrix<T> result(b.rowCount(), b.colCount()); // to return
    
    // code here
    
    
    return result;
}

#endif /* matrix_hpp */
