// https://leetcode.com/problems/single-number/

#include <vector>
#include <gtest/gtest.h>

int singelNum(std::vector<int> nums) {
    int rtn = 0;
    for (auto x: nums) {
        rtn ^= x;
    }
    return rtn;
}

TEST(singelNum, a) {
    auto input = std::vector<int>{2,2,1};
    int output = 1;
    EXPECT_EQ(singelNum(input), output);
}

TEST(singelNum, b) {
    auto input = std::vector<int>{4,2,1, 1, 2};
    int output = 4;
    EXPECT_EQ(singelNum(input), output);
}

TEST(singelNum, c) {
    auto input = std::vector<int>{1};
    int output = 1;
    EXPECT_EQ(singelNum(input), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}