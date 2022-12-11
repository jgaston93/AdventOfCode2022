#ifndef ADD_OPERATION_HPP
#define ADD_OPERATION_HPP

#include "Operation.hpp"

class AddOperation : Operation
{
    public:
        AddOperation(int value);
        ~AddOperation();
        virtual int PerformOperation(int input);
};

#endif // ADD_OPERATION_HPP