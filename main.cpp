#include <iostream>

#include "Matrix.hpp"
#include "Timer.hpp"

int main()
{
    const int rows = 1024;
    const int cols = 1024;
    MyMatrix::Matrix matrix(rows, cols);
    MyMatrix::Matrix matrix2(rows, cols);
    matrix.populate_random(0.0, 1.0);
    matrix2.populate_random(0.0, 1.0);
    {
        Timer timer;
        MyMatrix::Matrix matrix3 = matrix * matrix2;
    }
}