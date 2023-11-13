#include "Instructions.cpp"
using namespace std;

void to_binary(unsigned char x, unsigned char eight = 8)
{
    if (!eight)
    {
        return;
    }
    to_binary(x / 2, eight - 1);
    cout << x % 2;
}
int main()
{
    // Machine m1 {};
    unsigned char x{0b11100011}, y{0b00110110}, mantissa{};
    short ExpoRes{};
    float res{};
    unsigned char mx{static_cast<unsigned char>(x & static_cast<unsigned char>(15))}, my{static_cast<unsigned char>(y & static_cast<unsigned char>(15))};
    bool carry{}, neg{};
    if (((x >> 4) & 7) - 4 > 0)
    {
        mx <<= (((x >> 4) & 7) - 4);
    }
    else
    {
        mx >>= -(((x >> 4) & 7) - 4);
    }
    if ((((y >> 4) & 7) - 4) > 0)
    {
        my <<= (((y >> 4) & 7) - 4);
    }
    else
    {
        my >>= -(((y >> 4) & 7) - 4);
    }
    if (((x & 128) ^ (y & 128)))
    {
        if (x & 128)
        {
            neg = mx > my;
            mx = (~mx + 1) & 15;
        }
        if (y & 128)
        {

            neg = my > mx;
            my = (~my + 1) & 15;
        }
    }
    unsigned int bit{1};
    while (bit <= 128)
    {
        if ((mx & bit) ^ (my & bit))
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
            if ((mx & bit))
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
    if ((x & 128) ^ (y & 128))
    {
        mantissa = mantissa & 15;
    }
    if (carry && !neg)
    {
        while (!(mantissa & bit))
        {
            bit >>= 1;
        }
        bit <<= 1;
        mantissa |= bit;
    }
    bit = 128;
    char i{};
    if (neg)
    {
        mantissa = (~mantissa + 1) & 15;
    }
    while (!(mantissa & bit))
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
    bit = 8;
    while (bit)
    {
        if (ExpoRes > 0)
        {
            res += ((bit & mantissa) != 0) << (ExpoRes - 1);
        }
        else
        {
            if (bit & mantissa)
            {
                res += 1.0 / (((bit & mantissa) != 0) << ((ExpoRes * -1) + 1));
            }
        }
        ExpoRes--;
        bit >>= 1;
    }
    ExpoRes = (8 - i);
    unsigned char resb{};
    if (neg || ((x & 128) && (y & 128)))
    {
        resb |= 128;
        res = -res;
    }
    resb |= (ExpoRes << 4);
    resb |= (mantissa & 15);
    cout << "Floating Equivalent: " << res << endl;
    cout << "Unsigned Decimal Equivalent: " << (unsigned short)resb << endl;
    cout << "Two's complement Decimal Equivalent: " << (short)((char)resb) << endl;
    cout << "Raw Binary: ";
    to_binary(resb);
    cout << "\n";
    // m1.Interface();
    //  Memory m1{};
    //  CPU_Registers cr1 {};
    //   << m1 << endl;
    //   << cr1 << endl;

    return 0;
}