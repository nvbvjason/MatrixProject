#include <iostream>
#include "Matrix.hpp"

int main()
{
    MyMatrix::Matrix jason {10, 10};
    MyMatrix::Matrix stuff {10, 10};
    stuff.identity();
    jason.populate();
    std::cout << jason;
    std::cout << jason * stuff;
}