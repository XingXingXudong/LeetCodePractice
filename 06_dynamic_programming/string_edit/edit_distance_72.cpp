// https://leetcode.com/problems/edit-distance/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

template<typename T>
void print_dp(const std::vector<std::vector<T>>& dp){
    std::cout << "--------------------" << std::endl;
    for (const auto& vec: dp) {
        for (auto x: vec) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------" << std::endl;
}

int editDistance(const std::string& word1, const std::string& word2) {
    int m = word1.size();
    int n = word2.size();
    auto dp = std::vector<std::vector<int>>(m + 1, std::vector<int>(n + 1, m + n));
    print_dp(dp);
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else {
                dp[i][j] = std::min(dp[i-1][j-1] + (word1[i-1] == word2[j-1] ? 0 : 1),
                                    std::min(dp[i-1][j] + 1, dp[i][j-1] + 1));
            }
            print_dp(dp);
        }
    }
    return dp[m][n];
}

TEST(editDistance, a) {
    const std::string word1 = "ros";
    const std::string word2 = "horse";
    int output = 3;
    EXPECT_EQ(editDistance(word1, word2), output);
}

/*
TEST(editDistance, b) {
    const std::string word1 = "intention";
    const std::string word2 = "execution";
    int output = 5;
    EXPECT_EQ(editDistance(word1, word2), output);
}


TEST(editDistance, c) {
    const std::string word1 = "";
    const std::string word2 = "abc";
    int output = 3;
    EXPECT_EQ(editDistance(word1, word2), output);
}

TEST(editDistance, d) {
    const std::string word1 = "";
    const std::string word2 = "";
    int output = 0;
    EXPECT_EQ(editDistance(word1, word2), output);
}

TEST(editDistance, e) {
    const std::string word1 = "abc";
    const std::string word2 = "abc";
    int output = 0;
    EXPECT_EQ(editDistance(word1, word2), output);
}

TEST(editDistance, f) {
    const std::string word1 = "abch";
    const std::string word2 = "abc";
    int output = 1;
    EXPECT_EQ(editDistance(word1, word2), output);
}

TEST(editDistance, g) {
    const std::string word1 = "habc";
    const std::string word2 = "abc";
    int output = 1;
    EXPECT_EQ(editDistance(word1, word2), output);
}
*/

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}