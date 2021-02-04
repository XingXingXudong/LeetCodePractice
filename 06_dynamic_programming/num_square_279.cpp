// https://leetcode.com/problems/perfect-squares/

#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <climits>
#include <algorithm>

int num_square(int n) {
    auto dp = std::vector<int>(n + 1, INT_MAX);
    dp[0] = 0;
    for (size_t i = 1; i < dp.size(); ++i) {
        for (size_t j = 1; j * j <= i; ++j) {
            dp[i] = std::min(dp[i], dp[i - j*j] + 1);
        }
    }
    return dp[n];
}

TEST(num_square, e) {
    int input = 3;
    int output = 3;
    EXPECT_EQ(num_square(input), output);
}

TEST(num_square, d) {
    int input = 2;
    int output = 2;
    EXPECT_EQ(num_square(input), output);
}

TEST(num_square, c) {
    int input = 1;
    int output = 1;
    EXPECT_EQ(num_square(input), output);
}

TEST(num_square, b) {
    int input = 12;
    int output = 3;
    EXPECT_EQ(num_square(input), output);
}

TEST(num_square, a) {
    int input = 13;
    int output = 2;
    EXPECT_EQ(num_square(input), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}