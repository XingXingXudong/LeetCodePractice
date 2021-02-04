// https://leetcode.com/problems/base-7/

#include <vector>
#include <string>
#include <gtest/gtest.h>

std::string base7(int num) {
    if (num == 0) {
        return "0";
    }
    std::string rtn{};
    bool is_neg = num < 0 ? true : false;
    if (is_neg) {
        num = -num;
    }
    while(num) {
        int a = num / 7;
        int b = num % 7;
        rtn = std::to_string(b) + rtn;
        num = a;
    }
    if (is_neg) {
        rtn = "-" + rtn;
    }
    return rtn;
}

TEST(base7, a) {
    int input = 100;
    const std::string output{"202"};
    // EXPECT_STREQ(base7(input), output);
    EXPECT_EQ(base7(input), output);
}

TEST(base7, b) {
    int input = -10;
    const std::string output{"-13"};
    // EXPECT_STREQ(base7(input), output);
    EXPECT_EQ(base7(input), output);
}

TEST(base7, c) {
    int input = -7;
    const std::string output{"-10"};
    // EXPECT_STREQ(base7(input), output);
    EXPECT_EQ(base7(input), output);
}

TEST(base7, d) {
    int input = 7;
    const std::string output{"10"};
    // EXPECT_STREQ(base7(input), output);
    EXPECT_EQ(base7(input), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}