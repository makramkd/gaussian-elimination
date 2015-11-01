#include <iostream>
#include "matrix.hpp"

int main() {
    // new scope: test 1
    {
        std::vector<double> vector1{2, 1, 1, 0, 4, 3, 3, 1, 8,7,9,5, 6,7,9,8};
        std::vector<double> vector2{1, 1, -1, 3};

        matrix<double> m1(4, 4, {2, 1, 1, 0, 4, 3, 3, 1, 8,7,9,5, 6,7,9,8});
        nvector<double> b(4, {1, 1, -1, 3});

//        std::cout << "Information about A:" << std::endl;
//        auto data = m1.data();
//        for (auto i = data.begin(); i != data.end(); ++i) {
//            std::cout << *i << " ";
//        }
//        std::cout << std::endl;
//
//        std::cout << "Information about b:" << std::endl;
//        std::cout << "b has " << b.size() << " rows" << std::endl;
//        for (auto i = b.begin(); i != b.end(); ++i) {
//            std::cout << *i << " ";
//        }
//        std::cout << std::endl;

        auto x = gaussian_no_pivoting(m1, b);
        auto y = gaussian_partial_pivoting(m1, b);
        auto z = gaussian_complete_pivoting(m1, b);

        std::cout << "x is: (" << x[0] << ", " << x[1] << ", " << x[2] << ", " << x[3] << ")" << std::endl;
        std::cout << "y is: (" << y[0] << ", " << y[1] << ", " << y[2] << ", " << y[3] << ")" << std::endl;
        std::cout << "z is: (" << z[0] << ", " << z[1] << ", " << z[2] << ", " << z[3] << ")" << std::endl;
    }
    {
        // random matrix obtained by rand() from octave
        std::vector<double> vector1{0.505170, 0.319162, 0.055511, 0.320261,
        0.871669, 0.620923, 0.261755, 0.449800, 0.293107};
        std::vector<double> vector2{0.892676, 0.722300, 0.093932};

        matrix<double> m1(3, 3, {0.505170, 0.319162, 0.055511, 0.320261,
                                 0.871669, 0.620923, 0.261755, 0.449800, 0.293107});
        nvector<double> b(3, {0.892676, 0.722300, 0.093932});

        auto x = gaussian_no_pivoting(m1, b);
        auto y = gaussian_partial_pivoting(m1, b);
        auto z = gaussian_complete_pivoting(m1, b);

        std::cout << "x is: (" << x[0] << ", " << x[1] << ", " << x[2] << ")" << std::endl;
        std::cout << "y is: (" << y[0] << ", " << y[1] << ", " << y[2] << ")" << std::endl;
        std::cout << "z is: (" << z[0] << ", " << z[1] << ", " << z[2] << ")" << std::endl;
    }
    {
        // random matrix obtained by rand() from octave
        std::vector<double> vector1{0.654685 ,  0.720004  , 0.018242 ,  0.975395 ,  0.982658,
        0.454674  , 0.093996  , 0.595628 ,  0.553775 ,  0.638518,
        0.295120  , 0.744430 ,  0.816709 ,  0.205386 ,  0.748289,
        0.925692 ,  0.517190 ,  0.373999  , 0.442019 ,  0.306950,
        0.229962  , 0.695608  , 0.225804  , 0.164334  , 0.835898};

        std::vector<double> vector2{0.601810,
                0.078653,
                0.525409,
                0.765338,
                0.517138};

        matrix<double> m1(5, 5, {0.654685 ,  0.720004  , 0.018242 ,  0.975395 ,  0.982658,
                                 0.454674  , 0.093996  , 0.595628 ,  0.553775 ,  0.638518,
                                 0.295120  , 0.744430 ,  0.816709 ,  0.205386 ,  0.748289,
                                 0.925692 ,  0.517190 ,  0.373999  , 0.442019 ,  0.306950,
                                 0.229962  , 0.695608  , 0.225804  , 0.164334  , 0.835898});
        nvector<double> b(5, {0.601810,
                              0.078653,
                              0.525409,
                              0.765338,
                              0.517138});

        auto x = gaussian_no_pivoting(m1, b);
        auto y = gaussian_partial_pivoting(m1, b);
        auto z = gaussian_complete_pivoting(m1, b);

        std::cout << "x is: (" << x[0] << ", " << x[1] << ", " << x[2] << ", " << x[3] << ", " << x[4] << ")" << std::endl;
        std::cout << "y is: (" << y[0] << ", " << y[1] << ", " << y[2] << ", " << y[3] << ", " << y[4] << ")" << std::endl;
        std::cout << "z is: (" << z[0] << ", " << z[1] << ", " << z[2] << ", " << z[3] << ", " << z[4] << ")" << std::endl;
    }
}