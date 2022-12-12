#ifndef BIG_INT_HPP
#define BIG_INT_HPP

class BigInt
{
    public:
        BigInt();
        ~BigInt();

        unsigned long long int GetHigh();
        unsigned long long int GetLow();
        void SetHigh(unsigned long long int);
        void SetLow(unsigned long long int);

        BigInt operator+(BigInt&);
        BigInt operator*(BigInt&);
        BigInt operator%(BigInt&);
        BigInt operator==(BigInt&);

    private:
        unsigned long long int high;
        unsigned long long int low;
};

#endif // BIG_INT_HPP