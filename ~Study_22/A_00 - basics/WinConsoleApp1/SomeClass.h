#pragma once

#include <iostream>

class SomeClass
{
private:
    int m_value1{};
    double m_value2{};
    char m_value3{};

public:
    SomeClass();

    void print();
};