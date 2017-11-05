
#include <iostream>

#include "timer.h"
#include "matrix.h"

#if defined(AMATRIX_COMPARE_WITH_EIGEN)
#include "Eigen/Dense"
#endif

template<typename TMatrixType, int NumberOfRows, int NumberOfColumns>
class ComparisonColumn{
	TMatrixType mA;
	void initialize(TMatrixType& TheMatrix){
		for(int i = 0 ; i < NumberOfRows ; i++)
			for(int j  = 0 ; j < NumberOfColumns ; j++)
				TheMatrix(i,j) = 0.00;
	}

public:
	
	ComparisonColumn(){
		initialize(mA);
	}
	
	Timer::duration_type MeasureAccessTime() {
		int repeat_number = 10000000;
		Timer timer;
		for (int i_repeat = 0; i_repeat < repeat_number; i_repeat++)
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					mA(i, j) += i - j;
		return timer.elapsed().count();
	}

	

};


template <typename TMatrixType>
Timer::duration_type MeasureAssignTime(TMatrixType& A) {
    int repeat_number = 10000000;
    TMatrixType B = A;
    Timer timer;
    for (int i_repeat = 0; i_repeat < repeat_number; i_repeat++) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                B(i, j) += i - j;
        A = B;
    }

    return timer.elapsed().count();
}

template <typename TMatrixType>
Timer::duration_type MeasureSumTime(TMatrixType& A, TMatrixType& B) {
    int repeat_number = 10000;
    TMatrixType C = A;
    TMatrixType D = A;
    Timer timer;
    for (int i_repeat = 0; i_repeat < repeat_number; i_repeat++) {
        C = A + B;
        B = C;
    }

    return timer.elapsed().count();
}

template <typename TMatrixType1, typename TMatrixType2>
Timer::duration_type MeasureMultTime(TMatrixType1& A, TMatrixType2& B) {
    int repeat_number = 1000;
    TMatrixType1 C = A;
    TMatrixType1 D = A;
    Timer timer;
    for (int i_repeat = 0; i_repeat < repeat_number; i_repeat++) {
        D = A;
        for (int i = 0; i < 1000; i++) {
            C = D * B;
            D = C;
        }
    }

    return timer.elapsed().count();
}

void CompareAccessTime() {
    ComparisonColumn<AMatrix::Matrix<double, 3, 3>,3,3> a_matrix_column;
    ComparisonColumn<Eigen::Matrix<double, 3, 3>,3,3> eigen_column;
	std::cout << "A[i,j] += i -j\t\t" << a_matrix_column.MeasureAccessTime();
	std::cout << "\t\t" << eigen_column.MeasureAccessTime() << std::endl;
}

void CompareAssignTime() {
    AMatrix::Matrix<double, 3, 3> m_33(0.00);
    std::cout << "A = B\t\t\t" << MeasureAssignTime(m_33) << std::endl;
}

int main() {
    std::cout << "operation\t\tAMatrix\t\tEigen\t\tUblas\t\tAtlas" << std::endl;
    CompareAccessTime();
    CompareAssignTime();
    return 0;
}
