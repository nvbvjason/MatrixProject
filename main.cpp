#include <iostream>
#include "Matrix.hpp"

int main()
{
    auto* jason = new MyMatrix::Matrix{10, 10, 5};
    auto* la = new MyMatrix::Matrix{10, 10, 5};
    auto* bla = new MyMatrix::Matrix{10, 10, 0};
    *bla = *jason * *la;
    std::cout << *bla;
}