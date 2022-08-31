#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <cstdint>
#include <array>
#include <string>
#include <random>

// Big Endian
class BigInt
{
private:
    static const int bytes{ 2048 };
    static const int size{ bytes / sizeof(uint64_t) + !!(bytes % sizeof(uint64_t)) };
    std::array<uint64_t, size> nums{};

    uint64_t u64_mul(uint64_t left, uint64_t right, uint64_t& carry);

public:
    static BigInt GetBigRandom();

    BigInt(std::array<uint64_t, 256>&);
    BigInt(uint64_t);

    BigInt operator~() const;

    BigInt operator<<(size_t) const;
    BigInt operator>>(size_t) const;

    BigInt& operator+=(const BigInt& right);
    BigInt operator+(const BigInt& right) const;
    BigInt& operator+=(const uint64_t right);
    BigInt operator+(const uint64_t right) const;

    BigInt& operator-=(const BigInt& right);
    BigInt operator-(const BigInt& right) const;
    BigInt& operator-=(const uint64_t right);
    BigInt operator-(const uint64_t right) const;

    BigInt& operator*=(const BigInt& right);
    BigInt operator*(const BigInt& right) const;
    BigInt& operator*=(const uint64_t right);
    BigInt operator*(const uint64_t right) const;

    std::string ToHex();
};

BigInt BigInt::GetBigRandom()
{
    static std::random_device rd;
    static std::mt19937_64 eng(rd());
    static std::uniform_int_distribution<uint64_t> distr;

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

inline BigInt BigInt::operator~() const
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
    return *this;
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

inline BigInt BigInt::operator-(const BigInt& right) const
{
    BigInt copy{ *this };
    copy -= right;
    return copy;
}

inline BigInt BigInt::operator-(const uint64_t right) const
{
    BigInt copy{ *this };
    copy += ~BigInt(right) + 1;
    return copy;
}

inline uint64_t BigInt::u64_mul(uint64_t left, uint64_t right, uint64_t& carry)
{
    uint64_t left_h = left >> 32;
    uint64_t right_h = right >> 32;
    uint64_t left_l = left & 0xffffffff;
    uint64_t right_l = right & 0xffffffff;

    uint64_t ll_rl = left_l * right_l;
    uint64_t lh_rl = left_h * right_l;
    uint64_t rh_ll = right_h * left_l;
    uint64_t rh_lh = right_h * left_h;

    uint64_t carry1 = ll_rl >> 32;
    uint64_t left_row1 = lh_rl + carry1;
    uint64_t result1 = ((left_row1 & 0xffffffff) << 32) + (ll_rl & 0xffffffff);
    uint64_t carry2 = rh_ll >> 32;
    uint64_t left_row2 = rh_lh + carry2;
    uint64_t result2 = rh_ll & 0xffffffff;

    carry = (left_row1 >> 32) + left_row2 + (((left_row1 & 0xffffffff) + result2) >> 32);
    return result1 + (result2 << 32);
}

inline BigInt& BigInt::operator*=(const BigInt& right)
{
    bool carry_on = false;
    uint64_t carry = 0;
    for (int i = size - 1; i >= 0; --i)
    {
        uint64_t carry_next_turn;
        nums[i] = u64_mul(nums[i], right.nums[i], carry_next_turn);
        if (carry)
        {
            uint64_t temp;
            if (__builtin_add_overflow(nums[i], carry, &temp))
                carry_next_turn += 1;
            nums[i] = temp;
            carry = 0;
        }

        carry = carry_next_turn;
    }

    return *this;
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