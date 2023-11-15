#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
class Address
{
protected:
    unsigned char location;

public:
    Address() { location = 0; };
    virtual unsigned char get_address() const = 0;
    virtual void set_address(unsigned char x) = 0;
    virtual ~Address() = default;
};
std::string to_hex(unsigned short val)
{
    std::string Hexa{"  "};
    if ((val & 15) >= 10)
    {
        Hexa[1] = (val & 15) - 10 + 'A';
    }
    else
    {
        Hexa[1] = (val & 15) + '0';
    }
    val >>= 4;
    if ((val & 15) >= 10)
    {
        Hexa[0] = (val & 15) - 10 + 'A';
    }
    else
    {
        Hexa[0] = (val & 15) + '0';
    }
    return Hexa;
}
char to_hexa_digit(unsigned char value)
{
    char Hexa{};
    if (value >= 10)
    {
        Hexa = (value%10) + 'A';
    }
    else
    {
        Hexa = value + 48;
    }
    return Hexa;
}
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
unsigned char to_decimal(const char *Hexbyte)
{
    unsigned char result{};
    if (Hexbyte)
    {
        char size{}, i{};
        while (Hexbyte[size])
        {
            ++size;
        }
        i = (--size);
        while (i > -1)
        {
            if ((Hexbyte[i] >= 65 && Hexbyte[i] <= 90))
            {
                result += (10 + (Hexbyte[i] - 65)) * ((size - i == 0) ? 1 : 16);
            }
            else if (Hexbyte[i] >= 97 && Hexbyte[i] <= 122)
            {
                result += (10 + (Hexbyte[i] - 97)) * ((size - i == 0) ? 1 : 16);
            }
            else
            {
                result += (Hexbyte[i] - 48) * ((size - i == 0) ? 1 : 16);
            }
            i--;
        }
    }
    return result;
}
unsigned char to_decimal(char Hexbyte)
{
    if (Hexbyte >= 65)
    {
        return Hexbyte - 65 + 10;
    }
    else
    {
        return Hexbyte - 48;
    }
}