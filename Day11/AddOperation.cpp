#include "AddOperation.hpp"


AddOperation::AddOperation(int value) : Operation(value)
{
}

AddOperation::~AddOperation()
{
}

int AddOperation::PerformOperation(int input)
{
    return m_value + input;
}
