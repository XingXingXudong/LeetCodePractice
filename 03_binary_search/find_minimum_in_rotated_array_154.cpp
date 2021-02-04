// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/
#include <gtest/gtest.h>
#include <vector>
#include <iostream>

int minInOrder(const std::vector<int>& nums, int left, int right) {
    std::cout << "******************************" << std::endl;
    int min = nums[left];
    for (int i = left + 1; i <= right; ++i) {
        if (nums[i] < min) {
            min = nums[i];
        }
    }
    std::cout << "******************************" << std::endl;
    return min;
}

int findMin(const std::vector<int>& nums) {
    if (nums.size() == 1) {return nums[0];};
    int left = 0, right = nums.size() - 1, mid = 0;
    while (nums[left] >= nums[right]) {
        if ((right - left) == 1) {
            return nums[right];
        }
        mid = (left + right) / 2;
        if (nums[mid] > nums[right]) { // 注意这个边界条件， right是正确的
            left = mid;
        } else if (nums[mid] < nums[left]) {
            right = mid;
        // 这里暗含着条件是 nums[left] == nums[min] == nums[right]，根据前两个条件，这里的else 为：
        // nums[mid] <= nums[right] && nums[mid] >= nums[left], 即：
        // nums[left] <= nums[mid] <= nums[right], 根据旋转数组的定义有：nums[left] >= nums[right]，从而:
        // nums[right] <= nums[left] <= nums[mid] <= nums[right]，即nums[left] == nums[mid] == nums[right]
        // 此时，无法判断，mid是在左边有序区间还是右边有序区间，故而采用顺序搜索的方法，
        } else {
            return minInOrder(nums, left, right);
            // 也可简单的移动一步，感觉可以，但是实测不行，可能是简单的移动破坏了，迭代中，维持的关系（不变量）
            // ++left;
        }
    }
    return nums[left];
}

// 也可以，效率会更好
int findMin1(const std::vector<int>& nums) {
    if (nums.size() == 1) {return nums[0];};
    int left = 0, right = nums.size() - 1, mid = 0;
    while (nums[left] >= nums[right]) {
        if ((right - left) == 1) {
            return nums[right];
        }
        mid = (left + right) / 2;
        if (nums[left] == nums[mid] && nums[left] == nums[right]) {
            return minInOrder(nums, left, right);
        }
        if (nums[mid] >= nums[left]) { // 注意这个边界条件， right是正确的
            left = mid;
        } else if (nums[mid] <= nums[right]) {
            right = mid;
        }
    }
    return nums[left];
}

TEST(min_rotated, a1) {
    auto input = std::vector<int>{3, 1, 1};
    auto target = 1;
    EXPECT_EQ(findMin1(input), target);
}

TEST(min_rotated, b1) {
    auto input = std::vector<int>{1, 0, 1, 1, 1, 1, 1, 1};
    auto target = 0;
    EXPECT_EQ(findMin1(input), target);
}

TEST(min_rotated, c1) {
    auto input = std::vector<int>{1, 1, 1, 1, 1, 0, 1, 1};
    auto target = 0;
    EXPECT_EQ(findMin1(input), target);
}

TEST(min_rotated, a) {
    auto input = std::vector<int>{2,2,2,0,1};
    auto target = 0;
    EXPECT_EQ(findMin1(input), target);
}

TEST(min_rotated, b) {
    auto input = std::vector<int>{2,3,4,5,1};
    auto target = 1;
    EXPECT_EQ(findMin1(input), target);
}

TEST(min_rotated, c) {
    auto input = std::vector<int>{2,3,4,5,6};
    auto target = 2;
    EXPECT_EQ(findMin1(input), target);
}

TEST(min_rotated, d) {
    auto input = std::vector<int>{2, 2, 2, 2};
    auto target = 2;
    EXPECT_EQ(findMin1(input), target);
}

TEST(min_rotated, f) {
    auto input = std::vector<int>{2,2,2,0,1,2};
    auto target = 0;
    EXPECT_EQ(findMin1(input), target);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}