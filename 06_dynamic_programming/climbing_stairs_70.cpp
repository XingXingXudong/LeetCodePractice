// https://leetcode.com/problems/climbing-stairs/

#include <iostream>
#include <vector>
#include <gtest/gtest.h>

int climbStairs_recurrent(int n) {
    if (n <= 0) {
        return 0;
    }
    if (n < 3) {
        return n;
    }
    int back_one = 2;
    int back_two = 1;
    int current = 0;
    for (int i = 3; i <= n; ++i) {
        current = back_one + back_two;
        std::cout << current << std::endl;
        back_two = back_one;
        back_one = current;
    }
    return current;
}



int climbStairs_recursive(int n) {
    if (n <= 0) {
        return 0;
    }
    if (n < 3) {
        return n;
    }
    return climbStairs_recursive(n - 1) + climbStairs_recursive(n - 2);
}

TEST(climbStairs_recursive, a) {
    int input = 2;
    int output = 2;
    EXPECT_EQ(climbStairs_recursive(input), output);
}

TEST(climbStairs_recursive, b) {
    int input = 3;
    int output = 3;
    EXPECT_EQ(climbStairs_recursive(input), output);
}

TEST(climbStairs_recursive, c) {
    int input = 1;
    int output = 1;
    EXPECT_EQ(climbStairs_recursive(input), output);
}

TEST(climbStairs_recursive, d) {
    int input = 5;
    int output = 8;
    EXPECT_EQ(climbStairs_recursive(input), output);
}
TEST(climbStairs_recursive, e) {
    int input = 45;
    int output = 1836311903;
    EXPECT_EQ(climbStairs_recursive(input), output);
}
TEST(climbStairs_recurrent, a) {
    int input = 2;
    int output = 2;
    EXPECT_EQ(climbStairs_recurrent(input), output);
}

TEST(climbStairs_recurrent, b) {
    int input = 3;
    int output = 3;
    EXPECT_EQ(climbStairs_recurrent(input), output);
}

TEST(climbStairs_recurrent, c) {
    int input = 1;
    int output = 1;
    EXPECT_EQ(climbStairs_recurrent(input), output);
}

TEST(climbStairs_recurrent, d) {
    int input = 5;
    int output = 8;
    EXPECT_EQ(climbStairs_recurrent(input), output);
}

TEST(climbStairs_recurrent, e) {
    int input = 45;
    int output = 1836311903;
    EXPECT_EQ(climbStairs_recurrent(input), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
