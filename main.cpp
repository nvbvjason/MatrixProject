#include "Matrix.hpp"
#include "Timer.hpp"

int main()
{
    int32_t size = 1500;
    auto* jason = new MyMatrix::Matrix{size, size};
    auto* bla = new MyMatrix::Matrix{size, size};
    {
        Timer timer;
        *jason * *bla;
    }
}
