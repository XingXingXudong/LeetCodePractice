// https://leetcode.com/problems/permutations/

#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

/* 
首先，明确求全排列，基于交换方法的算法步骤如下，以123说明
位置1和位置1交换：1 2 3
     位置2位置3交换 1 3，2
位置1和位置2交换：2 1 3
     位置2和位置3交换 2 3 1
位置1和位置3交换：3 2 1
     位置2和位置3交换：3 1 2
*/

bool is_same(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b) {
    auto set_a = std::set<std::vector<int>>{};
    auto set_b = std::set<std::vector<int>>{};
    for(const auto& x: a) {
        set_a.insert(x);
    }
    for(const auto& x: b) {
        set_b.insert(x);
    }
    return set_a == set_b;
}

void print_matrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row: matrix) {
        for (auto x: row) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> permute_stl(std::vector<int>& nums) {
    auto ans = std::vector<std::vector<int>>{};
    do {
        ans.push_back(nums);
    } while(std::next_permutation(nums.begin(), nums.end()));
    return ans;
}

void backtrans(std::vector<int>& nums, size_t level, std::vector<std::vector<int>>& ans){
    if (level == nums.size() - 1) {
        ans.push_back(nums);
    }
    for (size_t i = level; i < nums.size(); ++i) {
        std::swap(nums[i], nums[level]);
        backtrans(nums, level + 1, ans);
        std::swap(nums[i], nums[level]);
    }
}

std::vector<std::vector<int>> permute_recursive(std::vector<int>& nums) {
    auto ans = std::vector<std::vector<int>>{};
    backtrans(nums, 0, ans);
    return ans;
}


TEST(permute, a) {
    auto input = std::vector<int>{1, 2, 3};
    auto output = permute_stl(input);
    print_matrix(output);
    EXPECT_TRUE(is_same(permute_recursive(input), output));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}