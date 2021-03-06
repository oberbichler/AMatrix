#pragma once

// A matrix Library to be simple and fast
#include <cmath>
#include <limits>
#include "matrix_storage.h"
#include "matrix_iterator.h"

namespace AMatrix {

template <typename TDataType, std::size_t TSize1, std::size_t TSize2>
class Matrix : public MatrixExpression<Matrix<TDataType, TSize1, TSize2>,
                   row_major_access>,
               public MatrixStorage<TDataType, TSize1, TSize2> {
   public:
    using data_type = TDataType;
    using base_type = MatrixStorage<TDataType, TSize1, TSize2>;
    using base_type::at;
    using base_type::data;
    using base_type::size;
    using base_type::size1;
    using base_type::size2;
    
    using iterator = RandomAccessIterator<TDataType>;
    using const_iterator = RandomAccessIterator<const TDataType>;


    Matrix() {}

    explicit Matrix(std::size_t TheSize1, std::size_t TheSize2)
        : base_type(TheSize1, TheSize2) {}

    Matrix(Matrix const& Other) : base_type(Other) {}

    Matrix(Matrix&& Other) : base_type(Other) {}

    template <typename TExpressionType, std::size_t TCategory>
    explicit Matrix(MatrixExpression<TExpressionType, TCategory> const& Other)
        : base_type(Other) {}

    template <typename TOtherMatrixType>
    explicit Matrix(TOtherMatrixType const& Other) : base_type(Other) {}

    explicit Matrix(std::initializer_list<TDataType> InitialValues)
        : base_type(InitialValues) {}
	 
    template <typename TExpressionType, std::size_t TCategory>
    Matrix& operator=(
        MatrixExpression<TExpressionType, TCategory> const& Other) {
        base_type::operator=(Other);
        return *this;
    }

    template <typename TOtherMatrixType>
    Matrix& operator=(TOtherMatrixType const& Other) {
        base_type::operator=(Other);
        return *this;
    }

    Matrix& operator=(Matrix const& Other) {
        base_type::operator=(Other);
        return *this;
    }

    Matrix& operator=(Matrix&& Other) {
        base_type::operator=(Other);
        return *this;
    }

    friend bool operator==(Matrix const& First, Matrix const& Second) {
        for (std::size_t i = 0; i < First.size(); i++)
            if (First.data()[i] != Second.data()[i])
                return false;
        return true;
    }

    template <typename TExpressionType, std::size_t TCategory>
    Matrix& operator+=(
        MatrixExpression<TExpressionType, TCategory> const& Other) {
        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                at(i, j) += Other.expression()(i, j);

        return *this;
    }

    template <typename TExpressionType>
    Matrix& operator+=(
        MatrixExpression<TExpressionType, row_major_access> const& Other) {
        for (std::size_t i = 0; i < size(); i++)
            at(i) += Other.expression()[i];

        return *this;
    }

    template <typename TExpressionType, std::size_t TCategory>
    Matrix& operator-=(
        MatrixExpression<TExpressionType, TCategory> const& Other) {
        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                at(i, j) -= Other.expression()(i, j);

        return *this;
    }

    template <typename TExpressionType>
    Matrix& operator-=(
        MatrixExpression<TExpressionType, row_major_access> const& Other) {
        for (std::size_t i = 0; i < size(); i++)
            at(i) -= Other.expression()[i];

        return *this;
    }

    Matrix& operator*=(data_type TheValue) {
        for (std::size_t i = 0; i < size(); i++)
            at(i) *= TheValue;

        return *this;
    }

    Matrix& operator/=(data_type TheValue) {
        auto inverse_of_value = 1.00 / TheValue;
        for (std::size_t i = 0; i < size(); i++)
            at(i) *= inverse_of_value;

        return *this;
    }

    MatrixUnaryMinusExpression<Matrix> operator-() const {
        return MatrixUnaryMinusExpression<Matrix>(*this);
    }

    void resize(std::size_t NewSize1, std::size_t NewSize2) {
        base_type::resize(NewSize1, NewSize2);
    }

    void resize(std::size_t NewSize) { base_type::resize(NewSize); }

    void swap(Matrix& Other){
        base_type::swap(Other);
    }

    iterator begin() { return iterator(data()); }

    iterator end() { return iterator(data() + size()); }

    const_iterator begin() const { return const_iterator(data()); }

    const_iterator end() const { return const_iterator(data() + size()); }

    template <typename TExpressionType>
    data_type dot(
        MatrixExpression<TExpressionType, row_major_access> const& Other)
        const {
        data_type result = data_type();
        for (std::size_t i = 0; i < size(); ++i) {
            result += at(i) * Other.expression()[i];
        }
        return result;
    }

    data_type squared_norm() const { return dot(*this); }

    data_type norm() const { return std::sqrt(dot(*this)); }

    void normalize() {
        auto the_norm = norm();
        if (the_norm > std::numeric_limits<data_type>::epsilon()) {
            const auto norm_inverse = 1.0 / the_norm;
            for (std::size_t i = 0; i < size(); ++i) {
                at(i) *= norm_inverse;
            }
        }
    }

    Matrix& noalias() { return *this; }

    TransposeMatrix<Matrix<TDataType, TSize1, TSize2>> transpose() {
        return TransposeMatrix<Matrix<TDataType, TSize1, TSize2>>(*this);
    }
};

template <typename TDataType, std::size_t TSize1, std::size_t TSize2>
bool operator!=(Matrix<TDataType, TSize1, TSize2> const& First,
    Matrix<TDataType, TSize1, TSize2> const& Second) {
    return !(First == Second);
}

/// output stream function
template <typename TDataType, std::size_t TSize1, std::size_t TSize2>
inline std::ostream& operator<<(std::ostream& rOStream,
    Matrix<TDataType, TSize1, TSize2> const& TheMatrix) {
    rOStream << '{';
    for (std::size_t i = 0; i < TheMatrix.size1(); i++) {
        for (std::size_t j = 0; j < TheMatrix.size2(); j++)
            rOStream << TheMatrix(i, j) << ',';
        rOStream << '\n';
    }
    rOStream << '}';

    return rOStream;
}

}  // namespace AMatrix
