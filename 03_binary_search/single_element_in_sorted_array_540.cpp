// https://leetcode.com/problems/single-element-in-a-sorted-array
#include <gtest/gtest.h>
#include <vector>
#include <iostream>

int findEle(const std::vector<int>& nums) {
    if (nums.size() % 2 == 0) {
        throw std::invalid_argument("Invalid parameter.");
    }
    if (nums.size() == 1) {
        return nums[0];
    }
    int left = 0, right = nums.size(), mid = 0;
    while (left <= right) {
        mid = (left + right) / 2;
        if ((mid == 0 && nums[mid] != nums[mid+1]) 
            || (mid == nums.size() - 1 && nums[mid] != nums[mid-1])
            || (nums[mid] != nums[mid + 1] && nums[mid] != nums[mid - 1])
            ) {
            // return nums[mid];
            break;
        }
        if (nums[mid] == nums[mid - 1]) {
            if ((mid - left) % 2 == 1) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        } else {
            if ((mid - left) % 2 == 0) {
                left = mid + 2;
            } else {
                right = mid;
            }
        }
    }
    return nums[mid];
}

TEST(findEle, a1) {
    auto input = std::vector<int>{1, 2, 2, 3, 3};
    EXPECT_EQ(findEle(input), 1);
}

TEST(findEle, a) {
    auto input = std::vector<int>{1,1,2,3,3,4,4,8,8};
    auto output = 2;
    EXPECT_EQ(findEle(input), output);
}

TEST(findEle, b) {
    auto input = std::vector<int>{3,3,7,7,10,11,11};
    auto output = 10;
    EXPECT_EQ(findEle(input), output);
}

TEST(findEle, c) {
    auto input = std::vector<int>{1,3,3,7,7,11,11};
    auto output = 1;
    EXPECT_EQ(findEle(input), output);
}

TEST(findEle, d) {
    auto input = std::vector<int>{3,3,7,7,11,11,13};
    auto output = 13;
    EXPECT_EQ(findEle(input), output);
}

TEST(findEle, e) {
    auto input = std::vector<int>{1};
    EXPECT_EQ(findEle(input), 1);
}

TEST(findEle, exception) {
    auto input = std::vector<int>{};
    EXPECT_THROW(findEle(input), std::invalid_argument);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
