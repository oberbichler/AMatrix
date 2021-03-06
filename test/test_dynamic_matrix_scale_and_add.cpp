#include "amatrix.h"
#include "checks.h"

std::size_t TestMatrixScaleAndAdd(std::size_t TSize1, std::size_t TSize2) {
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> a_matrix(TSize1, TSize2);
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> b_matrix(TSize1, TSize2);
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> c_matrix(TSize1, TSize2);
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            a_matrix(i, j) = 2.33 * i - 4.52 * j;
    double scale_factor = 0.25;

    b_matrix = a_matrix.transpose();
    c_matrix = scale_factor * a_matrix + b_matrix.transpose();

    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            AMATRIX_CHECK_EQUAL(c_matrix(i, j), (1 + scale_factor) * (2.33 * i - 4.52 * j));

    return 0;  // not failed
}

std::size_t TestMatrixScaleAndAddEqual(std::size_t TSize1, std::size_t TSize2) {
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> a_matrix(TSize1, TSize2);
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> b_matrix(TSize1, TSize2);
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> c_matrix(TSize1, TSize2);
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            a_matrix(i, j) = 2.33 * i - 4.52 * j;
    double scale_factor = 0.25;

    b_matrix = a_matrix;
    a_matrix += scale_factor * b_matrix;

    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            AMATRIX_CHECK_EQUAL(a_matrix(i, j), (1 + scale_factor) * (2.33 * i - 4.52 * j));

    return 0;  // not failed
}

int main() {
    std::size_t number_of_failed_tests = 0;
	number_of_failed_tests += TestMatrixScaleAndAdd(1,1);

	number_of_failed_tests += TestMatrixScaleAndAdd(1,2);
	number_of_failed_tests += TestMatrixScaleAndAdd(2,1);
	number_of_failed_tests += TestMatrixScaleAndAdd(2,2);

	number_of_failed_tests += TestMatrixScaleAndAdd(3,1);
	number_of_failed_tests += TestMatrixScaleAndAdd(3,2);
	number_of_failed_tests += TestMatrixScaleAndAdd(3,3);
	number_of_failed_tests += TestMatrixScaleAndAdd(1,3);
	number_of_failed_tests += TestMatrixScaleAndAdd(2,3);
	number_of_failed_tests += TestMatrixScaleAndAdd(3,3);

 	number_of_failed_tests += TestMatrixScaleAndAddEqual(1,1);

	number_of_failed_tests += TestMatrixScaleAndAddEqual(1,2);
	number_of_failed_tests += TestMatrixScaleAndAddEqual(2,1);
	number_of_failed_tests += TestMatrixScaleAndAddEqual(2,2);

	number_of_failed_tests += TestMatrixScaleAndAddEqual(3,1);
	number_of_failed_tests += TestMatrixScaleAndAddEqual(3,2);
	number_of_failed_tests += TestMatrixScaleAndAddEqual(3,3);
	number_of_failed_tests += TestMatrixScaleAndAddEqual(1,3);
	number_of_failed_tests += TestMatrixScaleAndAddEqual(2,3);
	number_of_failed_tests += TestMatrixScaleAndAddEqual(3,3);

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
