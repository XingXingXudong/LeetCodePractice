// https://leetcode.com/problems/power-of-four/

#include <gtest/gtest.h>

bool isPowerOfFour(int n) {
    // return num > 0 && !(num & (num - 1)) && (num & 1431655765);
    return n > 1 && !(n & (n - 1)) && (n & 1431655765);
}

TEST(isPowerOfFour, a) {
    int num = 16;
    EXPECT_TRUE(isPowerOfFour(num));
}

TEST(isPowerOfFour, b) {
    int num = 5;
    EXPECT_FALSE(isPowerOfFour(num));
}

TEST(isPowerOfFour, c) {
    int num = 1;
    EXPECT_FALSE(isPowerOfFour(num));
}

TEST(isPowerOfFour, d) {
    int num = 0;
    EXPECT_FALSE(isPowerOfFour(num));
}

TEST(isPowerOfFour, e) {
    int num = 64;
    EXPECT_TRUE(isPowerOfFour(num));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}