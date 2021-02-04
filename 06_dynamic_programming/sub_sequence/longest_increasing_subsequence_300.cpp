// https://leetcode.com/problems/longest-increasing-subsequence/
#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <algorithm>

// O(n^2)
int longestSubSeq(const std::vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }
    std::vector<int> dp(nums.size(), 1);
    int rtn = dp[0];
    for (size_t i = 1; i < nums.size(); ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (nums[i] > nums[j]) {
                dp[i] = std::max(dp[i], dp[j] + 1);
            }
        }
        rtn = std::max(rtn, dp[i]);
    }
    return rtn;
}

// O(nlong(n))
int longestSubSeq1(const std::vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }
    std::vector<int> dp{nums[0]};
    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] > dp.back()) {
            dp.push_back(nums[i]);
        } else {
            auto it = std::lower_bound(dp.begin(), dp.end(), nums[i]);
            if (*it > nums[i]) {
                *it = nums[i];
            }
        }
    }
    return static_cast<int>(dp.size());
}

TEST(longestSubSeq1, a) {
    auto input = std::vector<int>{10,9,2,5,3,7,101,18};
    int output = 4;
    EXPECT_EQ(longestSubSeq1(input), output);
}

TEST(longestSubSeq1, b) {
    auto input = std::vector<int>{0, 1, 0, 3, 2, 3};
    int output = 4;
    EXPECT_EQ(longestSubSeq1(input), output);
}

TEST(longestSubSeq1, c) {
    auto input = std::vector<int>{7, 7, 7, 7, 7, 7, 7};
    int output = 1;
    EXPECT_EQ(longestSubSeq1(input), output);
}

TEST(longestSubSeq1, d) {
    auto input = std::vector<int>{3, 2, 1};
    int output = 1;
    EXPECT_EQ(longestSubSeq1(input), output);
}

TEST(longestSubSeq1, e) {
    auto input = std::vector<int>{1};
    int output = 1;
    EXPECT_EQ(longestSubSeq1(input), output);
}

TEST(longestSubSeq, a) {
    auto input = std::vector<int>{10,9,2,5,3,7,101,18};
    int output = 4;
    EXPECT_EQ(longestSubSeq(input), output);
}

TEST(longestSubSeq, b) {
    auto input = std::vector<int>{0, 1, 0, 3, 2, 3};
    int output = 4;
    EXPECT_EQ(longestSubSeq(input), output);
}

TEST(longestSubSeq, c) {
    auto input = std::vector<int>{7, 7, 7, 7, 7, 7, 7};
    int output = 1;
    EXPECT_EQ(longestSubSeq(input), output);
}

TEST(longestSubSeq, d) {
    auto input = std::vector<int>{3, 2, 1};
    int output = 1;
    EXPECT_EQ(longestSubSeq(input), output);
}

TEST(longestSubSeq, e) {
    auto input = std::vector<int>{1};
    int output = 1;
    EXPECT_EQ(longestSubSeq(input), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}