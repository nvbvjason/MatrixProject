#ifndef MATRIXPROJECT_MATRIX_HPP
#define MATRIXPROJECT_MATRIX_HPP

#include <stdexcept>
#include <cstddef>
#include <random>
#include <iostream>

namespace MyMatrix{

    class Matrix {
    private:
        double** elem;
        size_t row_count;
        size_t column_count;
    public:
        explicit Matrix(size_t rows = 1, size_t columns = 1);

        [[nodiscard]] size_t rows() const { return row_count; }
        [[nodiscard]] size_t columns() const { return column_count; }
        double* operator[](size_t row) { return elem[row]; }
        const double* operator[](size_t row) const { return elem[row]; }

        Matrix operator+(const Matrix& other) const;
        Matrix operator-(const Matrix& other) const;
        Matrix operator*(const Matrix& other) const;

        void identity();
        void populate_random();
        void populate_sym();
        void populate();
        void transpose();
        ~Matrix();
    };

std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
}

#endif //MATRIXPROJECT_MATRIX_HPP
