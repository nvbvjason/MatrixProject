#include <iostream>

#include "Timer.hpp"
#include "Matrix.hpp"

int main()
{
    int32_t size = 10;
    auto* jason = new MyMatrix::Matrix{size, size};
    auto* iden = new MyMatrix::Matrix{size, size};
    jason->populate_random(0, size);
    iden->populate_random(0, size);
    *jason * *iden;
}
