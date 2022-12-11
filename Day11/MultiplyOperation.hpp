#ifndef MULTIPLY_OPERATION_HPP
#define MULTIPLY_OPERATION_HPP

#include "Operation.hpp"

class MultiplyOperation : Operation
{
    public:
        MultiplyOperation(int value);
        ~MultiplyOperation();
        virtual int PerformOperation(int input);
};

#endif // MULTIPLY_OPERATION_HPP