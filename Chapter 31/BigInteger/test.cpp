#include "BigInt.hpp"
#include <cstdio>
#include <random>

void addition(FILE* const output)
{
    for (int i = 0; i < 10000; ++i)
    {
        BigInt<2048> bigA = BigInt<2048>::GetBigRandom();
        BigInt<2048> bigB = BigInt<2048>::GetBigRandom();
        BigInt<2048> bigC = bigA + bigB;
        
        fprintf(output, "0x%s\n", bigA.ToHex().c_str());
        fprintf(output, "0x%s\n", bigB.ToHex().c_str());
        fprintf(output, "0x%s\n", bigC.ToHex().c_str());
    }
}

void subtraction(FILE* const output)
{
    for (int i = 0; i < 10000; ++i)
    {
        BigInt<2048> bigA = BigInt<2048>::GetBigRandom();
        BigInt<2048> bigB = BigInt<2048>::GetBigRandom();
        BigInt<2048> bigC = bigA - bigB;
        
        fprintf(output, "0x%s\n", bigA.ToHex().c_str());
        fprintf(output, "0x%s\n", bigB.ToHex().c_str());
        fprintf(output, "0x%s\n", bigC.ToHex().c_str());
    }
}

void multiplication(FILE* const output)
{
    for (int i = 0; i < 10000; ++i)
    {
        BigInt<2048> bigA = BigInt<2048>::GetBigRandom();
        BigInt<2048> bigB = BigInt<2048>::GetBigRandom();
        BigInt<2048> bigC = bigA * bigB;
        
        fprintf(output, "0x%s\n", bigA.ToHex().c_str());
        fprintf(output, "0x%s\n", bigB.ToHex().c_str());
        fprintf(output, "0x%s\n", bigC.ToHex().c_str());
    }
}

int main(void)
{
    FILE* add = fopen("add", "w+");
    FILE* sub = fopen("sub", "w+");
    FILE* mul = fopen("mul", "w+");

    addition(add);
    subtraction(sub);
    multiplication(mul);

    fclose(add);
    fclose(sub);
    fclose(mul);
    return 0;
}