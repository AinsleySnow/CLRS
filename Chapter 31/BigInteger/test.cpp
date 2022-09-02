#include "BigInt.hpp"
#include <cstdio>
#include <random>

void addition(FILE* const output)
{
    for (int i = 0; i < 10000; ++i)
    {
        BigInt bigA = BigInt::GetBigRandom();
        BigInt bigB = BigInt::GetBigRandom();
        BigInt bigC = bigA + bigB;
        
        fprintf(output, "0x%s\n", bigA.ToHex().c_str());
        fprintf(output, "0x%s\n", bigB.ToHex().c_str());
        fprintf(output, "0x%s\n", bigC.ToHex().c_str());
    }
}

void subtraction(FILE* const output)
{
    for (int i = 0; i < 10000; ++i)
    {
        BigInt bigA = BigInt::GetBigRandom();
        BigInt bigB = BigInt::GetBigRandom();
        BigInt bigC = bigA - bigB;
        
        fprintf(output, "0x%s\n", bigA.ToHex().c_str());
        fprintf(output, "0x%s\n", bigB.ToHex().c_str());
        fprintf(output, "0x%s\n", bigC.ToHex().c_str());
    }
}

void multiplication(FILE* const output)
{
    for (int i = 0; i < 10000; ++i)
    {
        BigInt bigA = BigInt::GetBigRandom();
        BigInt bigB = BigInt::GetBigRandom();
        BigInt bigC = bigA * bigB;
        
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