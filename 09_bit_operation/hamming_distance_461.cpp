// https://leetcode.com/problems/hamming-distance/

#include <gtest/gtest.h>
#include <climits>

int hamming(int x, int y) {
    int diff = x ^ y;
    int rtn = 0;
    while (diff) {
        if (diff & 1) {
            ++rtn;
        }
        diff >>= 1;
    }
    return rtn;
}

TEST(hamming, a) {
    int x = 1, y = 4;
    int output = 2;
    EXPECT_EQ(hamming(x, y), output);
}

TEST(hamming, b) {
    int x = 1, y = 0;
    int output = 1;
    EXPECT_EQ(hamming(x, y), output);
}

TEST(hamming, c) {
    int x = 0, y = 0;
    int output = 0;
    EXPECT_EQ(hamming(x, y), output);
}

TEST(hamming, d) {
    int x = 0, y = INT_MAX;
    int output = 31;
    EXPECT_EQ(hamming(x, y), output);
}
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}