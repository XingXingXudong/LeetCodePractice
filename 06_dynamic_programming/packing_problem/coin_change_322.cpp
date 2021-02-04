// https://leetcode.com/problems/coin-change/

#include <vector>
#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>

void print_dp(const std::vector<int>& dp) {
    std::cout << "------------------------------" << std::endl;
    for (const auto& x: dp) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    std::cout << "------------------------------" << std::endl;
}

int coinChange(const std::vector<int>& coins, int amount) {
    if (amount < 0) {
        return -1;
    }
    if (amount == 0) {
        return 0;
    }
    auto dp = std::vector<int>(amount+1, amount + 2);
    dp[0] = 0;
    print_dp(dp);
    for (int i = 0; i <= amount; ++i) {
        for (const auto x: coins) {
            if (x <= i) {
                dp[i] = std::min(dp[i], dp[i-x] + 1);
                print_dp(dp);
            }
        }
    }
    return dp[amount] == amount + 2 ? -1 : dp[amount];
}

TEST(coinChange, a) {
    auto input = std::vector<int>{1, 2, 5};
    auto amount = 11;
    auto output = 3;
    EXPECT_EQ(coinChange(input, amount), output);
}

TEST(coinChange, b) {
    auto input = std::vector<int>{2};
    auto amount = 3;
    auto output = -1;
    EXPECT_EQ(coinChange(input, amount), output);
}

TEST(coinChange, c) {
    auto input = std::vector<int>{1};
    auto amount = 0;
    auto output = 0;
    EXPECT_EQ(coinChange(input, amount), output);
}

TEST(coinChange, d) {
    auto input = std::vector<int>{1};
    auto amount = 1;
    auto output = 1;
    EXPECT_EQ(coinChange(input, amount), output);
}

TEST(coinChange, e) {
    auto input = std::vector<int>{1};
    auto amount = 2;
    auto output = 2;
    EXPECT_EQ(coinChange(input, amount), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}