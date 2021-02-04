// https://leetcode.com/problems/minimum-path-sum/
#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <algorithm>

int min_path_sum(std::vector<std::vector<int>>& grad) {
    if (grad.empty() || grad[0].empty()) {
        return 0;
    }
    for (size_t i = 1; i < grad.size(); ++i) {
        grad[i][0] += grad[i-1][0];
    }
    for (size_t i = 1; i < grad[0].size(); ++i) {
        grad[0][i] += grad[0][i-1];
    }
    for (size_t i = 1; i < grad.size(); ++i) {
        for (size_t j = 1; j < grad[i].size(); ++j) {
            grad[i][j] += std::min(grad[i][j-1], grad[i-1][j]);
        }
    }
    return grad.back().back();
}

int min_path_sum_compress(const std::vector<std::vector<int>>& grad) {
    size_t row = grad.size(), col = grad[0].size();
    auto dp = std::vector<int>(col, 0);
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            if (i == 0 && j == 0) {
                dp[j] = grad[i][j];
            } else if (i == 0) {
                dp[j] = dp[j-1] + grad[i][j];
            } else if (j == 0) {
                dp[j] = dp[j] + grad[i][j];
            } else {
                dp[j] = grad[i][j] + std::min(dp[j], dp[j-1]);
            }
        }
    }
    return dp.back();
}

TEST(min_path_sum, a) {
    auto input = std::vector<std::vector<int>> {
        {1,3,1},{1,5,1},{4,2,1}
    };
    int output = 7;
    EXPECT_EQ(min_path_sum(input), output);
}

TEST(min_path_sum, b) {
    auto input = std::vector<std::vector<int>> {
        {1}
    };
    int output = 1;
    EXPECT_EQ(min_path_sum(input), output);
}

TEST(min_path_sum, c) {
    auto input = std::vector<std::vector<int>> {};
    int output = 0;
    EXPECT_EQ(min_path_sum(input), output);
}

TEST(min_path_sum, d) {
    auto input = std::vector<std::vector<int>> {{1, 2}, {3, 4}};
    int output = 7;
    EXPECT_EQ(min_path_sum(input), output);
}

TEST(min_path_sum_compress, a) {
    auto input = std::vector<std::vector<int>> {
        {1,3,1},{1,5,1},{4,2,1}
    };
    int output = 7;
    EXPECT_EQ(min_path_sum_compress(input), output);
}

TEST(min_path_sum_compress, b) {
    auto input = std::vector<std::vector<int>> {
        {1}
    };
    int output = 1;
    EXPECT_EQ(min_path_sum_compress(input), output);
}

TEST(min_path_sum_compress, c) {
    auto input = std::vector<std::vector<int>> {};
    int output = 0;
    EXPECT_EQ(min_path_sum_compress(input), output);
}

TEST(min_path_sum_compress, d) {
    auto input = std::vector<std::vector<int>> {{1, 2}, {3, 4}};
    int output = 7;
    EXPECT_EQ(min_path_sum_compress(input), output);
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}