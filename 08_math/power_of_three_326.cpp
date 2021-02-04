// https://leetcode.com/problems/power-of-three/

#include <iostream>
#include <gtest/gtest.h>
#include <cmath>
#include <climits>

bool powerOfThree(int num) {
    // 下面的解法会受到浮点数的精度的影响正确性，比如4782968
    // float a = log(num * 1.0) / log(3 * 1.0);
    // float b = fmod(a, 1);
    // std::cout << a << ": " << b << std::endl;
    // return std::fabs(b - 0.0) < FLT_EPSILON;

    // 正确
    // return num > 0 && 1162261467 % num == 0;

    if (num < 1) {
        return false;
    }
    while (num > 1) {
        if (num % 3 != 0) {
            return false;
        }
        num /= 3;
    }
    return true;
}

TEST(powerofThree, b1) {
    int num = 4782968;
    EXPECT_FALSE(powerOfThree(num));
}

TEST(powerOfThree, a1) {
    int num = 243;
    EXPECT_TRUE(powerOfThree(num));
}


TEST(powerOfThree, a) {
    int num = 0;
    EXPECT_FALSE(powerOfThree(num));
}

TEST(powerOfThree, b) {
    int num = 3;
    EXPECT_TRUE(powerOfThree(num));
}

TEST(powerOfThree, c) {
    int num = 6;
    EXPECT_FALSE(powerOfThree(num));
}

TEST(powerOfThree, d) {
    int num = 9;
    EXPECT_TRUE(powerOfThree(num));
}

TEST(powerOfThree, e) {
    int num = 45;
    EXPECT_FALSE(powerOfThree(num));
}

int main(int argc, char* argv[]) {
    for (int i = 1; i < 10; ++i) {
        std::cout << "fmod(" << i << ", 1) = " << fmod(i*1.0, 1) << std::endl;
    }
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}