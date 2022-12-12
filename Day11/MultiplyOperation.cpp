#include "MultiplyOperation.hpp"


MultiplyOperation::MultiplyOperation(unsigned long long int value) : Operation(value)
{
}

MultiplyOperation::~MultiplyOperation()
{
}

unsigned long long int MultiplyOperation::PerformOperation(unsigned long long int input)
{
    return m_value * input;
}
