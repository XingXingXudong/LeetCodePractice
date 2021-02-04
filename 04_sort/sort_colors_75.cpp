// https://leetcode.com/problems/sort-colors/ 

#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <algorithm>

bool is_equal(const std::vector<int>& nums_a, const std::vector<int> nums_b) {
    if (nums_a.size() != nums_b.size()) {
        return false;
    }
    for (size_t i = 0; i < nums_a.size(); ++i) {
        if (nums_a[i] != nums_b[i]) {
            return false;
        }
    }
    return true;
}

void print_nums(const std::vector<int>& nums) {
    for (auto x: nums) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

void sort_colors_simple(std::vector<int>& nums) {
    size_t left = 0, right = nums.size() - 1;
    for (size_t i = 0; i < nums.size(); ++i) {
        while(nums[i] == 2 && i < right) std::swap(nums[i], nums[right--]);
        while(nums[i] == 0 && i > left) std::swap(nums[i], nums[left++]);
    } 
}

void sort_colors(std::vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        while (left < right && nums[left] == 0) ++left;  // left 在非0的位置，1 or 2
        while (left < right && nums[right] == 2) --right;  // right 在非2的位置，0 or 1
        if (left == right) break;
        if (nums[right] == 0) {
            std::swap(nums[left], nums[right]);
            ++left;
        }      
        if (nums[left] == 2) {
            std::swap(nums[left], nums[right]);
            --right;
        } 
        if (nums[left] == nums[right]) {
            int i = left + 1;
            for (;i < right; ++i) {
                if (nums[i] < nums[left]) {
                    std::swap(nums[i], nums[left]);
                    ++left;
                    break;
                }
                if (nums[i] > nums[right]) {
                    std::swap(nums[i], nums[right]);
                    --right;
                    break;
                }
            }
            if (i == right) {
                break;
            }
        }
    }
}

TEST(is_equal, a) {
    auto nums = std::vector<int>{2, 0, 2, 1, 1, 0};
    EXPECT_TRUE(is_equal(nums, nums));
}

TEST(sort_colors_simple, a) {
    auto nums = std::vector<int>{2, 0, 2, 1, 1, 0};
    auto nums_input = std::vector<int>{nums};
    sort_colors_simple(nums_input);
    auto nums_target = std::vector<int>{nums};
    std::sort(nums_target.begin(), nums_target.end());
    EXPECT_TRUE(is_equal(nums_input, nums_target));
}

TEST(sort_colors_simple, b) {
    auto nums = std::vector<int>{0, 2, 1};
    auto nums_input = std::vector<int>{nums};
    sort_colors_simple(nums_input);
    auto nums_target = std::vector<int>{nums};
    std::sort(nums_target.begin(), nums_target.end());
    EXPECT_TRUE(is_equal(nums_input, nums_target));
}

TEST(sort_colors_simple, b1) {
    auto nums = std::vector<int>{2, 0, 1};
    auto nums_input = std::vector<int>{nums};
    sort_colors_simple(nums_input);
    auto nums_target = std::vector<int>{nums};
    std::sort(nums_target.begin(), nums_target.end());
    EXPECT_TRUE(is_equal(nums_input, nums_target));
}

TEST(sort_colors_simple, b2) {
    auto nums = std::vector<int>{1, 0, 2};
    auto nums_input = std::vector<int>{nums};
    sort_colors_simple(nums_input);
    auto nums_target = std::vector<int>{nums};
    std::sort(nums_target.begin(), nums_target.end());
    EXPECT_TRUE(is_equal(nums_input, nums_target));
}

TEST(sort_colors_simple, c) {
    auto nums = std::vector<int>{0};
    auto nums_input = std::vector<int>{nums};
    sort_colors_simple(nums_input);
    auto nums_target = std::vector<int>{nums};
    std::sort(nums_target.begin(), nums_target.end());
    EXPECT_TRUE(is_equal(nums_input, nums_target));
}

TEST(sort_colors_simple, d) {
    auto nums = std::vector<int>{1};
    auto nums_input = std::vector<int>{nums};
    sort_colors_simple(nums_input);
    auto nums_target = std::vector<int>{nums};
    std::sort(nums_target.begin(), nums_target.end());
    EXPECT_TRUE(is_equal(nums_input, nums_target));
}

TEST(sort_colors_simple, e) {
    auto nums = std::vector<int>{2};
    auto nums_input = std::vector<int>{nums};
    sort_colors_simple(nums_input);
    auto nums_target = std::vector<int>{nums};
    std::sort(nums_target.begin(), nums_target.end());
    EXPECT_TRUE(is_equal(nums_input, nums_target));
}

TEST(sort_colors_simple, f) {
    auto nums = std::vector<int>{2, 1};
    auto nums_input = std::vector<int>{nums};
    sort_colors_simple(nums_input);
    auto nums_target = std::vector<int>{nums};
    std::sort(nums_target.begin(), nums_target.end());
    EXPECT_TRUE(is_equal(nums_input, nums_target));
}

TEST(sort_colors_simple, g) {
    auto nums = std::vector<int>{0, 1};
    auto nums_input = std::vector<int>{nums};
    sort_colors_simple(nums_input);
    auto nums_target = std::vector<int>{nums};
    std::sort(nums_target.begin(), nums_target.end());
    EXPECT_TRUE(is_equal(nums_input, nums_target));
}

TEST(sort_colors_simple, A) {
    auto nums = std::vector<int>{1, 0, 1};
    auto nums_input = std::vector<int>{nums};
    sort_colors_simple(nums_input);
    auto nums_target = std::vector<int>{nums};
    std::sort(nums_target.begin(), nums_target.end());
    EXPECT_TRUE(is_equal(nums_input, nums_target));
}

TEST(sort_colors, a) {
    auto nums = std::vector<int>{2, 0, 2, 1, 1, 0};
    auto nums_input = std::vector<int>{nums};
    sort_colors(nums_input);
    auto nums_target = std::vector<int>{nums};
    std::sort(nums_target.begin(), nums_target.end());
    EXPECT_TRUE(is_equal(nums_input, nums_target));
}

TEST(sort_colors, b) {
    auto nums = std::vector<int>{0, 2, 1};
    auto nums_input = std::vector<int>{nums};
    sort_colors(nums_input);
    auto nums_target = std::vector<int>{nums};
    std::sort(nums_target.begin(), nums_target.end());
    EXPECT_TRUE(is_equal(nums_input, nums_target));
}

TEST(sort_colors, b1) {
    auto nums = std::vector<int>{2, 0, 1};
    auto nums_input = std::vector<int>{nums};
    sort_colors(nums_input);
    auto nums_target = std::vector<int>{nums};
    std::sort(nums_target.begin(), nums_target.end());
    EXPECT_TRUE(is_equal(nums_input, nums_target));
}

TEST(sort_colors, b2) {
    auto nums = std::vector<int>{1, 0, 2};
    auto nums_input = std::vector<int>{nums};
    sort_colors(nums_input);
    auto nums_target = std::vector<int>{nums};
    std::sort(nums_target.begin(), nums_target.end());
    EXPECT_TRUE(is_equal(nums_input, nums_target));
}

TEST(sort_colors, c) {
    auto nums = std::vector<int>{0};
    auto nums_input = std::vector<int>{nums};
    sort_colors(nums_input);
    auto nums_target = std::vector<int>{nums};
    std::sort(nums_target.begin(), nums_target.end());
    EXPECT_TRUE(is_equal(nums_input, nums_target));
}

TEST(sort_colors, d) {
    auto nums = std::vector<int>{1};
    auto nums_input = std::vector<int>{nums};
    sort_colors(nums_input);
    auto nums_target = std::vector<int>{nums};
    std::sort(nums_target.begin(), nums_target.end());
    EXPECT_TRUE(is_equal(nums_input, nums_target));
}

TEST(sort_colors, e) {
    auto nums = std::vector<int>{2};
    auto nums_input = std::vector<int>{nums};
    sort_colors(nums_input);
    auto nums_target = std::vector<int>{nums};
    std::sort(nums_target.begin(), nums_target.end());
    EXPECT_TRUE(is_equal(nums_input, nums_target));
}

TEST(sort_colors, f) {
    auto nums = std::vector<int>{2, 1};
    auto nums_input = std::vector<int>{nums};
    sort_colors(nums_input);
    auto nums_target = std::vector<int>{nums};
    std::sort(nums_target.begin(), nums_target.end());
    EXPECT_TRUE(is_equal(nums_input, nums_target));
}

TEST(sort_colors, g) {
    auto nums = std::vector<int>{0, 1};
    auto nums_input = std::vector<int>{nums};
    sort_colors(nums_input);
    auto nums_target = std::vector<int>{nums};
    std::sort(nums_target.begin(), nums_target.end());
    EXPECT_TRUE(is_equal(nums_input, nums_target));
}

TEST(sort_colors, A) {
    auto nums = std::vector<int>{1, 0, 1};
    auto nums_input = std::vector<int>{nums};
    sort_colors(nums_input);
    auto nums_target = std::vector<int>{nums};
    std::sort(nums_target.begin(), nums_target.end());
    EXPECT_TRUE(is_equal(nums_input, nums_target));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}