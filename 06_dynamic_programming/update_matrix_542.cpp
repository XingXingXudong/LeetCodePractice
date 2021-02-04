// https://leetcode.com/problems/01-matrix/

#include <vector>
#include <iostream>
#include <gtest/gtest.h>
#include <climits>
#include <algorithm>

bool is_equal(const std::vector<std::vector<int>>& a, std::vector<std::vector<int>>& b) {
    if (a.size() != b.size() || a[0].size() != b[0].size()) {
        return false;
    }
    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < a[i].size(); ++j) {
            if (a[i][j] != b[i][j]) {
                return false;
            }
        }
    }
    return true;
}

std::vector<std::vector<int>> update(const std::vector<std::vector<int>>& matrix) {
    if (matrix.empty()) {
        return {};
    }
    int row = matrix.size(), col = matrix[0].size();
    // 注意这里的INT_MAX，由于在DP的过程中，会有在DP上加1的操作，选择不当会有溢出
    auto dp = std::vector<std::vector<int>>(row, std::vector<int>(col, INT_MAX - 4));
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (matrix[i][j] == 0) {
                dp[i][j] = 0;
            } else {
                if (i > 0) {
                    dp[i][j] = std::min(dp[i][j], dp[i-1][j] + 1);
                }
                if (j > 0) {
                    dp[i][j] = std::min(dp[i][j], dp[i][j-1] + 1);
                }
            }
        }
    }
    for (int i = row - 1 ; i >= 0; --i) {
        for (int j = col - 1; j >= 0; --j) {
            if (matrix[i][j] != 0) {
                if (i < row - 1) {
                    dp[i][j] = std::min(dp[i][j], dp[i + 1][j] + 1);
                }
                if (j < col - 1) {
                    dp[i][j] = std::min(dp[i][j], dp[i][j + 1] + 1);
                }
            }
        }
    }
    return dp;
}

TEST(is_equal, a) {
    auto input = std::vector<std::vector<int>> {
       {0,0,0},
       {0,1,0},
       {0,0,0}
    };
    auto output = std::vector<std::vector<int>> {
       {0,0,0},
       {0,1,0},
       {0,0,0}
    };
    EXPECT_TRUE(is_equal(input, output));
}


TEST(update, a) {
    auto input = std::vector<std::vector<int>> {
       {0,0,0},
       {0,1,0},
       {0,0,0}
    };
    auto output = std::vector<std::vector<int>> {
       {0,0,0},
       {0,1,0},
       {0,0,0}
    };
    EXPECT_TRUE(is_equal(update(input), output));
}

TEST(update, b) {
    auto input = std::vector<std::vector<int>> {
       {0,0,0},
       {0,1,0},
       {1,1,1}
    };
    auto output = std::vector<std::vector<int>> {
       {0,0,0},
       {0,1,0},
       {1,2,1}
    };
    EXPECT_TRUE(is_equal(update(input), output));
}

TEST(update, c) {
    auto input = std::vector<std::vector<int>> {
        {1,1,0,0,1,0,0,1,1,0},{1,0,0,1,0,1,1,1,1,1},{1,1,1,0,0,1,1,1,1,0},{0,1,1,1,0,1,1,1,1,1},{0,0,1,1,1,1,1,1,1,0},{1,1,1,1,1,1,0,1,1,1},{0,1,1,1,1,1,1,0,0,1},{1,1,1,1,1,0,0,1,1,1},{0,1,0,1,1,0,1,1,1,1},{1,1,1,0,1,0,1,1,1,1}
    };
    auto output = std::vector<std::vector<int>> {
        {2,1,0,0,1,0,0,1,1,0},{1,0,0,1,0,1,1,2,2,1},{1,1,1,0,0,1,2,2,1,0},{0,1,2,1,0,1,2,3,2,1},{0,0,1,2,1,2,1,2,1,0},{1,1,2,3,2,1,0,1,1,1},{0,1,2,3,2,1,1,0,0,1},{1,2,1,2,1,0,0,1,1,2},{0,1,0,1,1,0,1,2,2,3},{1,2,1,0,1,0,1,2,3,4}
    };

    auto rtn = update(input);
    // for (const auto & row: rtn) {
    //     for (auto x: row) {
    //         std::cout << x << " ";
    //     }
    //     std::cout << std::endl;
    // }
    EXPECT_TRUE(is_equal(rtn, output));
}
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}