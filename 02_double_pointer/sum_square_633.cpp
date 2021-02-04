#include <gtest/gtest.h>
#include <iostream>
#include <vector>

bool judgeSquareSum(int c) {
    auto nums = std::vector<int>{};
    int num = 0;
    while (num*num <= c) {
        nums.push_back(num*num);
        ++num;
    }
    if (num*num == c) {
        return true;     // square num
    }
    size_t l_idx = 0;
    size_t r_idx = nums.size() - 1;
    int sum = 0;
    while (l_idx <= r_idx) {
        sum = nums[l_idx] + nums[r_idx];
        if (sum < c) {
            ++l_idx;
        } else if (sum > c) {
            --r_idx;
        } else {
            return true;
        }
    }
    return false;
}

TEST(judgeSquareSum, a) {
    EXPECT_TRUE(judgeSquareSum(5));
}

TEST(judgeSquareSum, b) {
    EXPECT_FALSE(judgeSquareSum(3));
}

TEST(judgeSquareSum, c) {
    EXPECT_TRUE(judgeSquareSum(1));
}

TEST(judgeSquareSum, d) {
    EXPECT_TRUE(judgeSquareSum(2));
}

TEST(judgeSquareSum, e) {
    EXPECT_TRUE(judgeSquareSum(4));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}