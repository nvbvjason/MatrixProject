//
// Created by jason on 12/09/2023.
//

#ifndef MATRIXPROJECT_MATRIX_HPP
#define MATRIXPROJECT_MATRIX_HPP

#include <stdexcept>
#include <cstddef>

class Matrix {
private:
    double** elem;
    size_t row_count;
    size_t column_count;
public:
    explicit Matrix(size_t rows = 1, size_t columns = 1);

    [[nodiscard]] size_t rows() const { return row_count; }
    [[nodiscard]] size_t columns() const { return column_count; }

};


#endif //MATRIXPROJECT_MATRIX_HPP
