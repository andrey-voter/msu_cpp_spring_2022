#include <iostream>
#include <string>
#include <typeinfo>
#include <gtest/gtest.h>

#include "BigInt.hpp"



int main()
{
    custom::BigInt A("123456789987654321123456789987654321");
    custom::BigInt B("-300");
    std::cout << A << std::endl;
    std::cout << B << std::endl;
    custom::BigInt C = A + B;
    std::cout << C << std::endl;
    return 0;
}