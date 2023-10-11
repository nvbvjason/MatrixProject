//
// Created by jason on 12/09/2023.
//

#include "Matrix.hpp"

Matrix::Matrix(size_t rows, size_t columns)
        : row_count {rows}, column_count {columns}
{
    elem = new double* [row_count * column_count];
    if (!elem)
        throw std::runtime_error("can't construct matrix");
    for (size_t row = 0; row < row_count; row++) {
        elem[row] = new double[column_count];
    }
}