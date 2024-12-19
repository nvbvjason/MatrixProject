#include "Matrix.hpp"

#include <cassert>
#include <iomanip>
#include <stdexcept>
#include <random>
#include <cstring>

namespace MyMatrix {
Matrix::Matrix(const int32_t rows, const int32_t columns, const bool is_identity)
    : m_rows{rows}, m_columns{columns}, m_elem{new double[rows * columns]}
{
    assert(0 < rows && "Matrix initialization row smaller zero");
    assert(0 < columns && "Matrix initialization columns smaller zero");
    if (is_identity) {
        for (int32_t row = 0; row < rows; ++row)
            for (int32_t col = 0; col < columns; ++col) {
                if (row == col)
                    (*this)[row][col] = 1;
                else
                    (*this)[row][col] = 0;
            }
    }
}

Matrix::Matrix(const Matrix& other)
    : m_rows{other.m_rows}, m_columns{other.m_columns}, m_elem{new double[other.rows() * other.columns()]}
{
    for (int32_t row = 0; row < m_rows; row++)
        for (int32_t column = 0; column < m_columns; column++)
            (*this)[row][column] = other[row][column];
}

Matrix::Matrix(Matrix&& other) noexcept
    : m_rows{other.rows()}, m_columns{other.columns()}
{
    m_elem = other.get_matrix();
    other.m_elem = nullptr;
    other.m_rows = 0;
    other.m_columns = 0;
}

double Matrix::at(const int32_t row, const int32_t column) const
{
    if (row <= 0 || m_rows + 1 < row)
        throw std::invalid_argument("row out of range");
    if (column <= 0 || m_columns + 1 < column)
        throw std::invalid_argument("row out of range");
    return (*this)[row][column];
}

Matrix& Matrix::operator=(const Matrix& other)
{
    if (this == &other)
        return *this;
    if (m_rows != other.rows() || m_columns != other.columns()) {
        m_rows = other.rows();
        m_columns = other.columns();
        delete[] m_elem;
        m_elem = new double[m_rows * m_columns];
    }
    for (int32_t row = 0; row < m_rows; row++)
        for (int32_t column = 0; column < m_columns; column++)
            (*this)[row][column] = other[row][column];
    return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept
{
    if (this == &other)
        return *this;
    m_rows = other.rows();
    m_columns = other.columns();
    delete[] m_elem;
    m_elem = other.get_matrix();
    other.m_elem = nullptr;
    other.m_rows = 0;
    other.m_columns = 0;
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
    assert(m_rows == other.m_rows && "Matrix addition different row count");
    assert(m_columns == other.m_columns && "Matrix addition different column count");
    for (int32_t row = 0; row < m_rows; row++)
        for (int32_t column = 0; column < m_columns; column++)
            (*this)[row][column] += other[row][column];
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
    assert(m_rows == other.m_rows && "Matrix subtraction different row count");
    assert(m_columns == other.m_columns && "Matrix subtraction different column count");
    for (int32_t row = 0; row < m_rows; row++)
        for (int32_t column = 0; column < m_columns; column++)
            (*this)[row][column] -= other[row][column];
    return *this;
}

// change order for cachethrouput
Matrix& Matrix::operator*=(const Matrix& other)
{
    assert(m_columns == other.m_rows && "Matrix multiplication unaligned");
    auto* result = new Matrix{m_rows, other.columns()};
    memset(result->m_elem, 0, sizeof(double) * m_rows * other.m_columns);
    for (int32_t row = 0; row < m_rows; ++row)
        for (int32_t i = 0; i < m_columns; ++i)
            for (int32_t col = 0; col < other.m_columns; ++col)
                (*result)[row][col] += (*this)[row][i] * other[i][col];
    m_columns = other.columns();
    delete[] m_elem;
    m_elem = result->m_elem;
    result->m_elem = nullptr;
    result->~Matrix();
    return *this;
}

Matrix operator+(const Matrix& first, const Matrix& second)
{
    Matrix result = first;
    return result += second;
}

Matrix operator-(const Matrix& first, const Matrix& second)
{
    Matrix result = first;
    return result -= second;
}

    Matrix operator*(const Matrix& first, const Matrix& second)
{
    Matrix result = first;
    return result *= second;
}

Matrix Matrix::operator*(const double scala) const
{
    auto* result = new Matrix{*this};
    for (int32_t row = 0; row < m_rows; row++)
        for (int32_t column = 0; column < m_columns; column++)
            *result[row][column] *= scala;
    return *result;
}

void Matrix::identity()
{
    for (int32_t row = 0; row < m_rows; row++) {
        for (int32_t column = 0; column < m_columns; column++) {
            if (row == column)
                (*this)[row][column] = 1;
            else
                (*this)[row][column] = 0;
        }
    }
}

void Matrix::populate_random(const double low, const double high)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(low, high);
    for (int32_t row = 0; row < m_rows; row++)
        for (int32_t column = 0; column < m_columns; column++)
            (*this)[row][column] = dist(mt);
}

void Matrix::populate_sym()
{
    for (int32_t row = 0; row < m_rows; row++)
        for (int32_t column = 0; column < m_columns; column++)
            (*this)[row][column] = static_cast<double>(row + 1 + column);
}

void Matrix::populate()
{
    for (int32_t row = 0; row < m_rows; row++)
        for (int32_t column = 0; column < m_columns; column++)
            (*this)[row][column] = static_cast<double>(row + 1 + column * m_columns);
}

void Matrix::transpose()
{
    if (m_rows == m_columns) {
        for (int32_t row = 0; row < m_rows - 1; row++) {
            for (int32_t column = row + 1; column < m_columns; column++) {
                const double temp = (*this)[column][row];
                (*this)[column][row] = (*this)[row][column];
                (*this)[row][column] = temp;
            }
        }
        return;
    }
    auto* result = new Matrix{m_columns, m_rows};
    for (int32_t row = 0; row < result->rows() - 1; row++)
        for (int32_t column = 0; column < result->columns(); column++)
            (*result)[row][column] = (*this)[column][row];
    delete[] m_elem;
    m_rows = result->m_rows;
    m_columns = result->m_columns;
    m_elem = result->m_elem;
    result->~Matrix();
}

void Matrix::gauss()
{
    for (int32_t i = 0; i < m_rows - 1; ++i) {
        int32_t pivot = i;
        double pivotsize = (*this)[i][i];
        if (pivotsize < 0)
            pivotsize = -pivotsize;
        for (int32_t j = i + 1; j < m_rows; ++j) {
            double temp = (*this)[j][i];
            if (temp < 0)
                temp = -temp;
            if (pivotsize < temp)
                pivot = j;
            pivotsize = temp;
        }
        if (pivotsize == 0)
            return;
        if (pivot != i) {
            for (int32_t j = 0; j < m_rows; ++j) {
                const double temp = (*this)[i][j];
                (*this)[i][j] = (*this)[pivot][j];
                (*this)[pivot][j] = temp;
            }
        }
        for (int32_t row = i + 1; row < m_rows; ++row) {
            const double f = (*this)[row][i] / (*this)[i][i];
            for (int32_t col = 0; col < m_rows; ++col)
                (*this)[row][col] -= f * (*this)[i][col];
            (*this)[row][i] = 0.0;
        }
    }
}

void Matrix::swap_rows(const int32_t first, const int32_t second)
{
    auto* temp = new double[m_columns];
    for (int32_t column = 0; column < m_columns; column++)
        temp[column] = (*this)[first][column];
    for (int32_t column = 0; column < m_columns; column++)
        (*this)[first][column] = (*this)[second][column];
    for (int32_t column = 0; column < m_columns; column++)
        (*this)[second][column] = temp[column];
    delete[] temp;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
    os << "-------------------------------------------------------------\n";
    for (int32_t row = 0; row < matrix.rows(); row++) {
        for (int32_t column = 0; column < matrix.columns(); column++)
            os << std::setw(8) << std::setfill(' ') << std::fixed << std::setprecision(3) << matrix[row][column] << ' ';
        os << '\n';
    }
    os << "-------------------------------------------------------------\n";
    return os;
}

bool operator==(const Matrix& a, const Matrix& b)
{
    if (&a == &b)
        return true;
    if (a.rows() != b.rows() || a.columns() != b.columns())
        return false;
    for (int32_t row = 0; row < a.rows() - 1; row++)
        for (int32_t column = 0; column < a.columns(); column++)
            if (a[row][column] != b[column][row])
                return false;
    return true;
}

bool operator!=(const Matrix& a, const Matrix& b)
{
    return !(a == b);
}
}
