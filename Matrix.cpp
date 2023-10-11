#include "Matrix.hpp"

namespace MyMatrix {

    Matrix::Matrix(size_t rows, size_t columns)
            : row_count {rows}, column_count {columns}
    {
        elem = new double* [row_count * column_count];
        for (size_t row = 0; row < row_count; row++) {
            elem[row] = new double[column_count];
        }
    }

    Matrix& Matrix::operator+(const Matrix& other)
    {
        if (row_count != other.rows() || column_count != other.columns())
            throw std::runtime_error("must be of equal size");
        for (size_t row = 0; row < row_count; row++) {
            for (size_t column = 0; column < column_count; column++) {
                elem[row][column] += other[row][column];
            }
        }
        return *this;
    }

    Matrix& Matrix::operator-(const Matrix& other)
    {
        if (row_count != other.rows() || column_count != other.columns())
            throw std::runtime_error("must be of equal size");
        for (size_t row = 0; row < row_count; row++) {
            for (size_t column = 0; column < column_count; column++) {
                elem[row][column] -= other[row][column];
            }
        }
        return *this;
    }

    Matrix& Matrix::operator*(const Matrix& other)
    {
        if (column_count != other.rows())
            throw std::runtime_error("row first must be equal to column count other");
        Matrix result = *new Matrix {row_count, other.columns()};
        for (size_t i = 0; i < row_count; i++) {
            for (size_t k = 0; k < other.columns(); k++) {
                double temp = 0;
                for (size_t j = 0; j < column_count; j++) {
                    temp += elem[i][j] * other[j][k];
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
                    elem[row][column] = 1;
                else
                    elem[row][column] = 0;
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
                elem[row][column] = dist(mt);
            }
        }
    }

    void Matrix::populate_sym()
    {
        for (size_t row = 0; row < row_count; row++) {
            for (size_t column = 0; column < column_count; column++) {
                elem[row][column] = (row + 1) + column;
            }
        }
    }

    void Matrix::populate()
    {
        for (size_t row = 0; row < row_count; row++) {
            for (size_t column = 0; column < column_count; column++) {
                elem[row][column] = (row + 1) + (column * column_count);
            }
        }
    }

    void Matrix::transpose()
    {
        if (row_count != column_count) {
            throw std::runtime_error("confused screaming");
        }
        for (size_t row = 0; row < row_count - 1; row++) {
            for (size_t column = row + 1; column < column_count; column++) {
                double temp = elem[row][column];
                elem[row][column] = elem[column][row];
                elem[column][row] = temp;
            }
        }
    };

    Matrix::~Matrix()
    {
        for (size_t row = 0; row < row_count; row++) {
            delete[] elem[row];
        }
        delete[] elem;
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