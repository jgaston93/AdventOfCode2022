#include "MultiplySelfOperation.hpp"


MultiplySelfOperation::MultiplySelfOperation(unsigned long long int value) : Operation(value)
{
}

MultiplySelfOperation::~MultiplySelfOperation()
{
}

unsigned long long int MultiplySelfOperation::PerformOperation(unsigned long long int input)
{
    return input * input;
}
