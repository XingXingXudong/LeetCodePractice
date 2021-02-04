// https://leetcode.com/problems/reverse-bits/

#include <gtest/gtest.h>

uint32_t reverse(uint32_t x) {
    uint32_t rtn = 0;
    for (int i = 0; i < 32; ++i) {
        rtn <<= 1;
        rtn +=  x & 1;
        x >>= 1;
    }
    return rtn;
}


TEST(reverse, a) {
    uint32_t a = 43261596;
    uint32_t b =  964176192;
    EXPECT_EQ(reverse(a), b);
}

TEST(reverse, b) {
    uint32_t a = 4294967293;
    uint32_t b = 3221225471;
    EXPECT_EQ(reverse(a), b);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}