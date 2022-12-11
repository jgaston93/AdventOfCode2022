#include "MultiplyOperation.hpp"


MultiplyOperation::MultiplyOperation(int value) : Operation(value)
{
}

MultiplyOperation::~MultiplyOperation()
{
}

int MultiplyOperation::PerformOperation(int input)
{
    return m_value * input;
}
