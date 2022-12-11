#ifndef OPERATION_HPP
#define OPERATION_HPP

class Operation
{
    public:
        Operation(int value);
        ~Operation();
        virtual int PerformOperation(int input);

    protected:
        int m_value;
};

#endif // OPERATION_HPP