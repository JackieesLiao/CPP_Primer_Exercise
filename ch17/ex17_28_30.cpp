#include <iostream>
#include <random>
#include <vector>

// 17.28/17.29/17.30: never-repeating random numbers. The 17.28 version
// keeps a history of the results; 17.29 lets the caller pick min and max;
// 17.30 adds a seed parameter so runs are reproducible.

unsigned unique_random(std::vector<unsigned> &history)
{
    static std::default_random_engine engine(std::random_device{}());
    static std::uniform_int_distribution<unsigned> distribution(0, 100);
    unsigned value = 0;
    do
    {
        value = distribution(engine);
    } while (std::find(history.begin(), history.end(), value) != history.end());
    history.push_back(value);
    return value;
}

unsigned ranged_random(unsigned low, unsigned high, unsigned seed = 0)
{
    // A fresh engine per call makes a given seed reproducible.
    std::default_random_engine engine(
        seed == 0 ? std::random_device{}() : seed);
    return std::uniform_int_distribution<unsigned>(low, high)(engine);
}

int main()
{
    std::vector<unsigned> history;
    std::cout << "17.28 unique draws:";
    for (int round = 0; round < 5; ++round)
    {
        std::cout << ' ' << unique_random(history);
    }
    std::cout << '\n';

    std::cout << "17.29 range 5..10: " << ranged_random(5, 10) << '\n';
    std::cout << "17.30 seeded 42 twice: " << ranged_random(1, 100, 42) << ' '
              << ranged_random(1, 100, 42) << '\n';
    return 0;
}
