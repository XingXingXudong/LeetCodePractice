// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

#include <vector>
#include <algorithm>
#include <gtest/gtest.h>
#include <climits>

int maxProfit(const std::vector<int>& prices) {
    int n = prices.size();
    if (n < 2) {
        return 0;
    }
    auto dp = std::vector<int>(n, 0);
    int min = INT_MAX;
    int max_profit = 0;
    for (auto x: prices) {
        min = std::min(min, x);
        max_profit = std::max(max_profit, x - min);
    }
    return max_profit;
}

TEST(maxProfit, a) {
    auto input = std::vector<int>{7,1,5,3,6,4};
    int output = 5;
    EXPECT_EQ(maxProfit(input), output);
}

TEST(maxProfit, b) {
    auto input = std::vector<int>{7,6,4,3,1};
    int output = 0;
    EXPECT_EQ(maxProfit(input), output);
}


TEST(maxProfit, c) {
    auto input = std::vector<int>{7,0,6,4,3,1};
    int output = 6;
    EXPECT_EQ(maxProfit(input), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}