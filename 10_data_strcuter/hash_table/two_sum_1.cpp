// https://leetcode.com/problems/two-sum/

#include <gtest/gtest.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

bool isEqual(const std::vector<int>& a, const std::vector<int>& b) {
    auto set_a = std::unordered_set<int>(a.begin(), a.end());
    auto set_b = std::unordered_set<int>(b.begin(), b.end());
    return set_a == set_b;
}

std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    auto map = std::unordered_map<int, int>{};
    // 在进入HashMap中的同时完成检索
    for (int i = 0; i < (int)nums.size(); ++i) {
        auto pos = map.find(target - nums[i]);
        if (pos == map.end()) {
            map[nums[i]] = i;
        } else {
            return std::vector<int>{i, pos->second};
        }
    }
    return std::vector<int>{};
}

TEST(towSum, a) {
    auto nums = std::vector<int>{2, 7, 11, 15};
    int target = 9;
    auto output = std::vector<int>{0, 1};
    EXPECT_TRUE(isEqual(output, twoSum(nums, target)));
}

TEST(towSum, b) {
    auto nums = std::vector<int>{3, 2, 4};
    int target = 6;
    auto output = std::vector<int>{2, 1};
    EXPECT_TRUE(isEqual(output, twoSum(nums, target)));
}

TEST(towSum, c) {
    auto nums = std::vector<int>{3, 3};
    int target = 6;
    auto output = std::vector<int>{0, 1};
    EXPECT_TRUE(isEqual(output, twoSum(nums, target)));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}