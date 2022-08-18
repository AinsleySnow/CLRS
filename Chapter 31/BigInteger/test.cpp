#include "BigInt.hpp"
#include <cstdio>
#include <random>

void addition(FILE* const output)
{
    for (int i = 0; i < 1000; ++i)
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
    for (int i = 0; i < 1000; ++i)
    {
        BigInt bigA = BigInt::GetBigRandom();
        BigInt bigB = BigInt::GetBigRandom();
        BigInt bigC = bigA - bigB;
        
        fprintf(output, "0x%s\n", bigA.ToHex().c_str());
        fprintf(output, "0x%s\n", bigB.ToHex().c_str());
        fprintf(output, "0x%s\n", bigC.ToHex().c_str());
    }
}

int main(void)
{
    FILE* add = fopen("add", "w+");
    FILE* sub = fopen("sub", "w+");

    addition(add);
    subtraction(sub);

    fclose(add);
    fclose(sub);
    return 0;
}