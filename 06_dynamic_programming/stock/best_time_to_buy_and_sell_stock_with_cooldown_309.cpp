// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/

#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

int maxProfit(const std::vector<int>& prices) {
    int days = prices.size();
    if (days < 2) {
        return 0;
    }
    std::vector<int> buys(days), sells(days), S1(days), S2(days);
    buys[0]  = S1[0] = -prices[0];
    sells[0] = S2[0] = 0;
    for (int i = 1; i < days; ++i) {
        buys[i] = S2[i-1] - prices[i];
        S1[i] = std::max(buys[i-1], S1[i-1]);
        sells[i] = std::max(buys[i-1], S1[i-1]) + prices[i];
        S2[i] = std::max(S2[i-1], sells[i-1]);
    }
    return std::max(S2[days-1], sells[days-1]);
}

TEST(maxProfit, a) {
    auto prices = std::vector<int>{1, 2, 3, 0, 2};
    int output = 3;
    EXPECT_EQ(maxProfit(prices), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}