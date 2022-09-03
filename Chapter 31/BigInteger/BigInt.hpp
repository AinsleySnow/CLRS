#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <cstdint>
#include <array>
#include <string>
#include <random>

// Big Endian
template <size_t bytes>
class BigInt
{
private:
    static const int size{ bytes / sizeof(uint64_t) + !!(bytes % sizeof(uint64_t)) };
    std::array<uint64_t, size> nums{};

    uint64_t u64_mul(uint64_t left, uint64_t right, uint64_t& carry);

public:
    static BigInt GetBigRandom();

    BigInt() {};
    BigInt(std::array<uint64_t, size>& array) : 
        nums(array) {};
    BigInt(uint64_t);

    BigInt operator~() const;

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

template <size_t bytes>
BigInt<bytes> BigInt<bytes>::GetBigRandom()
{
    static std::random_device rd;
    static std::mt19937_64 eng(rd());
    static std::uniform_int_distribution<uint64_t> distr;

    std::array<uint64_t, size> random{};
    for (int i = 0; i < size; ++i)
        random[i] = distr(eng);

    return BigInt<bytes>{ random };
}

template <size_t bytes>
BigInt<bytes>::BigInt(uint64_t n)
{
    nums[size - 1] = n; 
}

template <size_t bytes>
inline BigInt<bytes> BigInt<bytes>::operator~() const
{
    BigInt<bytes> copy{ *this };
    for (uint64_t& num : copy.nums)
        num = ~num;
    return copy;
}

template <size_t bytes>
inline BigInt<bytes>& BigInt<bytes>::operator+=(const BigInt<bytes>& right)
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

template <size_t bytes>
inline BigInt<bytes> BigInt<bytes>::operator+(const BigInt<bytes>& right) const
{
    BigInt<bytes> copy{ *this };
    copy += right;
    return copy;
}

template <size_t bytes>
inline BigInt<bytes>& BigInt<bytes>::operator+=(const uint64_t right)
{
    *this += BigInt<bytes>(right);
    return *this;
}

template <size_t bytes>
inline BigInt<bytes> BigInt<bytes>::operator+(const uint64_t right) const
{
    BigInt<bytes> copy{ *this };
    copy += BigInt<bytes>(right);
    return copy;
}

template <size_t bytes>
inline BigInt<bytes>& BigInt<bytes>::operator-=(const BigInt<bytes>& right)
{
    BigInt<bytes> compment{ ~right + 1 };
    *this += compment;
    return *this;
}

template <size_t bytes>
inline BigInt<bytes> BigInt<bytes>::operator-(const BigInt<bytes>& right) const
{
    BigInt<bytes> copy{ *this };
    copy -= right;
    return copy;
}

template <size_t bytes>
inline BigInt<bytes> BigInt<bytes>::operator-(const uint64_t right) const
{
    BigInt<bytes> copy{ *this };
    copy += ~BigInt<bytes>(right) + 1;
    return copy;
}

template <size_t bytes>
inline uint64_t BigInt<bytes>::u64_mul(uint64_t left, uint64_t right, uint64_t& carry)
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

template <size_t bytes>
inline BigInt<bytes>& BigInt<bytes>::operator*=(const BigInt<bytes>& right)
{
    BigInt<bytes> new_right{};

    for (int j = size - 1; j >= 0; --j) // the lower row
    {
        uint64_t carry_next_turn = 0;
        uint64_t carry = 0;
        BigInt<bytes> result{};
        
        for (int i = size - 1; i >= size - 1 - j; --i) // the upper row
        {
            result.nums[j - ((size - 1) - i)] = u64_mul(nums[i], right.nums[j], carry_next_turn);
            if (carry)
            {
                uint64_t temp;
                if (__builtin_add_overflow(result.nums[j - ((size - 1) - i)], carry, &temp))
                    carry_next_turn += 1;
                result.nums[j - ((size - 1) - i)] = temp;
            }
            carry = carry_next_turn;
        }
        new_right += result;
    }

    *this = new_right;
    return *this;
}

template <size_t bytes>
inline BigInt<bytes> BigInt<bytes>::operator*(const BigInt<bytes>& right) const
{
    BigInt<bytes> copy{ *this };
    copy *= right;
    return copy;
}

template <size_t bytes>
inline BigInt<bytes> BigInt<bytes>::operator*(const uint64_t right) const
{
    BigInt<bytes> copy{ *this };
    copy *= right;
    return copy;
}

template <size_t bytes>
std::string BigInt<bytes>::ToHex()
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