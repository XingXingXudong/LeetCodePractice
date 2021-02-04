// https://leetcode.com/problems/2-keys-keyboard/

#include <iostream>
#include <vector>
#include <string>
#include <gtest/gtest.h>
#include <cmath>

int minStep(int n) {
    auto dp = std::vector<int>(n+1, 0);
    int h = std::sqrt(n);
    for (int i = 2; i <= n; ++i) {
        dp[i] = i;
        for (int j = 2; j <= h; ++j) {
            if (i % j == 0) {
                dp[i] = dp[j] + dp[i / j];
                break;
            }
        }
    }
    return dp[n];
}

TEST(minStep, a) {
    int input = 3, output = 3;
    EXPECT_EQ(minStep(input), output);
}

TEST(minStep, b) {
    int input = 1, output = 0;
    EXPECT_EQ(minStep(input), output);
}

TEST(minStep, c) {
    int input = 2, output = 2;
    EXPECT_EQ(minStep(input), output);
}

TEST(minStep, d) {
    int input = 5, output = 5;
    EXPECT_EQ(minStep(input), output);
}

TEST(minStep, e) {
    int input = 6, output = 5;
    EXPECT_EQ(minStep(input), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
