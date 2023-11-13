#include "Instructions.cpp"
using namespace std;


void to_binary(unsigned char x, unsigned char eight = 8)
{
    if(!eight)
    {
        return;
    }
    to_binary(x/2,eight - 1);
    cout << x % 2;
}
int main()
{
    // Machine m1 {};
    unsigned char x{0b00110110}, y{0b01100110};
    short expx{((x >> 4) & 7) - 4}, expy{((y >> 4) & 7) - 4},expres{};
    unsigned char mantissa{};
    float res{};
    unsigned char mx{(x & 15)}, my{y & 15};
    bool carry{};
    if (expx > 0)
    {
        mx <<= expx;
    }
    else
    {
        mx >>= -expx;
    }
    if (expy > 0)
    {
        my <<= expy;
    }
    else
    {
        my >>= -expy;
    }
    unsigned int h28{1};
    while (h28 <= 128)
    {
        if ((mx & h28) ^ (my & h28))
        {
            if (!carry)
            {
                mantissa |= h28;
            }
        }
        else
        {
            if (((mx & h28) || (my & h28)))
            {
                if (carry)
                {
                    mantissa |= h28;
                }
                carry = 1;
            }
            else
            {
                carry = 0;
            }
        }
        h28 <<= 1;
    }
    h28 = 128;
    if (carry)
    {
        while (!(mantissa & h28))
        {
            h28 >>= 1;
        }
        h28 <<= 1;
        mantissa |= h28;
    }
    h28 = 128;
    short i{};
    while (!(mantissa & h28))
    {
        h28 >>= 1;
        ++i;
    } 
    expres = 8 - i - 4;
    if(expres > 0)
    {
        mantissa >>= expres;
    }
    else
    {
        mantissa <<= -expres;
    }
    unsigned char h8 = 8;
    while(h8)
    {
        if(expres > 0)
        {
            res += ((h8 & mantissa) != 0) << (expres - 1);
        }
        else
        {
            if(h8 & mantissa)
                res += 1.0/(((h8 & mantissa) != 0) << ((expres * -1) + 1));
        }
        expres--;
        h8 >>= 1;
    }
    expres = (8 - i);
    unsigned char resb{};
    resb = (((res < 0) << 128) & 128);
    resb |= (expres << 4);
    resb |= mantissa;
    cout <<"Floating Equivalent: " <<res << endl;
    cout <<"Decimal Equivalent: " <<(unsigned short)resb << endl;
    cout << "Raw Binary: ";
    to_binary(resb);
    cout << "\n";
    // m1.Interface();
    //  Memory m1{};
    //  CPU_Registers cr1 {};
    //  cout << m1 << endl;
    //  cout << cr1 << endl;

    return 0;
}