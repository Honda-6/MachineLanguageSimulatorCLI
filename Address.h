#pragma once
#include<iostream>
#include<iomanip>
class Address
{
protected:
    unsigned char location;
public:
    Address(){location = 0;};
    virtual unsigned char get_address() const = 0;
    virtual void set_address(unsigned char x) = 0;
    virtual ~Address() = default;
};
std::string to_hex(unsigned short val);
float to_float(unsigned char bitpattern)
{
    char exponent = ((bitpattern >> 4) & 7) - 4, bit = 8;
    bool negative = bitpattern & 128;
    float result{};
    while (bit)
    {
        if (exponent > 0)
        {
            result += ((bit & bitpattern) != 0) << (exponent - 1);
        }
        else
        {
            if (bit & bitpattern)
            {
                result += 1.0 / (((bit & bitpattern) != 0) << ((exponent * -1) + 1));
            }
        }
        exponent--;
        bit >>= 1;
    }
    result = ((negative) ? (-result) : result);
    return result;
}
void to_binary(unsigned char x, unsigned char eight = 8)
{
    if (!eight)
    {
        return;
    }
    to_binary(x / 2, eight - 1);
    std::cout << x % 2;
}