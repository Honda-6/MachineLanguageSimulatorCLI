#include "Instructions.h"

Instruction::Instruction(char OP,std::string Operands)
 : op {OP}, operand {Operands} {}


char Instruction::get_op() const
{
    return this->op;
}
std::string Instruction::get_operand() const
{
    return this->operand;
}

void Machine::Interface()
{
    std::cout << std::setw(14) << "Memory" << std::setw(46)<< "CPU" <<"\n";
    std::cout << "===========================" << std::setw(45) << "===========================\n";
    std::cout << "Address" << std::setw(17) << "Content" <<std::setw(29)<< "Register" << std::setw(17) << "Content\n";
    std::cout << "---------------------------" << std::setw(45) << "---------------------------\n";
    for(unsigned short i {}; i < 16; ++i)
    {
        std::cout << to_hex(memo[i].get_address()) << std::setw(10) << '|' << std::setw(10) << to_hex(memo[i].get_content());
        std::cout << std::setw(28) << to_hex(cpu[i].get_address()) << std::setw(8) << '|' << std::setw(8) << to_hex(cpu[i].get_content()) << '\n';
        std::cout << "---------------------------" << std::setw(45) << "---------------------------\n";
    }
    std::cout << to_hex(memo[16].get_address()) << std::setw(10) << '|' << std::setw(10) << to_hex(memo[16].get_content()) <<"\n";
    std::cout << "---------------------------\n";
    std::cout << to_hex(memo[17].get_address()) << std::setw(10) << '|' << std::setw(10) << to_hex(memo[17].get_content());
    std::cout << std::setw(37) << "Start Address: " << to_hex(start_address) << "\n";
    std::cout << "---------------------------\n";
    std::cout << to_hex(memo[18].get_address()) << std::setw(10) << '|' << std::setw(10) << to_hex(memo[18].get_content());
    std::cout << std::setw(31) << "Counter: " << to_hex(counter) << "\n";
    std::cout << "---------------------------\n";
    std::cout << to_hex(memo[19].get_address()) << std::setw(10) << '|' << std::setw(10) << to_hex(memo[19].get_content());
    std::cout << std::setw(30) << "Screen: " << (char)(memo[0].get_content()) << "\n";
    std::cout << "---------------------------\n";
    for(unsigned short i {19}; i < 256; ++i)
    {
        std::cout << to_hex(memo[i].get_address()) << std::setw(10) << '|' << std::setw(10) << to_hex(memo[i].get_content()) << "\n";
        std::cout << "---------------------------\n";
    }
}