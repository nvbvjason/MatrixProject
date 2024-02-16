#include <iostream>
#include "Matrix.hpp"

int main()
{
    auto* jason = new MyMatrix::Matrix{10, 10, true};
    jason->populate_random(0, 100);
    jason->gauss();
    std::cout << *jason;
}