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
private:
    void load_from_memory(unsigned char addressR,unsigned char addressM);
    void load_register(unsigned char addressR,const char* val);
    void store_in_memory(unsigned char addressR,unsigned char addressM);
    void store_in_screen(unsigned char addressR);
    void move_pattern(unsigned char addressR1, unsigned char addressR2);
    void add(char operation,unsigned char DestinationAddress,unsigned char register1,unsigned char register2);
    void AND(unsigned char DestinationAddress,unsigned char register1,unsigned char register2);
    void OR(unsigned char DestinationAddress,unsigned char register1,unsigned char register2);
    void XOR(unsigned char DestinationAddress,unsigned char register1,unsigned char register2);
    void rotate_right(unsigned char addressR,char times);
    void rotate_left(unsigned char addressR,char times);
    void jump(unsigned char addressR,unsigned char addressM);

public:
    Machine() = default;
    Instruction command;
    Memory memo;
    CPU_Registers cpu;
    unsigned char start_address{};
    unsigned short counter{};
    void read();
    void Interface();
    void execution();
    void reset();
    ~Machine() = default;
};