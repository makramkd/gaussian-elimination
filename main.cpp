#include <iostream>
#include "matrix.hpp"

int main() {
    std::vector<double> vector1{2, 1, 1, 0, 4, 3, 3, 1, 8,7,9,5, 6,7,9,8};
    std::vector<double> vector2{1, 1, -1, 3};

    matrix<double, 4, 4> m1{2, 1, 1, 0, 4, 3, 3, 1, 8,7,9,5, 6,7,9,8};
    nvector<double, 4> b{1, 1, -1, 3};

    std::cout << "Information about A:" << std::endl;
    auto data = m1.data();
    for (auto i = data.begin(); i != data.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    std::cout << "Information about b:" << std::endl;
    std::cout << "b has " << b.size() << " rows" << std::endl;
    for (auto i = b.begin(); i != b.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    auto x = gaussian_no_pivoting(m1, b);
    auto y = gaussian_partial_pivoting(m1, b);

    std::cout << "x is: (" << x[0] << ", " << x[1] << ", " << x[2] << ", " << x[3] << ")" << std::endl;
    std::cout << "y is: (" << y[0] << ", " << y[1] << ", " << y[2] << ", " << y[3] << ")" << std::endl;
}