#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <cstdint>
#include <array>
#include <string>
#include <random>

// Little Endian
class BigInt
{
private:
    static const int bytes{ 2048 };
    static const int size{ bytes / sizeof(uint64_t) + !!(bytes % sizeof(uint64_t)) };
    std::array<uint64_t, size> nums{};

public:
    static BigInt GetBigRandom();

    BigInt(std::array<uint64_t, 256>&);
    BigInt(uint64_t);

    BigInt& operator~() const;

    BigInt& operator+=(const BigInt& right);
    BigInt operator+(const BigInt& right) const;
    BigInt& operator+=(const uint64_t right);
    BigInt operator+(const uint64_t right) const;

    BigInt& operator-=(const BigInt& right);
    BigInt operator-(const BigInt& right) const;
    BigInt& operator-=(const uint64_t right);
    BigInt operator-(const uint64_t right) const;

    std::string ToHex();
};

BigInt BigInt::GetBigRandom()
{
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<uint64_t> distr;

    std::array<uint64_t, size> random{};
    for (int i = 0; i < size; ++i)
        random[i] = distr(eng);
    
    return BigInt{ random };
}

BigInt::BigInt(std::array<uint64_t, 256>& array)
{
    nums = array;
}

BigInt::BigInt(uint64_t n)
{
    nums[size - 1] = n; 
}

inline BigInt& BigInt::operator~() const
{
    BigInt copy{ *this };
    for (uint64_t& num : copy.nums)
        num = ~num;
    return copy;
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

inline BigInt BigInt::operator+(const BigInt& right) const
{
    BigInt copy{ *this };
    copy += right;
    return copy;
}

inline BigInt& BigInt::operator+=(const uint64_t right)
{
    *this += BigInt(right);
}

inline BigInt BigInt::operator+(const uint64_t right) const
{
    BigInt copy{ *this };
    copy += BigInt(right);
    return copy;
}

inline BigInt& BigInt::operator-=(const BigInt& right)
{
    BigInt compment{ ~right + 1 };
    *this += compment;
    return *this;
}

inline BigInt BigInt::operator-(const uint64_t right) const
{
    BigInt copy{ *this };
    copy += ~BigInt(right) + 1;
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