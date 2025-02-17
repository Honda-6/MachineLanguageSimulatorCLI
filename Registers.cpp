#include "Registers.h"

Register_Address::Register_Address()
    : content{} {}

unsigned char Register_Address::get_address() const
{
    return this->location;
}
unsigned char Register_Address::get_content() const
{
    return this->content;
}

void Register_Address::set_address(unsigned char x)
{
    this->location = x;
}
void Register_Address::set_content(const char *Hexbyte)
{
    unsigned char result{};
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
    this->content = result;
}

void Register_Address::set_content(unsigned char data)
{
    this->content = data;
}

void Register_Address::clear()
{
    this->content = 0;
}

Register_Address &Register_Address::operator=(const Register_Address &ra)
{
    if (this == &ra || this->location == ra.location)
        return *this;

    this->content = ra.content;
    return *this;
}

Register_Address &Register_Address::operator=(Register_Address &&ra)
{
    this->content = ra.content;
    return *this;
}
unsigned char Register_Address::operator&(const Register_Address &ra)
{
    return (this->content & ra.content);
}
unsigned char Register_Address::operator|(const Register_Address &ra)
{
    return (this->content | ra.content);
}
unsigned char Register_Address::operator^(const Register_Address &ra)
{
    return (this->content ^ ra.content);
}

CPU_Registers::CPU_Registers()
{
    for (unsigned char i{}; i < 16; ++i)
    {
        this->registers[i].set_address(i);
    }
}

CPU_Registers::CPU_Registers(const CPU_Registers &cr)
{
    for (unsigned char i{}; i < 16; ++i)
    {
        this->registers[i] = cr.registers[i];
    }
}

Register_Address &CPU_Registers::operator[](unsigned char i)
{
    return this->registers[i];
}

void CPU_Registers::clear_CPU()
{
    for(unsigned char i{}; i < 16; ++i)
    {
        this->registers[i].clear();
    }
}

std::ostream &operator<<(std::ostream &os, CPU_Registers &cr)
{
    os << std::setw(14) << "CPU"
       << "\n";
    os << "===========================\n";
    os << "Register" << std::setw(18) << "Content\n";
    os << "---------------------------\n";
    for (unsigned char i{}; i < 16; ++i)
    {
        os << to_hex(cr[i].get_address()) << std::setw(10) << '|' << std::setw(10) << to_hex(cr[i].get_content()) << '\n';
        os << "---------------------------\n";
    }
    return os;
}