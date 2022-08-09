#include "BigInt.hpp"
#include <cstdio>
#include <random>

int main(void)
{
    std::array<uint64_t, 256> a{};
    std::array<uint64_t, 256> b{};

    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<uint64_t> distr;

    FILE* output = fopen("output", "w+");
    
    for (int i = 0; i < 1000; ++i)
    {
        for (int j = 0; j < 256; ++j)
        {
            a[j] = distr(eng);
            b[j] = distr(eng);
        }

        BigInt bigA{ a };
        BigInt bigB{ b };

        BigInt bigC{ bigA + bigB };
        fprintf(output, "0x%s\n", bigA.ToHex().c_str());
        fprintf(output, "0x%s\n", bigB.ToHex().c_str());
        fprintf(output, "0x%s\n", bigC.ToHex().c_str());
    }

    fclose(output);
    return 0;
}