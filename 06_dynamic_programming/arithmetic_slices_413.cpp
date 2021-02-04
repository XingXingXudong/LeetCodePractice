// https://leetcode.com/problems/arithmetic-slices/

#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <numeric>

int slices_a(const std::vector<int>& nums) {
    if (nums.size() <= 2) {
        return 0;
    }
    auto dp = std::vector<int>(nums.size(), 0);
    for (size_t i = 2; i < nums.size(); ++i) {
        // 1, 2, 3, 4, 5, 7, 8, 9, 10;
        // [1, 2, 3] -> 1
        // 1, [2, 3, 4] -> 1 + 1
        // 1, 2, [3, 4, 5] -> 2 + 1
        // 1, 2, 3, 4, 5, [7, 8, 9] -> 1 // z在 [7, 8, 9],之前没有连续的数组，即[5, 7, 8]不连续
        // 1, 2, 3, 4, 5, 7, [8, 9, 10] -> 1 + 2 // z在 [7, 8, 9],之前有连续的数组，即[7, 8, 9]
        if (nums[i] - nums[i-1] == nums[i - 1] - nums[i - 2]) {
            dp[i] = dp[i-1] + 1;    // 当前位置上，连续等差子序列的统计数，为上一个位置的统计数加1
        }
    }
    return std::accumulate(dp.begin(), dp.end(), 0);
}

// 空间压缩: 从DP的过程，分析出压缩的方案
int slices_b(const std::vector<int>& nums) {
    int sum = 0;
    int dp = 0;
    for (size_t i = 2; i < nums.size(); ++i) {
        if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2]) {
            ++dp;
            sum += dp;
        } else {
            dp = 0;
        }
    }
    return sum;
}

TEST(slices, a) {
    auto input = std::vector<int>{1, 2, 3, 4};
    auto output = 3;
    EXPECT_EQ(slices(input), output);
}

TEST(slices, b) {
    auto input = std::vector<int>{};
    auto output = 0;
    EXPECT_EQ(slices(input), output);
}

TEST(slices, c) {
    auto input = std::vector<int>{1, 2, 3};
    auto output = 1;
    EXPECT_EQ(slices(input), output);
}

TEST(slices, d) {
    auto input = std::vector<int>{1, 2, 3, 4, 7, 8, 9, 10};
    auto output = 6;
    EXPECT_EQ(slices(input), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}