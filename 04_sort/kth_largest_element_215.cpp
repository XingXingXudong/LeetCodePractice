// 快速选择，k-thElement问题
// https://leetcode.com/problems/kth-largest-element-in-an-array/
// 相当于stdlib中的nth_element函数的功能。

#include <gtest/gtest.h>
#include <vector>
#include <iostream>

void print_nums(const std::vector<int>& nums) {
    for (auto x: nums) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

size_t partition(std::vector<int>& nums, size_t low, size_t high) {
    int pivot_key = nums[low];
    while(low < high) {
        while (low < high && nums[high] >= pivot_key) --high;
        nums[low] = nums[high];
        while (low < high && nums[low] <= pivot_key) ++low;
        nums[high] = nums[low];
    }
    nums[low] = pivot_key;
    // std::cout << "pivot: " << low << ", ";
    // print_nums(nums);
    return low;
}

int kth_large(const std::vector<int>& nums, size_t k) {
    if (k > nums.size() || k == 0) {
        throw std::invalid_argument("Invalid parameter.");
    }
    k = nums.size() - k;
    auto nums_ = std::vector<int>{nums};
    size_t low = 0, high = nums_.size() - 1, pivot = 0;
    while (low <= high) {
        pivot = partition(nums_, low, high);
        if (pivot == k) {
            break;
        } else if (pivot < k) {
            low = pivot + 1;
        } else if (pivot > k) {
            high = pivot - 1;
        }
    }
    return nums_[pivot];
}

TEST(kth_large, a) {
    auto input = std::vector<int>{3,2,1,5,6,4};
    size_t k = 2;
    int output = 5;
    EXPECT_EQ(kth_large(input, k), output);
}

TEST(kth_large, b) {
    auto input = std::vector<int>{3,2,3,1,2,4,5,5,6};
    size_t k = 4;
    int output = 4;
    EXPECT_EQ(kth_large(input, k), output);
}

TEST(kth_large, c) {
    auto input = std::vector<int>{3};
    size_t k = 1;
    int output = 3;
    EXPECT_EQ(kth_large(input, k), output);
}

TEST(kth_large, e1) {
    auto input = std::vector<int>{1, 2};
    size_t k = 3;
    EXPECT_THROW(kth_large(input, k), std::invalid_argument);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}