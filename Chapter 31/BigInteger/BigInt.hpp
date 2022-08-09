#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <cstdint>
#include <array>
#include <string>

// Little Endian
class BigInt
{
private:
    static const int bytes{ 2048 };
    static const int size{ bytes / sizeof(uint64_t) + !!(bytes % sizeof(uint64_t)) };
    std::array<uint64_t, size> nums;

public:
    BigInt(std::array<uint64_t, 256>);
    BigInt& operator+=(const BigInt& right);
    BigInt operator+(const BigInt& right);

    std::string ToHex();
};

BigInt::BigInt(std::array<uint64_t, 256> array)
{
    nums = array;
}

inline BigInt& BigInt::operator+=(const BigInt& right)
{
    bool carry_on{ false };

    for (int i{ size - 1 }; i >= 0; --i)
    {
        uint64_t result{};

        if (carry_on)
        {
            if (!__builtin_add_overflow(nums[i], right.nums[i], &result))
                carry_on = false;
            nums[i] = result;
            
            if (__builtin_add_overflow(nums[i], 1, &result))
                carry_on = true;
            nums[i] = result;
        }
        else
        {
            if (__builtin_add_overflow(nums[i], right.nums[i], &result))
                carry_on = true;
            nums[i] = result;
        }
    }

    return *this;
}

inline BigInt BigInt::operator+(const BigInt& right)
{
    BigInt copy{ *this };
    copy += right;
    return copy;
}

std::string BigInt::ToHex()
{
    std::string repr{};
    char hexrepr[17]{};

    for (uint64_t ele : nums)
    {
        sprintf(hexrepr, "%016llX", ele);
        repr += hexrepr;
    }
    
    return repr;
}

#endif // _BIGINT_H_