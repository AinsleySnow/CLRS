#include <cassert>
#include <random>
#include <vector>

std::vector<int> gen_random(int size)
{
    std::vector<int> result{};

    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<int> distr;

    for (int i = 0; i < size; ++i)
        result.push_back(distr(eng));

    return result;
}

void test_assending(void (*func)(int*, int))
{
    for (int k = 1; k <= 100; ++k)
    {
        std::vector<int> data{ gen_random(k) };
        func(data.data(), data.size());
        for (int i = 0; i < data.size() - 1; ++i)
            assert(data[i] <= data[i + 1]);
    }
}

void test_descending(void (*func)(int*, int))
{   
    for (int i = 0; i < 100; ++i)
    {
        std::vector<int> data{ gen_random(i) };
        func(data.data(), data.size());
        for (int i = 0; i < data.size() - 1; ++i)
            assert(data[i] <= data[i + 1]);
    }
}