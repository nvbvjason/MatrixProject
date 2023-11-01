#include <iostream>
#include "Matrix.hpp"

int main()
{
    MyMatrix::Matrix jason {10, 10};
    jason.populate();
    std::cout << jason;
}