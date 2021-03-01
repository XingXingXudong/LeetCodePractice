// https://leetcode.com/problems/split-array-largest-sum/

#include <gtest/gtest.h>
#include <vector>

TEST(split, a) {
    auto nums = std::vector<int>{7,2,5,10,8};
    int m = 2, output = 18;
    EXPECT_EQ(split(nums, m), output);
}

TEST(split, b) {
    auto nums = std::vector<int>{1,2,3,4,5};
    int m = 2, output = 9;
    EXPECT_EQ(split(nums, m), output);
}

TEST(split, c) {
    auto nums = std::vector<int>{1,4,4};
    int m = 3, output = 4;
    EXPECT_EQ(split(nums, m), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}