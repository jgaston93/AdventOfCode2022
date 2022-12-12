#ifndef ADD_OPERATION_HPP
#define ADD_OPERATION_HPP

#include "Operation.hpp"

class AddOperation : Operation
{
    public:
        AddOperation(unsigned long long int value);
        ~AddOperation();
        virtual unsigned long long int PerformOperation(unsigned long long int input);
};

#endif // ADD_OPERATION_HPP