#include "BigInt.hpp"


BigInt::BigInt() : high(0), low(0)
{

}

BigInt::~BigInt()
{

}

unsigned long long int BigInt::GetHigh()
{
    return high;
}

unsigned long long int BigInt::GetLow()
{
    return low;
}

void BigInt::SetHigh(unsigned long long int a)
{
    high = a;
}

void BigInt::SetLow(unsigned long long int a)
{
    low = a;
}

BigInt BigInt::operator+(BigInt& a)
{
    BigInt value;
    
    unsigned long long int a_high = a.GetHigh();
    unsigned long long int a_low = a.GetLow();

    unsigned long long int temp_high = 0;
    unsigned long long int temp_low = 0;

    if(low + a_low < low)
    {
        overflow = low + a_low;

    }
    else
    {
        value.SetLow(low + a_low);
    }
    value.SetHigh(high + a_high + overflow);

    return value;
}

BigInt BigInt::operator*(BigInt& a)
{

}

BigInt BigInt::operator%(BigInt& a)
{

}

BigInt BigInt::operator==(BigInt& a)
{

}
