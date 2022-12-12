#include "AddOperation.hpp"


AddOperation::AddOperation(unsigned long long int value) : Operation(value)
{
}

AddOperation::~AddOperation()
{
}

unsigned long long int AddOperation::PerformOperation(unsigned long long int input)
{
    return m_value + input;
}
