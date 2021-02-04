// https://leetcode.com/problems/factorial-trailing-zeroes/

#include <gtest/gtest.h>

int numZeros(int num) {
    return num < 5 ? 0 : num / 5 + numZeros(num / 5);
}

int numZeros1(int num) {
    int rtn = 0;
    while (num >= 5) {
        rtn += num / 5;
        num /= 5;
    }
    return rtn;
}

TEST(numZeros1, a) {
    int input = 3;
    int output = 0;
    EXPECT_EQ(numZeros1(input), output);
}

TEST(numZeros1, b) {
    int input = 5;
    int output = 1;
    EXPECT_EQ(numZeros1(input), output);
}

TEST(numZeros1, c) {
    int input = 10;
    int output = 2;
    EXPECT_EQ(numZeros1(input), output);
}

TEST(numZeros1, d) {
    int input = 0;
    int output = 0;
    EXPECT_EQ(numZeros1(input), output);
}

TEST(numZeros, a) {
    int input = 3;
    int output = 0;
    EXPECT_EQ(numZeros(input), output);
}

TEST(numZeros, b) {
    int input = 5;
    int output = 1;
    EXPECT_EQ(numZeros(input), output);
}

TEST(numZeros, c) {
    int input = 10;
    int output = 2;
    EXPECT_EQ(numZeros(input), output);
}

TEST(numZeros, d) {
    int input = 0;
    int output = 0;
    EXPECT_EQ(numZeros(input), output);
}

TEST(num, a) {
    for (int i = 0; i < 10^4; ++i) {
        EXPECT_EQ(numZeros(i), numZeros1(i));
    }
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}