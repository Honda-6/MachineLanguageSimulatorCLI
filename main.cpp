#include "Instructions.cpp"
using namespace std;

int main()
{
    // unsigned char x{0b01101010}, y{0b01101111}, mantissa{};
    // short ExpoRes{};
    // float res{};
    // unsigned char mx{static_cast<unsigned char>(x & static_cast<unsigned char>(15))}, my{static_cast<unsigned char>(y & static_cast<unsigned char>(15))};
    // bool carry{}, neg{};
    // char ExpoX{(((x >> 4) & 7) - 4)}, ExpoY{(((y >> 4) & 7) - 4)};
    // if (ExpoX > ExpoY)
    // {
    //     my >>= (ExpoX - ExpoY);
    // }
    // else
    // {
    //     mx >>= (ExpoY - ExpoX);
    // }
    // if (((x & 128) ^ (y & 128)))
    // {
    //     if (x & 128)
    //     {
    //         neg = mx > my;
    //         mx = (~mx + 1) & 15;
    //     }
    //     if (y & 128)
    //     {
    //         neg = my > mx;
    //         my = (~my + 1) & 15;
    //     }
    // }
    // else if (x & 128)
    // {
    //     neg = 1;
    // }
    // unsigned short bit{1};
    // while (bit <= 8)
    // {
    //     if ((mx & bit) ^ (my & bit))
    //     {
    //         if (!carry)
    //         {
    //             mantissa |= bit;
    //         }
    //     }
    //     else
    //     {
    //         if (carry)
    //         {
    //             mantissa |= bit;
    //         }
    //         if ((mx & bit))
    //         {
    //             carry = 1;
    //         }
    //         else
    //         {
    //             carry = 0;
    //         }
    //     }
    //     bit <<= 1;
    // }
    // bit = 128;
    // if ((x & 128) ^ (y & 128))
    // {
    //     mantissa = mantissa & 15;
    // }
    // if (carry && !((x & 128) ^ (y & 128)) && !(max(ExpoX, ExpoY) == 3 || max(ExpoX, ExpoY) == -4))
    // {
    //     bit = 16;
    //     mantissa |= bit;
    // }
    // bit = 128;
    // char i{};
    // if (neg && !((x & 128) && (y & 128)))
    // {
    //     mantissa = (~mantissa + 1) & 15;
    // }
    // while (!(mantissa & bit) && bit)
    // {
    //     bit >>= 1;
    //     ++i;
    // }
    // ExpoRes = 8 - i - 4;
    // if (ExpoRes > 0)
    // {
    //     mantissa >>= ExpoRes;
    // }
    // else
    // {
    //     mantissa <<= -ExpoRes;
    // }
    // bit = 8;
    // ExpoRes += max(ExpoX, ExpoY);
    // while (bit)
    // {
    //     if (ExpoRes > 0)
    //     {
    //         res += ((bit & mantissa) != 0) << (ExpoRes - 1);
    //     }
    //     else
    //     {
    //         if (bit & mantissa)
    //         {
    //             res += 1.0 / (((bit & mantissa) != 0) << ((ExpoRes * -1) + 1));
    //         }
    //     }
    //     ExpoRes--;
    //     bit >>= 1;
    // }
    // ExpoRes = (8 - i + max(ExpoX, ExpoY));
    // unsigned char resb{};
    // if (neg || ((x & 128) && (y & 128)))
    // {
    //     resb |= 128;
    //     res = -res;
    // }
    // resb |= (ExpoRes << 4);
    // resb |= (mantissa & 15);
    // cout << "Floating Equivalent: " << res << endl;
    // cout << "Unsigned Decimal Equivalent: " << (unsigned short)resb << endl;
    // cout << "Two's complement Decimal Equivalent: " << (short)((char)resb) << endl;
    // cout << "Raw Binary: ";
    // to_binary(resb);
    // cout << "\n";
    Machine m1{};
    m1.cpu[3].set_content("A4");
    m1.memo[0].set_content("C3");
    m1.Interface();

    return 0;
}