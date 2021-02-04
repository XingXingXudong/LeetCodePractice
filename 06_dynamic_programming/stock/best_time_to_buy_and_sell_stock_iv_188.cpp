//https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <gtest/gtest.h>

template<typename T>
void print(const std::vector<T>& vec) {
    std::cout << "------------------------------" << std::endl;
    for (auto x: vec) {
        std::cout << x << " ";
    }
    std::cout << "\n------------------------------" << std::endl;
}

int maxProfitUnLimit(const std::vector<int>& prices) {
    int maxP = 0;
    for (size_t i = 1; i < prices.size(); ++i) {
        if (prices[i] > prices[i-1]) {
            maxP += prices[i] - prices[i-1];
        }
    }
    return maxP;
}

int maxProfit(int k, const std::vector<int>& prices) {
    int days = prices.size();
    if (days < 2) {
        return 0;
    }
    if (k >= days) {
        return maxProfitUnLimit(prices);
    }
    auto buys = std::vector<int>(k+1, INT_MIN);
    auto sells = std::vector<int>(k+1, 0);
    for (int i = 0; i < days; ++i) {
        for (int j = 1; j <= k; ++j) {
            buys[j] = std::max(buys[j], sells[j-1] - prices[i]);
            print(buys);
            sells[j] = std::max(sells[j], buys[j] + prices[i]);
            print(sells);
        }
    }
    return sells[k];
}

TEST(maxProfit, a) {
    auto prices = std::vector<int>{2,4,1};
    int k = 2;
    int output = 2;
    EXPECT_EQ(maxProfit(k, prices), output);
}

TEST(maxProfit, b) {
    auto prices = std::vector<int>{3,2,6,5,0,3};
    int k = 2;
    int output = 7;
    EXPECT_EQ(maxProfit(k, prices), output);
}

TEST(maxProfit, c) {
    auto prices = std::vector<int>{3,2,6,5,0,3};
    int k = 1;
    int output = 4;
    EXPECT_EQ(maxProfit(k, prices), output);
}

TEST(maxProfit, d) {
    auto prices = std::vector<int>{3,2,6,5,0,3};
    int k = 0;
    int output = 0;
    EXPECT_EQ(maxProfit(k, prices), output);
}

TEST(maxProfit, e) {
    auto prices = std::vector<int>{3,2,6,5,0,3};
    int k = 10;
    int output = 7;
    EXPECT_EQ(maxProfit(k, prices), output);
}
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}