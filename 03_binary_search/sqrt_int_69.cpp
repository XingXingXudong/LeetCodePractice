#include <gtest/gtest.h>
#include <iostream>

unsigned int sqrt2(unsigned int x) {
    if (x < 4) {
        return 1;
    }

    unsigned int l = 1;
    unsigned int r = x;
    unsigned long mid = 0; // 注意这里mid使用了long，注意溢出的情形

    while ((r - l) > 1) {
        mid = (l + r) / 2;
        // std::cout << "mid: " << mid << std::endl;
        if (mid * mid < x) {
            l = mid;
        } else if (mid * mid > x) {
            r = mid;
        } else {
            return mid;
        }
    }
    return l;
}

// 左闭右闭二分搜索
unsigned int sqrt1(unsigned int x) {
    if (x == 0) {return 0;}
    unsigned int left = 1;
    unsigned int right = x;
    // unsigned long mid = 0;
    unsigned int mid = 0;
    while (true) {
        mid = left + (right - left) / 2;
        if (mid > x / mid) {
            right = mid - 1;
        } else {
            if ((mid + 1) > x / (mid + 1)) {
                return mid;
            }
            left = mid + 1;
        }
    }
}

// 牛顿迭代搜索
int sqrt(int a) {
    if (a == 0)  {return 0;}
    long x = a;
    while (x * x > a) {
        x = (x + (a / x)) / 2;
    }
    return x;
}


TEST(sqrt, a) {
    EXPECT_EQ(sqrt(1), 1);
    EXPECT_EQ(sqrt(2), 1);
    EXPECT_EQ(sqrt(3), 1);
}

TEST(sqrt, b) {
    EXPECT_EQ(sqrt(4), 2);
    EXPECT_EQ(sqrt(5), 2);
    EXPECT_EQ(sqrt(6), 2);
    EXPECT_EQ(sqrt(7), 2);
    EXPECT_EQ(sqrt(8), 2);
    EXPECT_EQ(sqrt(9), 3);
}

TEST(sqrt, c) {
    EXPECT_EQ(sqrt(99), 9);
    EXPECT_EQ(sqrt(100), 10);
    EXPECT_EQ(sqrt(101), 10);
}

TEST(sqrt, d) {
    EXPECT_EQ(sqrt(2147395599), 46339);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}