// https://leetcode.com/problems/longest-common-subsequence/

#include <iostream>
#include <vector>
#include <string>
#include <gtest/gtest.h>


int longestCommonSeq(const std::string& input1, const std::string& input2) {
    if (input1.empty() || input2.empty()) {
        return 0;
    }
    std::vector<std::vector<int>> dp(input1.size() + 1, std::vector<int>(input2.size() + 1, 0));
    for (size_t i = 1; i <= input1.size(); ++i) {
        for (size_t j = 1; j <= input2.size(); ++j) {
            if (input1[i-1] == input2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return dp[input1.size()][input2.size()];
}


TEST(longestCommonSeq, a) {
    const std::string input1{"abcde"};
    const std::string input2{"ace"};
    int output = 3;
    EXPECT_EQ(longestCommonSeq(input1, input2), output);
}

TEST(longestCommonSeq, b) {
    const std::string input1{"abc"};
    const std::string input2{"abc"};
    int output = 3;
    EXPECT_EQ(longestCommonSeq(input1, input2), output);
}

TEST(longestCommonSeq, c) {
    const std::string input1{"abc"};
    const std::string input2{"def"};
    int output = 0;
    EXPECT_EQ(longestCommonSeq(input1, input2), output);
}

TEST(longestCommonSeq, d) {
    const std::string input1{""};
    const std::string input2{"def"};
    int output = 0;
    EXPECT_EQ(longestCommonSeq(input1, input2), output);
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}