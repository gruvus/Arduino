#include "SomeClass.h"


SomeClass::SomeClass() 
    : m_value1{ 1 }
    , m_value2{ 2.2 }
    , m_value3{ 'c' } // Initialize our member variables
{
    // No need for assignment here
}

void SomeClass::print()
{
    std::cout << "SomeClass(" << m_value1 << ", " << m_value2 << ", " << m_value3 << ")\n";
}

