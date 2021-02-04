// https://leetcode.com/problems/maximal-square/
#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <algorithm>

int maximal_square(const std::vector<std::vector<char>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) {
        return 0;
    }
    size_t row = matrix.size(), col = matrix[0].size();
    int max_side = 0;
    auto dp = std::vector<std::vector<int>>(row + 1, std::vector<int>(col + 1, 0));
    for (size_t i = 1; i <= row; ++i) {
        for (size_t j = 1; j <= col; ++j) {
            if (matrix[i - 1][j - 1] == '1') {
                dp[i][j] = std::min(dp[i-1][j-1], std::min(dp[i-1][j], dp[i][j-1])) + 1;
            }
            max_side = std::max(max_side, dp[i][j]);
        }
    }
    return max_side * max_side;
}

TEST(maximal_square, a) {
    auto input = std::vector<std::vector<char>>{
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    };
    int output = 4;
    EXPECT_EQ(maximal_square(input), output);
}

TEST(maximal_square, b) {
    auto input = std::vector<std::vector<char>>{
        {'0', '1'}, {'1', '0'}
    };
    int output = 1;
    EXPECT_EQ(maximal_square(input), output);
}

TEST(maximal_square, c) {
    auto input = std::vector<std::vector<char>>{
        {'0'}
    };
    int output = 0;
    EXPECT_EQ(maximal_square(input), output);
}

TEST(maximal_square, d) {
    auto input = std::vector<std::vector<char>>{
        {'1'}
    };
    int output = 1;
    EXPECT_EQ(maximal_square(input), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}