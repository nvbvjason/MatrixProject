#pragma once

#ifndef MATRIXPROJECT_MATRIX_HPP
#define MATRIXPROJECT_MATRIX_HPP

#include <stdexcept>
#include <cstddef>
#include <random>
#include <iostream>
#include <vector>
#include <cassert>

namespace MyMatrix {

    class Matrix {
    private:
        double* elem;
        size_t row_count;
        size_t column_count;
    public:
        explicit Matrix(size_t rows = 1, size_t columns = 1);
        Matrix(const Matrix& other);
        Matrix(Matrix&& other) noexcept;

        [[nodiscard]] size_t rows() const { return row_count; }
        [[nodiscard]] size_t columns() const { return column_count; }
        double* get_matrix() { return elem; }
        double* operator[](size_t index) { return row(index); }
        const double* operator[](size_t index) const { return row(index); }
        double operator()(size_t row, size_t column) { return (*this)[row][column]; }
        double at(size_t row, size_t column);

        Matrix& operator=(const Matrix& other);
        Matrix& operator=(Matrix&& other) noexcept;
        Matrix& operator+=(const Matrix& other);
        Matrix& operator-=(const Matrix& other);

        Matrix operator+(const Matrix& other) const;
        Matrix operator-(const Matrix& other) const;
        Matrix operator*(const Matrix& other) const;
        Matrix operator*(double scala) const;

        void set_rows(size_t rows) { row_count = rows; }
        void set_columns(size_t columns) { column_count = columns; }
        void set_elem(double* ptr) { elem = ptr; }

        void identity();
        void populate_random();
        void populate_sym();
        void populate();
        void transpose();
        void Gauss();

        ~Matrix() { delete[]elem; }
    private:
        double* row(size_t index) { return elem + column_count * index; }
        [[nodiscard]] const double* row(size_t index) const { return elem + column_count * index; }

        void swap_rows(size_t first, size_t second);
    };

    std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
}

#endif //MATRIXPROJECT_MATRIX_HPP