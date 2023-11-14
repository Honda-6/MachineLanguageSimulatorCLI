#include"Memory.h"

Memory_Address::Memory_Address()
    : content{0} {}

unsigned char Memory_Address::get_address() const
{
    return this->location;
}
void Memory_Address::set_address(unsigned char x)
{
    this->location = x;
}
unsigned char Memory_Address::get_content() const
{
    return this->content;
}
void Memory_Address::set_content(const char* Hexbyte)
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

void Memory_Address::set_content(unsigned char data)
{
    this->content = data;
}

void Memory_Address::clear()
{
    this->content = 0;
}

Memory_Address &Memory_Address::operator=(const Memory_Address &m)
{
    if(this == &m || this->location== m.location)
        return *this;
    
    this->content = m.content;
    return *this;
}

Memory::Memory()
{
    for(unsigned short i{}; i < 256; ++i)
    {
        addresses[i].set_address(i);
    }
}
Memory::Memory(const Memory &m)
{
    for(unsigned short i{}; i < 256; ++i)
    {
        this->addresses[i] = m.addresses[i];
    }
}
Memory_Address &Memory::operator[](unsigned char i)
{
    return this->addresses[i];
}


void Memory::clear_memory()
{
    for(unsigned short i{}; i < 256; ++i)
    {
        this->addresses[i].clear();
    }
}
std::ostream &operator<<( std::ostream &os,Memory &m)
{
    os << std::setw(14) << "Memory" << "\n";
    os << "===========================\n";
    os << "Address" << std::setw(19) << "Content\n";
    os << "---------------------------\n";
    for(unsigned short i {}; i < 256; ++i)
    {
        os << to_hex(m[i].get_address()) << std::setw(10) << '|' << std::setw(10) << to_hex(m[i].get_content()) << '\n';
        os << "---------------------------\n";
    }
    return os;
}