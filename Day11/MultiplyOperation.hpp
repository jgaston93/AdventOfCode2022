#ifndef MULTIPLY_OPERATION_HPP
#define MULTIPLY_OPERATION_HPP

#include "Operation.hpp"

class MultiplyOperation : Operation
{
    public:
        MultiplyOperation(unsigned long long int value);
        ~MultiplyOperation();
        virtual unsigned long long int PerformOperation(unsigned long long int input);
};

#endif // MULTIPLY_OPERATION_HPP