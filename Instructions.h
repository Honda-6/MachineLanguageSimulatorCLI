#pragma once
#include"Registers.cpp"
#include"Memory.cpp"

class Instruction
{
private:
    char op;
    char operand[4] = "000";
public:
    Instruction(char OP = '0', const char* operands = nullptr);
    char get_op() const;
    void clear();
    char* get_operand();
    void set_op(char OP);
    ~Instruction() = default;
};

class Machine
{
private:
    void load_from_memory(unsigned char addressR,unsigned char addressM);
    void load_register(unsigned char addressR,unsigned char val);
    void store_in_memory(unsigned char addressR,unsigned char addressM);
    void move_pattern(unsigned char addressR1, unsigned char addressR2);
    void add(char operation,unsigned char DestinationAddress,unsigned char register1,unsigned char register2);
    void AND(unsigned char DestinationAddress,unsigned char register1,unsigned char register2);
    void OR(unsigned char DestinationAddress,unsigned char register1,unsigned char register2);
    void XOR(unsigned char DestinationAddress,unsigned char register1,unsigned char register2);
    void rotate_right(unsigned char addressR,char times);
    void rotate_left(unsigned char addressR,char times);
    void jump(unsigned char addressR,unsigned char addressM);
    char menu();
    bool halt{};
    bool read();
    void Interface();
    void execution();
    void reset();
    Instruction command;
    Memory memo;
    CPU_Registers cpu;
    unsigned char start_address{};
    unsigned short counter{};
public:
    Machine() = default;
    void program();
    ~Machine() = default;
};