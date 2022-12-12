#include "Operation.hpp"


Operation::Operation(unsigned long long int value) : m_value(value)
{
}

Operation::~Operation()
{
}

unsigned long long int Operation::PerformOperation(unsigned long long int input)
{
    (void)input;
    return 0;
}