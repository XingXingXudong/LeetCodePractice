// https://leetcode.com/problems/count-binary-substrings/
 
#include <gtest/gtest.h>
#include <string>

int countBinary(const std::string& s) {
    int prev = 0, cur = 1, count = 0;
    for (size_t i = 1; i < s.length(); ++i) {
        if (s[i] == s[i-1]) {
            ++cur;
        } else {
            prev = cur;
            cur = 1;
        }
        if (prev >= cur) {
            ++count;
        }
    }
    return count;
}

TEST(countBinary, a) {
    std::string inputs = "00110011";
    int output = 6;
    EXPECT_EQ(countBinary(inputs), output);
}

TEST(countBinary, b) {
    std::string inputs = "10101";
    int output = 4;
    EXPECT_EQ(countBinary(inputs), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}