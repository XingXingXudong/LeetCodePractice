// https://leetcode.com/problems/regular-expression-matching/
#include <iostream>
#include <vector>
#include <string>
#include <gtest/gtest.h>

bool isMatch(const std::string& s, const std::string& p) {
    int m = s.length(), n = p.length();
    auto dp = std::vector<std::vector<bool>>(m + 1, std::vector<bool>(n + 1, false));
    dp[0][0] = true;
    for (int i = 1; i <= n; ++i) {
        if (p[i - 1] == '*') {
            dp[0][i] = dp[0][i-2];
        }
    }
    // 重点在与根据不同的模式p，讨论动归状态
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '.') {
                dp[i][j] = dp[i-1][j-1];
            } else if (p[j - 1] != '*') {
                dp[i][j] = dp[i-1][j-1] && p[j-1] == s[i-1];
            } else if (p[j - 2] != s[i - 1] && p[j - 2] != '.') {
                dp[i][j] = dp[i][j-2];
            } else {
                dp[i][j] = dp[i][j-1] || dp[i-1][j] || dp[i][j-2];
            }
        }
    }
    return dp[m][n];
}

TEST(isMatch, a) {
    const std::string s = "aa", p = "a";
    EXPECT_FALSE(isMatch(s, p));
}

TEST(isMatch, b) {
    const std::string s = "aa", p = "a*";
    EXPECT_TRUE(isMatch(s, p));
}

TEST(isMatch, c) {
    const std::string s = "ab", p = ".*";
    EXPECT_TRUE(isMatch(s, p));
}

TEST(isMatch, d) {
    const std::string s = "aab", p = "c*a*b";
    EXPECT_TRUE(isMatch(s, p));
}

TEST(isMatch, e) {
    const std::string s = "mississippi", p = "mis*is*p*.";
    EXPECT_FALSE(isMatch(s, p));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}