#include <iostream>
#include <string>
#include "my_matrix.hpp"
#include <gtest/gtest.h>

int main()
{
    size_t rows = 5;
    size_t cols = 3;

    Matrix m(rows, cols);

    assert(m.getRows() == 5);
    assert(m.getColumns() == 3);

    m[1][2] = 5; // строка 1, колонка 2
    //double x = m[4][1];

    m *= 3; // умножение на число

    Matrix m1(rows, cols);

    if (m1 != m)
    {
        std::cout << "not equal" << std::endl;
    }
    Matrix m2 = m1 + m;
    std::cout << m2 << std::endl;    
    return 0;
}