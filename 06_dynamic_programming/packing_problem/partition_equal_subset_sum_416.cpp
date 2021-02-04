// https://leetcode.com/problems/partition-equal-subset-sum/

#include <vector>
#include <iostream>
#include <gtest/gtest.h>
#include <numeric>

void print_dp(const std::vector<std::vector<bool>>& dp) {
    std::cout << "------------------------------" << std::endl;
    for (const auto & vec: dp) {
        for (auto x: vec) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "------------------------------" << std::endl;
}

bool canPartition(const std::vector<int>& nums) {
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2 != 0) return false;
    int target = sum / 2;
    int N = nums.size();
    auto dp = std::vector<std::vector<bool>>(N+1, std::vector<bool>(target+1, false));
    for (int i = 0; i <= N; ++i) {
        dp[i][0] = true;
    }
    print_dp(dp);
    for (int i = 1; i <= N; ++i) {
        for (int j = nums[i-1]; j <= target; ++j) {
            std::cout << "dp[" << i << "][" << j << "] = dp[" << i - 1 << "][" << j << "] || dp[" << i-1 << "][" << j-nums[i-1] << "]" << std::endl;
            dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i-1]];
            print_dp(dp);
        }
    }
    return dp[N][target];
}

bool canPartitionCmp(const std::vector<int>& nums) {
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2 != 0) return false;
    int target = sum / 2;
    int N = nums.size();
    auto dp = std::vector<bool>(target+1, false);
    dp[0] = true;
    for (int i = 1; i <= N; ++i) {
        for (int j = target; j >= nums[i-1]; --j) {
            dp[j] = dp[j] || dp[j-nums[i-1]];
        }
    }
    return dp[target];
}

TEST(canPartition, a) {
    auto input = std::vector<int>{1, 5, 11, 5};
    bool output = true;
    EXPECT_EQ(canPartition(input), output);
}

TEST(canPartition, b) {
    auto input = std::vector<int>{1, 2, 3, 5};
    bool output = false;
    EXPECT_EQ(canPartition(input), output);
}

TEST(canPartition, b1) {
    auto input = std::vector<int>{1, 2, 3, 8};
    bool output = false;
    EXPECT_EQ(canPartition(input), output);
}

TEST(canPartition, c) {
    auto input = std::vector<int>{1};
    bool output = false;
    EXPECT_EQ(canPartition(input), output);
}

TEST(canPartitionCmp, a) {
    auto input = std::vector<int>{1, 5, 11, 5};
    bool output = true;
    EXPECT_EQ(canPartitionCmp(input), output);
}

TEST(canPartitionCmp, b) {
    auto input = std::vector<int>{1, 2, 3, 5};
    bool output = false;
    EXPECT_EQ(canPartitionCmp(input), output);
}

TEST(canPartitionCmp, b1) {
    auto input = std::vector<int>{1, 2, 3, 8};
    bool output = false;
    EXPECT_EQ(canPartitionCmp(input), output);
}

TEST(canPartitionCmp, c) {
    auto input = std::vector<int>{1};
    bool output = false;
    EXPECT_EQ(canPartitionCmp(input), output);
}
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}