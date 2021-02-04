// https://leetcode.com/problems/decode-ways/

#include <iostream>
#include <vector>
#include <string>
#include <gtest/gtest.h>

int decode(const std::string& s) {
    int n = s.length();
    if (n == 0) return 0;
    int prev = s[0] - '0';
    if (!prev) return 0;
    if (n == 1) return 1;
    auto dp = std::vector<int>(n+1, 1);
    for (int i = 2; i <= n; ++i) {
        int cur = s[i-1] - '0';
        if ((prev == 0 || prev > 2) && cur == 0) {
            return 0;
        }
        if ((prev < 2 && prev > 0) || (prev == 2 && cur < 7)) {
            if (cur) {
                dp[i] = dp[i-2] + dp[i-1];
            } else {
                dp[i] = dp[i-2];
            }
        } else {
            dp[i] = dp[i-1];
        }
        prev = cur;
    }
    return dp[n];
}

int decode_ways(const std::string& s) {
    if (s.length() < 1) {
        return 0;
    }
    auto dp = std::vector<int>(s.length(), 0);
    if (s[0] == '0') {
        return 0;
    }
    dp[0] = 1;
    for (size_t i = 1; i < s.length(); ++i) {
        if (s[i] == '0' && s[i-1] != '1' && s[i-1] != '2') {
            return 0;
        }
        if (s[i] == '0') {
            if (i == 1) {
                dp[i] = dp[i-1];
            } else {
                dp[i] = dp[i-2];
            }
            continue;
        }
        if ((s[i-1] == '1') || (s[i-1] == '2' && s[i] - '0' < 7)) {
            if (i > 1) {
                dp[i] = dp[i-1] + dp[i - 2];
            } else {
                dp[i] = dp[i-1] + 1;
            }
        } else {
            dp[i] = dp[i-1];
        }
    }
    return dp.back();
}

TEST(decode_ways, a) {
    const std::string input = "12";
    int output = 2;
    EXPECT_EQ(decode_ways(input), output);
}

TEST(decode_ways, b) {
    const std::string input = "226";
    int output = 3;
    EXPECT_EQ(decode_ways(input), output);
}

TEST(decode_ways, c) {
    const std::string input = "0";
    int output = 0;
    EXPECT_EQ(decode_ways(input), output);
}

TEST(decode_ways, d) {
    const std::string input = "1";
    int output = 1;
    EXPECT_EQ(decode_ways(input), output);
}

TEST(decode_ways, e) {
    const std::string input = "10";
    int output = 1;
    EXPECT_EQ(decode_ways(input), output);
}

TEST(decode_ways, f) {
    const std::string input = "1220";
    int output = 2;
    EXPECT_EQ(decode_ways(input), output);
}

TEST(decode_ways, g) {
    const std::string input = "12101202012712231";
    int output = 20;
    EXPECT_EQ(decode_ways(input), output);
}

TEST(decode_ways, h) {
    const std::string input ="2611055971756562";
    int output = 4;
    EXPECT_EQ(decode_ways(input), output);
}

TEST(decode, a) {
    const std::string input = "12";
    int output = 2;
    EXPECT_EQ(decode(input), output);
}

TEST(decode, b) {
    const std::string input = "226";
    int output = 3;
    EXPECT_EQ(decode(input), output);
}

TEST(decode, c) {
    const std::string input = "0";
    int output = 0;
    EXPECT_EQ(decode(input), output);
}

TEST(decode, d) {
    const std::string input = "1";
    int output = 1;
    EXPECT_EQ(decode(input), output);
}

TEST(decode, e) {
    const std::string input = "10";
    int output = 1;
    EXPECT_EQ(decode(input), output);
}

TEST(decode, f) {
    const std::string input = "1220";
    int output = 2;
    EXPECT_EQ(decode(input), output);
}

TEST(decode, g) {
    const std::string input = "12101202012712231";
    int output = 20;
    EXPECT_EQ(decode(input), output);
}

TEST(decode, h) {
    const std::string input ="2611055971756562";
    int output = 4;
    EXPECT_EQ(decode(input), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}