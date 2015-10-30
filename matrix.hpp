#ifndef matrix_hpp
#define matrix_hpp

#include <vector>
#include <algorithm>

// fwd declaration: in order to use enable_if
template<typename, const unsigned int, const unsigned int, typename = void> struct matrix;

// use matrices only for types that are arithmetic (i.e number types)
template<typename T, const unsigned int N, const unsigned int M>
struct matrix<T, N, M, typename std::enable_if<std::is_arithmetic<T>::value>::type> {

    matrix()
    : vec(N * M),
      rows(N),
      columns(M)
    {

    }

    matrix(T filler)
    : vec(N * M),
      rows(N),
      columns(M)
    {
        std::fill(vec.begin(), vec.end(), filler);
    }

    matrix(const matrix& other)
    : vec(other.vec),
      rows(other.rows),
      columns(other.columns)
    {

    }

    matrix(std::initializer_list<T> lst)
    : vec(N * M),
      rows(N),
      columns(M)
    {
        // only copy if they're the same size as the vector
        if (lst.size() == N * M) {
            std::copy(lst.begin(), lst.end(), vec.begin());
        }
    }

    T& operator()(unsigned int i, unsigned int j)
    {
        return vec[i * columns + j];
    }

    const T& operator()(unsigned int i, unsigned int j) const
    {
        return vec[i * columns + j];
    }

    unsigned int rowCount() const
    {
        return rows;
    }

    unsigned int colCount() const
    {
        return columns;
    }

    // data interface: return internal data
    std::vector<T> data() const
    {
        return vec;
    }

private:
    std::vector<T> vec;
    const unsigned int rows;
    const unsigned int columns;
};

// partial specialization of matrix in order to add some familiar operator[] syntax
// rather than using operator() for both matrices and vectors
template<typename T, const unsigned int N>
struct matrix<T, N, 1, typename std::enable_if<std::is_arithmetic<T>::value>::type> {

    matrix()
    : vec(N),
      rows(N)
    {

    }

    matrix(T filler)
    : vec(N),
      rows(N)
    {
        std::fill(vec.begin(), vec.end(), filler);
    }

    matrix(const matrix& other)
    : vec(other.vec),
      rows(other.rows)
    {

    }

    matrix(std::initializer_list<T> lst)
    : vec(N),
      rows(N)
    {
        if (lst.size() == N) {
            std::copy(lst.begin(), lst.end(), vec.begin());
        }
    }

    T& operator[](unsigned int i)
    {
        return vec[i];
    }

    const T& operator[](unsigned int i) const
    {
        return vec[i];
    }

    unsigned int size() const
    {
        return rows;
    }

    typename std::vector<T>::const_iterator begin() const
    {
        return vec.cbegin();
    }

    typename std::vector<T>::const_iterator end() const
    {
        return vec.cend();
    }
private:
    std::vector<T> vec;
    unsigned int rows;
};

template<typename T, const unsigned int N>
using nvector = matrix<T, N, 1, typename std::enable_if<std::is_arithmetic<T>::value>::type>;

template<class T, unsigned int N>
nvector<T, N> backsub(const matrix<T, N, N>& U, const nvector<T, N>& b)
{
    nvector<T, N> solution;
    
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

template<class T, unsigned int N>
nvector<T, N> gaussian_no_pivoting(const matrix<T, N, N>& A, nvector<T, N> b)
{
    matrix<T, N, N> partial(A); // to row reduce to upper triangular
    
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

template<class T, unsigned int N>
nvector<T, N> gaussian_partial_pivoting(const matrix<T, N, N>& A, nvector<T, N> b)
{
    matrix<T, N, N> partial(A); // to row reduce to upper triangular form
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

template<class T, unsigned int N>
nvector<T, N> gaussian_complete_pivoting(const matrix<T, N, N>& A, const nvector<T, N>& b)
{
    matrix<T, N, N> partial(A); // to row reduce
    nvector<T, N> result; // to return
    
    // code here
    
    
    return result;
}

#endif /* matrix_hpp */
