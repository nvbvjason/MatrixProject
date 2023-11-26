#pragma once

#ifndef MATRIXPROJECT_MATRIX_HPP
#define MATRIXPROJECT_MATRIX_HPP

#include <cstddef>
#include <random>
#include <iostream>


namespace MyMatrix {

class Matrix {
    // DATA
    size_t row_count;
    size_t column_count;
    double* elem;
public:
    // CREATORS
    explicit Matrix(size_t rows = 1, size_t columns = 1);
    Matrix(size_t rows, size_t columns, double value);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    ~Matrix() { delete[]elem; }

    // MANIPULATORS
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other) noexcept;
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scala) const;
    void identity();
    void populate_random();
    void populate_sym();
    void populate();
    void transpose();
    void Gauss();

    // ACCESSORS
    [[nodiscard]] size_t rows() const { return row_count; }
    [[nodiscard]] size_t columns() const { return column_count; }
    [[nodiscard]] double at(size_t row, size_t column) const;
    double* get_matrix() { return elem; }
    double* operator[](size_t index) { return elem + column_count * index; }
    const double* operator[](size_t index) const { return elem + column_count * index; }
    double operator()(size_t row, size_t column) { return (*this)[row][column]; }
private:
    void set_rows(size_t rows) { row_count = rows; }
    void set_columns(size_t columns) { column_count = columns; }
    void set_elem(double* ptr) { elem = ptr; }
    void swap_rows(size_t first, size_t second);
};

std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
bool operator==(const Matrix& a, const Matrix& b);
bool operator!=(const Matrix& a, const Matrix& b);
}

#endif //MATRIXPROJECT_MATRIX_HPP