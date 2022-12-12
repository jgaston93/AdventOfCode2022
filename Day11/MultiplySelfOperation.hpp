#ifndef MULTIPLY_SELF_OPERATION_HPP
#define MULTIPLY_SELF_OPERATION_HPP

#include "Operation.hpp"

class MultiplySelfOperation : Operation
{
    public:
        MultiplySelfOperation(unsigned long long int value);
        ~MultiplySelfOperation();
        virtual unsigned long long int PerformOperation(unsigned long long int input);
};

#endif // MULTIPLY_SELF_OPERATION_HPP