#include "Matrix.hpp"
#include <vector>
#include <cassert>
#include <stdexcept>


namespace MyMatrix {

Matrix::Matrix(size_t rows, size_t columns)
        : row_count{rows}, column_count{columns}, elem{new double[rows * columns]}
{
    assert(0 < rows && 0 < columns);
}

Matrix::Matrix(size_t rows, size_t columns, double value)
        : row_count{rows}, column_count{columns}, elem{new double[rows * columns]}
{
    assert(0 < rows && 0 < columns);
    for (size_t row = 0; row < row_count; row++)
        for (size_t column = 0; column < column_count; column++)
            (*this)[row][column] = value;
}

Matrix::Matrix(const Matrix& other)
        : row_count{other.rows()}, column_count{other.columns()}, elem{new double[other.rows() * other.columns()]}
{
    for (size_t row = 0; row < row_count; row++)
        for (size_t column = 0; column < column_count; column++)
            (*this)[row][column] = other[row][column];
}

Matrix::Matrix(Matrix&& other) noexcept
        : row_count{other.rows()}, column_count{other.columns()}
{
    elem = other.get_matrix();
    other.set_elem(nullptr);
    other.set_rows(0);
    other.set_columns(0);
}

double Matrix::at(size_t row, size_t column) const
{
    if (row <= 0 || row_count + 1 < row)
        throw std::invalid_argument("row out of range");
    if (column <= 0 || column_count + 1 < column)
        throw std::invalid_argument("row out of range");
    return (*this)[row][column];
}

Matrix& Matrix::operator=(const Matrix& other)
{
    if (this == &other)
        return *this;
    if (row_count != other.rows() || column_count != other.columns()) {
        row_count = other.rows();
        column_count = other.columns();
        delete[] elem;
        elem = new double[row_count * column_count];
    }
    for (size_t row = 0; row < row_count; row++)
        for (size_t column = 0; column < column_count; column++)
            (*this)[row][column] = other[row][column];
    return *this;
}

Matrix& Matrix::operator=(MyMatrix::Matrix&& other) noexcept
{
    if (this == &other)
        return *this;
    row_count = other.rows();
    column_count = other.columns();
    delete[] elem;
    elem = other.get_matrix();
    other.set_elem(nullptr);
    other.set_rows(0);
    other.set_columns(0);
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
    assert(row_count == other.rows());
    assert(column_count == other.columns());
    for (size_t row = 0; row < row_count; row++)
        for (size_t column = 0; column < column_count; column++)
            (*this)[row][column] += other[row][column];
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
    assert(row_count == other.rows());
    assert(column_count == other.columns());
    for (size_t row = 0; row < row_count; row++)
        for (size_t column = 0; column < column_count; column++)
            (*this)[row][column] -= other[row][column];
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
    assert(column_count == other.rows());
    auto* result = new Matrix{row_count, other.columns(), 0.0};
    for (size_t row = 0; row < row_count; row++)
        for (size_t column = 0; column < other.columns(); column++)
            for (size_t j = 0; j < column_count; j++)
                (*result)[row][column] += (*this)[row][j] * other[j][column];
    column_count = other.columns();
    delete[] elem;
    elem = result->elem;
    result->elem = nullptr;
    result->~Matrix();
    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const
{
    Matrix result = *this;
    return result += other;
}

Matrix Matrix::operator-(const Matrix& other) const
{
    Matrix result = *this;
    return result -= other;
}

Matrix Matrix::operator*(const Matrix& other) const
{
    Matrix result = *this;
    return result *= other;
}

Matrix Matrix::operator*(const double scalar) const
{
    auto* result = new Matrix{*this};
    for (size_t row = 0; row < row_count; row++)
        for (size_t column = 0; column < column_count; column++)
            *result[row][column] *= scalar;
    return *result;
}

void Matrix::identity()
{
    for (size_t row = 0; row < row_count; row++) {
        for (size_t column = 0; column < column_count; column++) {
            if (row == column)
                (*this)[row][column] = 1;
            else
                (*this)[row][column] = 0;
        }
    }
}

void Matrix::populate_random()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-10, 10.0);
    for (size_t row = 0; row < row_count; row++)
        for (size_t column = 0; column < column_count; column++)
            (*this)[row][column] = dist(mt);
}

void Matrix::populate_sym()
{
    for (size_t row = 0; row < row_count; row++)
        for (size_t column = 0; column < column_count; column++)
            (*this)[row][column] = static_cast<double>(row + 1 + column);
}

void Matrix::populate()
{
    for (size_t row = 0; row < row_count; row++)
        for (size_t column = 0; column < column_count; column++)
            (*this)[row][column] = static_cast<double>(row + 1 + column * column_count);
}

void Matrix::transpose()
{
    if (row_count == column_count) {
        for (size_t row = 0; row < row_count - 1; row++) {
            for (size_t column = row + 1; column < column_count; column++) {
                const double temp = (*this)[column][row];
                (*this)[column][row] = (*this)[row][column];
                (*this)[row][column] = temp;
            }
        }
        return;
    }
    auto* result = new Matrix{column_count, row_count};
    for (size_t row = 0; row < result->rows() - 1; row++)
        for (size_t column = 0; column < result->columns(); column++)
            (*result)[row][column] = (*this)[column][row];
    delete[] elem;
    row_count = result->rows();
    column_count = result->columns();
    elem = result->get_matrix();
    result->~Matrix();
}

void Matrix::Gauss()
{
    const size_t height = row_count;
    for (size_t k = 0; k < column_count; k++) {

        std::vector<std::vector<size_t>> to_sort;
        std::vector<size_t> temp_vi;

        // count how many 0 start each row
        for (size_t row = k; row < height; row++) {
            int counter = 0;
            for (size_t column = 0; column < height; column++) {
                if ((*this)[row][column] == 0)
                    counter++;
                else
                    break;
            }
            temp_vi.push_back(row);
            temp_vi.push_back(counter);
            to_sort.push_back(temp_vi);
            temp_vi.clear();
        }

        // swap
//        for (size_t i = k; i < to_sort.size(); i++) {
//            bool swap = false;
//            size_t size_t_temp = to_sort[i][i];
//            size_t row_index_to_swap = 0;
//            std::vector<double> to_swap;
//            for (size_t j = i; j < to_sort.size(); j++) {
//                if (to_sort[j][i] < size_t_temp) {
//                    to_swap
//                }
//            }
//        }
    }
}

void Matrix::swap_rows(size_t first, size_t second)
{
    auto* temp = new double[column_count];
    for (size_t column = 0; column < column_count; column++)
        temp[column] = (*this)[first][column];
    for (size_t column = 0; column < column_count; column++)
        (*this)[first][column] = (*this)[second][column];
    for (size_t column = 0; column < column_count; column++)
        (*this)[second][column] = temp[column];
    delete[] temp;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
    os << "-------------------------------------------------------------\n";
    for (size_t row = 0; row < matrix.rows(); row++) {
        for (size_t column = 0; column < matrix.columns(); column++)
            os << matrix[row][column] << '\t';
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
    for (size_t row = 0; row < a.rows() - 1; row++)
        for (size_t column = 0; column < a.columns(); column++)
            if (a[row][column] != b[column][row])
                return false;
    return true;
}

bool operator!=(const Matrix& a, const Matrix& b)
{
    return !(a == b);
}

}