#include "srp.hpp"
#include <iostream>

int main()
{
    Srp calculator;
    int a = 4, b = 7;
    std::cout << a << " + " << b << " = " << calculator.add(a, b) << '\n';
}
