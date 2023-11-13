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