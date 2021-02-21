// https://leetcode.com/problems/implement-strstr/

#include <string>
#include <gtest/gtest.h>

void calNext(const std::string& needle, std::vector<int>& next) {
    for (int j = 1, p = -1; j < (int)needle.length(); ++j) {
        while (p > - 1 && needle[p+1] != needle[j]) {
            p = next[p]; // 如果下一位置不同，往前回溯
        }
        if (needle[p + 1] == needle[j]) {
            ++p;  // 如果下一位置相同，更新相同的最大前缀和最大后缀长
        }
        next[j] = p;
    }
}

int strStr(const std::string& haystack, const std::string& needle) {
    int k = -1, n = haystack.length(), p = needle.length();
    if (p == 0) {
        return 0;
    }
    auto next = std::vector<int>(p, -1);
    calNext(needle, next);   // 计算next数组
    for (int i = 0; i < n; ++i) {
        while (k > -1 && needle[k + 1] != haystack[i]) {
            k = next[k];   // 有部分匹配，往前回溯
        }
        if (needle[k + 1] == haystack[i]) {
            ++k;
        }
        if (k == p-1) {
            return i - p + 1;   // 完成匹配，返回匹配的起始位置
        }
    }
    return -1;
}

TEST(strStr, a) {
    std::string haystack = "hello";
    std::string needle = "ll";
    int output = 2;
    EXPECT_EQ(strStr(haystack, needle), output);
}

TEST(strStr, b) {
    std::string haystack = "aaaaa";
    std::string needle = "bba";
    int output = -1;
    EXPECT_EQ(strStr(haystack, needle), output);
}

TEST(strStr, c) {
    std::string haystack = "";
    std::string needle = "";
    int output = 0;
    EXPECT_EQ(strStr(haystack, needle), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}