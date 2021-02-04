#include <gtest/gtest.h>
#include <vector>
#include <iostream>

// https://leetcode.com/problems/search-in-rotated-sorted-array-ii/submissions/

bool hasNum(const std::vector<int>& input, int target) {
    if (input.empty()) {
        return false;
    }
    size_t left = 0, right = input.size() - 1, mid = 0;
    while (left <= right)
    {
        mid = (left + right) / 2;
        if (input[mid] == target)  {
            return true;
        } 
        // 无法判断区间的单调性
        if (input[mid] == input[left]) {
            ++left;
        } else if (input[mid] > input[left]) { // 在左半的升序区间中，且目标值也在左半区间中
            // input[mid] 位于左边有序区间，则target的位置有如下三种情况：
            // 1. target < input[mid] && target >= input[left]，即位于左边有序区间的左半边，此时应该令right = mid - 1;
            // 2. target > input[mid], 即位于左边有序区间的右半边，此时应该令left = mid + 1;
            // 3. target < input[left] (蕴含target < input[mid])，即位于右边的有序区间，此时应该令left = mid + 1;
            // 通过1，2，3可知，问题的关键在于，mid位于左边有序区间时，若target < input[mid]，需要注意target可能在左边有序区间，
            // 也可能在右边有序区间。 综上有如下代码：
            if (target >= input[left] && target < input[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else { // 在右边的升序数组中
            if (target > input[mid] && target <= input[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return false;
}

TEST(hasNum, a) {
    auto input = std::vector<int>{2, 5, 6, 0, 0, 1, 2};
    auto target = 0;
    EXPECT_TRUE(hasNum(input, target));
}

TEST(hasNum, b) {
    auto input = std::vector<int>{2, 5, 6, 0, 0, 1, 2};
    auto target = 2;
    EXPECT_TRUE(hasNum(input, target));
}

TEST(hasNum, c) {
    auto input = std::vector<int>{3, 5, 6, 0, 0, 1, 2};
    auto target = 3;
    EXPECT_TRUE(hasNum(input, target));
}

TEST(hasNum, e) {
    auto input = std::vector<int>{3, 5, 6, 0, 0, 1, 2};
    auto target = 2;
    EXPECT_TRUE(hasNum(input, target));
}

TEST(hasNum, f) {
    auto input = std::vector<int>{3, 5, 6, 0, 0, 1, 2};
    auto target = 4;
    EXPECT_FALSE(hasNum(input, target));
}

TEST(hasNum, g) {
    auto input = std::vector<int>{4, 5, 6, 0, 0, 1, 2};
    auto target = 3;
    EXPECT_FALSE(hasNum(input, target));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}