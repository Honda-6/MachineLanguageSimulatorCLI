#include "Instructions.h"

Instruction::Instruction(char OP, const char *Operands)
    : op{OP}
{
    for (unsigned char i{}; Operands && Operands[i] && i < 4; ++i)
        this->operand[i] = Operands[i];
}

char Instruction::get_op() const
{
    return this->op;
}
char *Instruction::get_operand()
{
    return this->operand;
}
void Instruction::set_op(char OP)
{
    this->op = OP;
}
void Instruction::clear()
{
    this->op = '0';
    for (unsigned char i{}; i < 3; ++i)
        this->operand[i] = '0';
    this->operand[3] = 0;
}
void Machine::load_from_memory(unsigned char addressR, unsigned char addressM)
{
    this->cpu[addressR].set_content(this->memo[addressM].get_content());
}
void Machine::load_register(unsigned char addressR, unsigned char val)
{
    this->cpu[addressR].set_content(val);
}
void Machine::store_in_memory(unsigned char addressR, unsigned char addressM)
{
    this->memo[addressM].set_content(this->cpu[addressR].get_content());
}
void Machine::move_pattern(unsigned char addressR1, unsigned char addressR2)
{
    this->cpu[addressR2] = this->cpu[addressR1];
}
void Machine::add(char operation, unsigned char DestinationAddress, unsigned char register1, unsigned char register2)
{
    if (operation == '5')
    {
        this->cpu[DestinationAddress].set_content(this->cpu[register1].get_content() + this->cpu[register2].get_content());
    }
    else
    {
        unsigned char mantissa{};
        short ExpoRes{};
        float res{};
        unsigned char R1mantissa{static_cast<unsigned char>(this->cpu[register1].get_content() & static_cast<unsigned char>(15))}, R2mantissa{static_cast<unsigned char>(this->cpu[register2].get_content() & static_cast<unsigned char>(15))};
        bool carry{}, negativity{};
        char ExponentRegister1{(char)((char)((this->cpu[register1].get_content() >> 4) & 7) - (char)4)}, ExponentRegister2{(char)((char)((this->cpu[register2].get_content() >> 4) & 7) - (char)4)};
        if (ExponentRegister1 > ExponentRegister2)
        {
            R2mantissa >>= (ExponentRegister1 - ExponentRegister2);
        }
        else
        {
            R1mantissa >>= (ExponentRegister2 - ExponentRegister1);
        }
        if (((this->cpu[register1].get_content() & 128) ^ (this->cpu[register2].get_content() & 128)))
        {
            if (this->cpu[register1].get_content() & 128)
            {
                negativity = R1mantissa > R2mantissa;
                R1mantissa = (~R1mantissa + 1) & 15;
            }
            if (this->cpu[register2].get_content() & 128)
            {
                negativity = R2mantissa > R1mantissa;
                R2mantissa = (~R2mantissa + 1) & 15;
            }
        }
        else if (this->cpu[register1].get_content() & 128)
        {
            negativity = 1;
        }
        unsigned short bit{1};
        while (bit <= 8)
        {
            if ((R1mantissa & bit) ^ (R2mantissa & bit))
            {
                if (!carry)
                {
                    mantissa |= bit;
                }
            }
            else
            {
                if (carry)
                {
                    mantissa |= bit;
                }
                if ((R1mantissa & bit))
                {
                    carry = 1;
                }
                else
                {
                    carry = 0;
                }
            }
            bit <<= 1;
        }
        bit = 128;
        if ((this->cpu[register1].get_content() & 128) ^ (this->cpu[register2].get_content() & 128))
        {
            mantissa = mantissa & 15;
        }
        if (carry && !((this->cpu[register1].get_content() & 128) ^ (this->cpu[register2].get_content() & 128)) && !(std::max(ExponentRegister1, ExponentRegister2) == 3 || std::max(ExponentRegister1, ExponentRegister2) == -4))
        {
            bit = 16;
            mantissa |= bit;
        }
        bit = 128;
        char i{};
        if (negativity && !((this->cpu[register1].get_content() & 128) && (this->cpu[register2].get_content() & 128)))
        {
            mantissa = (~mantissa + 1) & 15;
        }
        while (!(mantissa & bit) && bit)
        {
            bit >>= 1;
            ++i;
        }
        ExpoRes = 8 - i - 4;
        if (ExpoRes > 0)
        {
            mantissa >>= ExpoRes;
        }
        else
        {
            mantissa <<= -ExpoRes;
        }
        ExpoRes = (8 - i + std::max(ExponentRegister1, ExponentRegister2));
        unsigned char resb{};
        if (negativity || ((this->cpu[register1].get_content() & 128) && (this->cpu[register2].get_content() & 128)))
        {
            resb |= 128;
        }
        resb |= (ExpoRes << 4);
        resb |= (mantissa & 15);
    }
}
void Machine::AND(unsigned char DestinationAddress, unsigned char register1, unsigned char register2)
{
    this->cpu[DestinationAddress].set_content(cpu[register1] & cpu[register2]);
}
void Machine::OR(unsigned char DestinationAddress, unsigned char register1, unsigned char register2)
{
    this->cpu[DestinationAddress].set_content(cpu[register1] | cpu[register2]);
}
void Machine::XOR(unsigned char DestinationAddress, unsigned char register1, unsigned char register2)
{
    this->cpu[DestinationAddress].set_content(cpu[register1] ^ cpu[register2]);
}
void Machine::rotate_right(unsigned char addressR, char times)
{
    unsigned char BitPattern{this->cpu[addressR].get_content()};
    while (times--)
    {
        if (BitPattern % 2)
        {
            BitPattern >>= 1;
            BitPattern |= (1 << 7);
        }
        else
        {
            BitPattern >>= 1;
        }
    }
    this->cpu[addressR].set_content(BitPattern);
}
void Machine::rotate_left(unsigned char addressR, char times)
{
    unsigned char BitPattern{this->cpu[addressR].get_content()};
    while (times--)
    {
        if (BitPattern & 128)
        {
            BitPattern <<= 1;
            BitPattern |= (1);
        }
        else
        {
            BitPattern <<= 1;
        }
    }
    this->cpu[addressR].set_content(BitPattern);
}
void Machine::jump(unsigned char addressR, unsigned char addressM)
{
    if (this->cpu[0].get_content() == this->cpu[addressR].get_content())
        this->counter = addressM;
    else
        this->counter += 2;
}
void Machine::reset()
{
    this->memo.clear_memory();
    this->cpu.clear_CPU();
    this->halt = false;
    this->counter = this->start_address = 0;
    this->command.clear();
}
void Machine::execution()
{
    switch (memo[this->counter].get_content() / 16)
    {
    case 1:
        this->load_from_memory(memo[this->counter].get_content() % 16, memo[this->counter + 1].get_content());
        this->command.set_op(to_hexa_digit(memo[this->counter].get_content() / 16));
        this->command.get_operand()[0] = to_hexa_digit(memo[this->counter].get_content() % 16);
        this->command.get_operand()[1] = to_hexa_digit(memo[this->counter + 1].get_content() / 16);
        this->command.get_operand()[2] = to_hexa_digit(memo[this->counter + 1].get_content() % 16);
        this->command.get_operand()[3] = 0;
        counter += 2;
        break;
    case 2:
        this->load_register(memo[this->counter].get_content() % 16, memo[this->counter + 1].get_content());
        this->command.set_op(to_hexa_digit(memo[this->counter].get_content() / 16));
        this->command.get_operand()[0] = to_hexa_digit(memo[this->counter].get_content() % 16);
        this->command.get_operand()[1] = to_hexa_digit(memo[this->counter + 1].get_content() / 16);
        this->command.get_operand()[2] = to_hexa_digit(memo[this->counter + 1].get_content() % 16);
        this->command.get_operand()[3] = 0;
        counter += 2;
        break;
    case 3:
        this->store_in_memory(memo[this->counter].get_content() % 16, memo[this->counter + 1].get_content());
        this->command.set_op(to_hexa_digit(memo[this->counter].get_content() / 16));
        this->command.get_operand()[0] = to_hexa_digit(memo[this->counter].get_content() % 16);
        this->command.get_operand()[1] = to_hexa_digit(memo[this->counter + 1].get_content() / 16);
        this->command.get_operand()[2] = to_hexa_digit(memo[this->counter + 1].get_content() % 16);
        this->command.get_operand()[3] = 0;
        counter += 2;
        break;
    case 4:
        this->move_pattern(memo[this->counter + 1].get_content() / 16, memo[this->counter + 1].get_content() % 16);
        this->command.set_op(to_hexa_digit(memo[this->counter].get_content() / 16));
        this->command.get_operand()[0] = to_hexa_digit(memo[this->counter].get_content() % 16);
        this->command.get_operand()[1] = to_hexa_digit(memo[this->counter + 1].get_content() / 16);
        this->command.get_operand()[2] = to_hexa_digit(memo[this->counter + 1].get_content() % 16);
        this->command.get_operand()[3] = 0;
        counter += 2;
        break;
    case 5:
        this->add('5', memo[this->counter].get_content() % 16, memo[this->counter + 1].get_content() / 16, memo[this->counter + 1].get_content() % 16);
        this->command.set_op(to_hexa_digit(memo[this->counter].get_content() / 16));
        this->command.get_operand()[0] = to_hexa_digit(memo[this->counter].get_content() % 16);
        this->command.get_operand()[1] = to_hexa_digit(memo[this->counter + 1].get_content() / 16);
        this->command.get_operand()[2] = to_hexa_digit(memo[this->counter + 1].get_content() % 16);
        this->command.get_operand()[3] = 0;
        counter += 2;
        break;
    case 6:
        this->add('6', memo[this->counter].get_content() % 16, memo[this->counter + 1].get_content() / 16, memo[this->counter + 1].get_content() % 16);
        this->command.set_op(to_hexa_digit(memo[this->counter].get_content() / 16));
        this->command.get_operand()[0] = to_hexa_digit(memo[this->counter].get_content() % 16);
        this->command.get_operand()[1] = to_hexa_digit(memo[this->counter + 1].get_content() / 16);
        this->command.get_operand()[2] = to_hexa_digit(memo[this->counter + 1].get_content() % 16);
        this->command.get_operand()[3] = 0;
        counter += 2;
        break;
    case 7:
        this->OR(memo[this->counter].get_content() % 16, memo[this->counter + 1].get_content() / 16, memo[this->counter + 1].get_content() % 16);
        this->command.set_op(to_hexa_digit(memo[this->counter].get_content() / 16));
        this->command.get_operand()[0] = to_hexa_digit(memo[this->counter].get_content() % 16);
        this->command.get_operand()[1] = to_hexa_digit(memo[this->counter + 1].get_content() / 16);
        this->command.get_operand()[2] = to_hexa_digit(memo[this->counter + 1].get_content() % 16);
        this->command.get_operand()[3] = 0;
        counter += 2;
        break;
    case 8:
        this->AND(memo[this->counter].get_content() % 16, memo[this->counter + 1].get_content() / 16, memo[this->counter + 1].get_content() % 16);
        this->command.set_op(to_hexa_digit(memo[this->counter].get_content() / 16));
        this->command.get_operand()[0] = to_hexa_digit(memo[this->counter].get_content() % 16);
        this->command.get_operand()[1] = to_hexa_digit(memo[this->counter + 1].get_content() / 16);
        this->command.get_operand()[2] = to_hexa_digit(memo[this->counter + 1].get_content() % 16);
        this->command.get_operand()[3] = 0;
        counter += 2;
        break;
    case 9:
        this->XOR(memo[this->counter].get_content() % 16, memo[this->counter + 1].get_content() / 16, memo[this->counter + 1].get_content() % 16);
        this->command.set_op(to_hexa_digit(memo[this->counter].get_content() / 16));
        this->command.get_operand()[0] = to_hexa_digit(memo[this->counter].get_content() % 16);
        this->command.get_operand()[1] = to_hexa_digit(memo[this->counter + 1].get_content() / 16);
        this->command.get_operand()[2] = to_hexa_digit(memo[this->counter + 1].get_content() % 16);
        this->command.get_operand()[3] = 0;
        counter += 2;
        break;
    case 10:
        this->rotate_right(memo[this->counter].get_content() % 16, memo[this->counter + 1].get_content());
        this->command.set_op(to_hexa_digit(memo[this->counter].get_content() / 16));
        this->command.get_operand()[0] = to_hexa_digit(memo[this->counter].get_content() % 16);
        this->command.get_operand()[1] = to_hexa_digit(memo[this->counter + 1].get_content() / 16);
        this->command.get_operand()[2] = to_hexa_digit(memo[this->counter + 1].get_content() % 16);
        this->command.get_operand()[3] = 0;
        counter += 2;
        break;
    case 11:
        this->command.set_op(to_hexa_digit(memo[this->counter].get_content() / 16));
        this->command.get_operand()[0] = to_hexa_digit(memo[this->counter].get_content() % 16);
        this->command.get_operand()[1] = to_hexa_digit(memo[this->counter + 1].get_content() / 16);
        this->command.get_operand()[2] = to_hexa_digit(memo[this->counter + 1].get_content() % 16);
        this->command.get_operand()[3] = 0;
        this->jump(memo[this->counter].get_content() % 16, memo[this->counter + 1].get_content());
        break;
    case 13:
        this->rotate_left(memo[this->counter].get_content() % 16, memo[this->counter + 1].get_content());
        this->command.set_op(to_hexa_digit(memo[this->counter].get_content() / 16));
        this->command.get_operand()[0] = to_hexa_digit(memo[this->counter].get_content() % 16);
        this->command.get_operand()[1] = to_hexa_digit(memo[this->counter + 1].get_content() / 16);
        this->command.get_operand()[2] = to_hexa_digit(memo[this->counter + 1].get_content() % 16);
        this->command.get_operand()[3] = 0;
        counter += 2;
        break;
    case 12:
        halt = true;
        this->command.set_op(to_hexa_digit(memo[this->counter].get_content() / 16));
        this->command.get_operand()[0] = to_hexa_digit(memo[this->counter].get_content() % 16);
        this->command.get_operand()[1] = to_hexa_digit(memo[this->counter + 1].get_content() / 16);
        this->command.get_operand()[2] = to_hexa_digit(memo[this->counter + 1].get_content() % 16);
        this->command.get_operand()[3] = 0;
        counter += 2;
        break;
    default:
        this->command.set_op(to_hexa_digit(memo[this->counter].get_content() / 16));
        this->command.get_operand()[0] = to_hexa_digit(memo[this->counter].get_content() % 16);
        this->command.get_operand()[1] = to_hexa_digit(memo[this->counter + 1].get_content() / 16);
        this->command.get_operand()[2] = to_hexa_digit(memo[this->counter + 1].get_content() % 16);
        this->command.get_operand()[3] = 0;
        counter += 2;
        break;
    }
}

char spaces(unsigned char val)
{
    char digits{};
    if (val & 128)
        digits += 2;
    char signedval{static_cast<char>(val)};
    val /= 10;
    signedval /= 10;
    while (val)
    {
        digits++;
        val /= 10;
    }
    while (signedval)
    {
        digits++;
        signedval /= 10;
    }
    return digits;
}

void Machine::Interface()
{
    std::cout << std::setw(23) << "Memory" << std::setw(78) << "CPU"
              << "\n";
    std::cout << "==========================================================" << std::setw(72) << "=========================================================\n";
    std::cout << "Address" << std::setw(25) << "Content" << std::setw(50) << "Register" << std::setw(27) << "Content\n";
    std::cout << "----------------------------------------------------------" << std::setw(72) << "---------------------------------------------------------\n";
    for (unsigned short i{}; i < 16; ++i)
    {
        std::cout << to_hex(memo[i].get_address()) << std::setw(10) << '|' << std::setw(10) << to_hex(memo[i].get_content()) << " / " << (short)memo[i].get_content() << " / " << (short)((char)memo[i].get_content()) << " / " << std::fixed << std::setprecision(5) << to_float(memo[i].get_content()) << " / ";
        to_binary(memo[i].get_content());
        std::cout << std::setw(28 - spaces(memo[i].get_content()) - 1) << to_hex(cpu[i].get_address()) << std::setw(8) << '|' << std::setw(8) << to_hex(cpu[i].get_content()) << " / " << (short)cpu[i].get_content() << " / " << (short)((char)cpu[i].get_content()) << " / " << std::fixed << std::setprecision(5) << to_float(cpu[i].get_content()) << " / ";
        to_binary(cpu[i].get_content());
        std::cout << "\n----------------------------------------------------------" << std::setw(72) << "---------------------------------------------------------\n";
    }
    std::cout << to_hex(memo[16].get_address()) << std::setw(10) << '|' << std::setw(10) << to_hex(memo[16].get_content()) << " / " << (short)memo[16].get_content() << " / " << (short)((char)memo[16].get_content()) << " / " << std::fixed << std::setprecision(5) << to_float(memo[16].get_content()) << " / ";
    to_binary(memo[16].get_content());
    std::cout << "\n----------------------------------------------------------\n";
    std::cout << to_hex(memo[17].get_address()) << std::setw(10) << '|' << std::setw(10) << to_hex(memo[17].get_content()) << " / " << (short)memo[17].get_content() << " / " << (short)((char)memo[17].get_content()) << " / " << std::fixed << std::setprecision(5) << to_float(memo[17].get_content()) << " / ";
    to_binary(memo[17].get_content());
    std::cout << std::setw(37 - spaces(memo[17].get_content()) - 1) << "Start Address: " << to_hex(this->start_address) << "\n";
    std::cout << "----------------------------------------------------------\n";
    std::cout << to_hex(memo[18].get_address()) << std::setw(10) << '|' << std::setw(10) << to_hex(memo[18].get_content()) << " / " << (short)memo[18].get_content() << " / " << (short)((char)memo[18].get_content()) << " / " << std::fixed << std::setprecision(5) << to_float(memo[18].get_content()) << " / ";
    to_binary(memo[18].get_content());
    std::cout << std::setw(31 - spaces(memo[18].get_content()) - 1) << "Counter: " << to_hex(counter) << "\n";
    std::cout << "----------------------------------------------------------\n";
    std::cout << to_hex(memo[19].get_address()) << std::setw(10) << '|' << std::setw(10) << to_hex(memo[19].get_content()) << " / " << (short)memo[19].get_content() << " / " << (short)((char)memo[19].get_content()) << " / " << std::fixed << std::setprecision(5) << to_float(memo[19].get_content()) << " / ";
    to_binary(memo[19].get_content());
    std::cout << std::setw(30 - spaces(memo[19].get_content()) - 1) << "Screen: " << (char)(memo[0].get_content()) << "\n";
    std::cout << "----------------------------------------------------------\n";
    std::cout << to_hex(memo[20].get_address()) << std::setw(10) << '|' << std::setw(10) << to_hex(memo[20].get_content()) << " / " << (short)memo[20].get_content() << " / " << (short)((char)memo[20].get_content()) << " / " << std::fixed << std::setprecision(5) << to_float(memo[20].get_content()) << " / ";
    to_binary(memo[20].get_content());
    std::cout << std::setw(35 - spaces(memo[20].get_content()) - 1) << "Instruction: " << this->command.get_op() << this->command.get_operand() << "\n";
    std::cout << "----------------------------------------------------------\n";
    for (unsigned short i{21}; i < 256; ++i)
    {
        std::cout << to_hex(memo[i].get_address()) << std::setw(10) << '|' << std::setw(10) << to_hex(memo[i].get_content()) << " / " << (short)memo[i].get_content() << " / " << (short)((char)memo[i].get_content()) << " / " << std::fixed << std::setprecision(5) << to_float(memo[i].get_content()) << " / ";
        to_binary(memo[i].get_content());
        std::cout << "\n----------------------------------------------------------\n";
    }
}

char Machine::menu()
{
    char selection{};
    std::cout << "\n           Machine Language Simulator (CLI)\n"
              << "__________________________________________________\n"
              << "1- Load instructions from a file into memory\n"
              << "2- Display current memory and cpu status\n"
              << "3- Execute one instruction\n"
              << "4- Run instructions till halt or end of memory\n"
              << "5- Reset\n"
              << "6- Exit\n\n";
    std::cin >> selection;
    while (selection < 48 || selection > 54)
    {
        std::cout << "\nInvalid input!!\n"
                  << "Please enter one of the specified options: ";
        std::cin >> selection;
    }
    return selection;
}

bool Machine::read()
{
    char filename[100]{};
    std::cout << "Specify file containing instructions to load from: ";
    std::cin >> filename;
    std::FILE *f;
    f = std::fopen(filename, "r");
    if (!f)
    {
        return false;
    }
    this->reset();
    this->counter = this->start_address = to_decimal(std::fgets(command.get_operand(), 3, f));
    unsigned short i{start_address};
    while (!feof(f) && i < 256)
    {
        if (fgetc(f) >= 48)
        {
            fseek(f, -1, SEEK_CUR);
            command.set_op(fgetc(f));
            fgets(command.get_operand(), 4, f);
            memo[i].set_content(to_decimal(command.get_op()) * 16 + to_decimal(command.get_operand()[0]));
            ++i;
            memo[i].set_content(to_decimal(command.get_operand()[1]) * 16 + to_decimal(command.get_operand()[2]));
            ++i;
        }
    }
    std::fclose(f);
    std::cout << "Instructions loaded!..\n";
    this->command.clear();
    return true;
}

void Machine::program()
{
    while (true)
    {
        switch (menu())
        {
        case '1':
            if (!this->read())
            {
                std::cerr << "Failed to open file!\n";
            }
            break;
        case '2':
            Interface();
            break;
        case '3':
            if (this->halt || this->counter > 255)
                std::cout << "Program halted or reached its end!\n";
            else
            {
                execution();
                Interface();
            }
            break;
        case '4':
            if (this->halt || this->counter > 255)
                std::cout << "Program halted or reached its end!\n";
            else
            {
                while (!halt && this->counter <= 255)
                {
                    execution();
                }
                Interface();
                std::cout << "Program finished!..\n";
            }
            break;
        case '5':
            this->reset();
            std::cout << "Memory and registers are cleared!\n";
            break;
        case '6':
            std::cout << "Program Exited!..\n";
            return;
        default:
            break;
        }
    }
}