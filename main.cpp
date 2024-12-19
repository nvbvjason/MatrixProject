#include <iostream>

#include "Matrix.hpp"
#include "Timer.hpp"

int main()
{
    MyMatrix::Matrix matrix(1000, 1000);
    MyMatrix::Matrix matrix2(1000, 1000);
    matrix.populate_random(0.0, 1.0);
    matrix2.populate_random(0.0, 1.0);
    {
        Timer timer;
        MyMatrix::Matrix matrix3 = matrix * matrix2;
    }
}