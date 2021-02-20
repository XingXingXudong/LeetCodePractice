// https://leetcode.com/problems/palindromic-substrings/

#include <gtest/gtest.h>
#include <string>

int extendSubstring(const std::string& s, int l, int r) {
    int count = 0;
    while (l >= 0 && r < (int)s.length() && s[r] == s[l]) {
        --l; 
        ++r;
        ++count;
    }
    return count;
}

int countSubstring(const std::string& s) {
    int count = 0;
    for (int i = 0; i < (int)s.length(); ++i) {
        count += extendSubstring(s, i, i);  // 奇数长度的对称子串；
        count += extendSubstring(s, i, i + 1);  // 偶数长度的子串；
    }
    return count;
}

TEST(countSubstring, a) {
    std::string s = "abc";
    int output = 3;
    EXPECT_EQ(countSubstring(s), output);
}

TEST(countSubstring, b) {
    std::string s = "aaa";
    int output = 6;
    EXPECT_EQ(countSubstring(s), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}