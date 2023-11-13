#pragma once
#include"Registers.cpp"
#include"Memory.cpp"

class Instruction
{
private:
    char op;
    std::string operand;
public:
    Instruction(char OP = 0, std::string Operands = "");
    char get_op() const;
    std::string get_operand() const;
    ~Instruction() = default;
};

class Machine
{
public:
    Machine() = default;
    Instruction command;
    Memory memo;
    CPU_Registers cpu;
    unsigned char counter{},start_address{};
    void read();
    void Interface();
    void execution();
    void reset();
    ~Machine() = default;
};