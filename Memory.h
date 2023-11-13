#pragma once
#include "Address.h"

class Memory_Address : public Address
{
private:
    unsigned char content;
public:
    Memory_Address();
    virtual unsigned char get_address() const override;
    virtual void set_address(unsigned char x) override;
    unsigned char get_content() const;
    void set_content(const char* Hexbyte);
    void set_content(unsigned char data);
    Memory_Address &operator=(const Memory_Address &m);
    virtual ~Memory_Address() override = default;
};

class Memory
{
private:
    Memory_Address addresses[256];
public:
    Memory();
    Memory(const Memory &m);
    Memory_Address &operator[](unsigned char i);
    ~Memory() = default;
};

std::ostream &operator<<( std::ostream &os,Memory &m);