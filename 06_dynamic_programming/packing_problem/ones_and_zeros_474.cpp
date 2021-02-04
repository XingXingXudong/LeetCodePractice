// https://leetcode.com/problems/ones-and-zeroes/

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>

void ones_and_zeros(const std::string& str, int& zeros, int& ones) {
    zeros = 0;
    ones = 0;
    for(const auto& x: str) {
        if (x == '1') {
            ++ones;
        } else {
            ++zeros;
        }
    }
}

int oneAndZeros(const std::vector<std::string>& strs, int m, int n) {
    auto dp = std::vector<std::vector<int>>(m+1, std::vector<int>(n+1, 0));
    int  zeros = 0, ones = 0;
    for (const auto& str: strs) {
        ones_and_zeros(str, zeros, ones);
        for (int i = m; i >= zeros; --i) {
            for (int j = n; j >= ones; --j) {
                dp[i][j] = std::max(dp[i][j], dp[i-zeros][j-ones]+1);
            }
        }
    }
    return dp[m][n];
}

TEST(oneAndZeros, a) {
    auto input = std::vector<std::string>{"10","0001","111001","1","0"};
    int m = 5, n = 3;
    int output = 4;
    EXPECT_EQ(oneAndZeros(input, m, n), output);
}

TEST(oneAndZeros, b) {
    auto input = std::vector<std::string>{"10","0","1"};
    int m = 1, n = 1;
    int output = 2;
    EXPECT_EQ(oneAndZeros(input, m, n), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}