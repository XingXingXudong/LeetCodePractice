// https://leetcode.com/problems/count-primes/

#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <cmath>

int countPrime(int num) {
    if (num < 2) {
        return 0;
    }
    auto isPrime = std::vector<bool>(num, true);
    int count = num - 2;
    for (int i = 2; i <= (int) std::sqrt(num); ++i) {
        for (int j = i*2; j < num; j += i) {
            if (isPrime[j]) {
                isPrime[j] = false;
                --count;
            }
        }
    }
    return count;
}

TEST(countPrime, a) {
    int input = 10;
    int output = 4;
    EXPECT_EQ(countPrime(input), output);
}

TEST(countPrime, b) {
    int input = 0;
    int output = 0;
    EXPECT_EQ(countPrime(input), output);
}

TEST(countPrime, c) {
    int input = 1;
    int output = 0;
    EXPECT_EQ(countPrime(input), output);
}

TEST(countPrime, d) {
    int input = 2;
    int output = 0;
    EXPECT_EQ(countPrime(input), output);
}

TEST(countPrime, g) {
    int input = 3;
    int output = 1;
    EXPECT_EQ(countPrime(input), output);
}

TEST(countPrime, e) {
    int input = 4;
    int output = 2;
    EXPECT_EQ(countPrime(input), output);
}

TEST(countPrime, f) {
    int input = 7;
    int output = 3;
    EXPECT_EQ(countPrime(input), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}