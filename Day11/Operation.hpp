#ifndef OPERATION_HPP
#define OPERATION_HPP

class Operation
{
    public:
        Operation(unsigned long long int value);
        ~Operation();
        virtual unsigned long long int PerformOperation(unsigned long long int input);

    protected:
        unsigned long long int m_value;
};

#endif // OPERATION_HPP