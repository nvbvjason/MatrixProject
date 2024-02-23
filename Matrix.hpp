#pragma once

#ifndef MATRIXPROJECT_MATRIX_HPP
#define MATRIXPROJECT_MATRIX_HPP

#include <cstdint>
#include <ostream>

namespace MyMatrix {

class Matrix {
    // DATA
    int32_t m_rows;
    int32_t m_columns;
    double* m_elem;
public:
    // CREATORS
    Matrix(int32_t rows, int32_t columns, bool is_identity = false);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    ~Matrix() { delete[]m_elem; }

    // MANIPULATORS
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other) noexcept;
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    double* operator[](const int32_t index) { return m_elem + m_columns * index; }
    void identity();
    void populate_random(double low, double high);
    void populate_sym();
    void populate();
    void transpose();
    void gauss();

    // ACCESSORS
    Matrix operator*(double scala) const;
    [[nodiscard]] int32_t rows() const { return m_rows; }
    [[nodiscard]] int32_t columns() const { return m_columns; }
    [[nodiscard]] double at(int32_t row, int32_t column) const;
    [[nodiscard]] double* get_matrix() const { return m_elem; }
    [[nodiscard]] const double* operator[](int32_t index) const { return m_elem + m_columns * index; }
    double operator()(const int32_t row, const int32_t column) { return (*this)[row][column]; }
private:
    void swap_rows(int32_t first, int32_t second);
};

Matrix operator+(const Matrix& other);
Matrix operator-(const Matrix& other);
Matrix operator*(const Matrix& other);


std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
bool operator==(const Matrix& a, const Matrix& b);
bool operator!=(const Matrix& a, const Matrix& b);
}

#endif //MATRIXPROJECT_MATRIX_HPP