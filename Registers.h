#pragma once
#include "Address.h"

class Register_Address: public Address
{
private:
    unsigned char content;
public:
    Register_Address();
    virtual unsigned char get_address() const override;
    virtual void set_address(unsigned char x) override;
    unsigned char get_content() const;
    void set_content(const char* Hexbyte);
    void set_content(unsigned char data);
    void clear();
    Register_Address &operator=(const Register_Address &ra);
    Register_Address &operator=(Register_Address &&ra);
    unsigned char operator&(const Register_Address &ra);
    unsigned char operator|(const Register_Address &ra);
    unsigned char operator^(const Register_Address &ra);
    virtual ~Register_Address() = default;
};
class CPU_Registers
{
private:
    Register_Address registers [16];
public:
    CPU_Registers();
    CPU_Registers(const CPU_Registers &cr);
    Register_Address &operator[](unsigned char i);
    void clear_CPU();
    ~CPU_Registers() = default;
};
std::ostream &operator<<( std::ostream &os,CPU_Registers &cr);