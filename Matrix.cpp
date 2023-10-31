#include <format>
#include <cassert>
#include "Matrix.hpp"

namespace MyMatrix {

    Matrix::Matrix(size_t rows, size_t columns)
            : row_count{rows}, column_count{columns}, elem{new double[rows * columns]}
    {
        assert(rows != 0 && columns != 0);
    }

    Matrix& Matrix::operator=(const MyMatrix::Matrix& other)
    {
        if (this == &other)
            return *this;
        row_count = other.rows();
        column_count = other.columns();
        delete[] elem;
        elem = new double[row_count * column_count];
        for (size_t row = 0; row < row_count; row++) {
            for (size_t column = 0; column < column_count; column++) {
                (*this)[row][column] = other[row][column];
            }
        }
        return *this;
    }

    Matrix Matrix::operator+(const Matrix& other) const
    {
        assert(row_count == other.rows() && column_count == other.columns());
        Matrix Mat{row_count, column_count};
        for (size_t row = 0; row < row_count; row++) {
            for (size_t column = 0; column < column_count; column++) {
                Mat[row][column] = (*this)[row][column] + other[row][column];
            }
        }
        return Mat;
    }

    Matrix Matrix::operator-(const Matrix& other) const
    {
        assert(row_count == other.rows() && column_count == other.columns());
        Matrix Mat{row_count, column_count};
        for (size_t row = 0; row < row_count; row++) {
            for (size_t column = 0; column < column_count; column++) {
                Mat[row][column] = (*this)[row][column] - other[row][column];
            }
        }
        return Mat;
    }

    Matrix Matrix::operator*(const Matrix& other) const
    {
        assert(column_count == other.rows());
        Matrix result{row_count, other.columns()};
        for (size_t i = 0; i < row_count; i++) {
            for (size_t k = 0; k < other.columns(); k++) {
                double temp = 0;
                for (size_t j = 0; j < column_count; j++) {
                    temp += (*this)[i][j] * other[j][k];
                }
                result[i][k] = temp;
            }
        }
        return result;
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
        for (size_t row = 0; row < row_count; row++) {
            for (size_t column = 0; column < column_count; column++) {
                (*this)[row][column] = dist(mt);
            }
        }
    }

    void Matrix::populate_sym()
    {
        for (size_t row = 0; row < row_count; row++) {
            for (size_t column = 0; column < column_count; column++) {
                (*this)[row][column] = (row + 1) + column;
            }
        }
    }

    void Matrix::populate()
    {
        for (size_t row = 0; row < row_count; row++) {
            for (size_t column = 0; column < column_count; column++) {
                (*this)[row][column] = (row + 1) + (column * column_count);
            }
        }
    }

    void Matrix::transpose()
    {

        assert(row_count == column_count);
        for (size_t row = 0; row < row_count - 1; row++) {
            for (size_t column = row + 1; column < column_count; column++) {
                double temp = (*this)[row][column];
                (*this)[row][column] = (*this)[row][column];
                (*this)[row][column] = temp;
            }
        }
    }

    std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
    {
        os << "-------------------------------------------------------------\n";
        for (size_t row = 0; row < matrix.rows(); row++) {
            for (size_t column = 0; column < matrix.columns(); column++) {
                os << matrix[row][column] << '\t';
            }
            os << '\n';
        }
        os << "-------------------------------------------------------------\n";
        return os;
    }
}