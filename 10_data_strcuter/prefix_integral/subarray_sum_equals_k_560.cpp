// https://leetcode.com/problems/subarray-sum-equals-k/

#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>

int subarraySum(const std::vector<int>& nums, int k) {
    auto map = std::unordered_map<int, int>{};
    map[0] = 1;
    int acc_sum = 0, count = 0;
    // 遍历当前位置，统计有多少个满足条件的区间
    for (auto x: nums) {
        acc_sum += x;
        // 当前位置为区间的右端点，则map[acc_sum - k]中记录了满足和为k的左端区间的个数；
        count += map[acc_sum - k];
        ++map[acc_sum];
    }
    return count;
}

TEST(subarraySum, a) {
    auto nums = {1,1,1};
    int k = 2;
    int output = 2;
    EXPECT_EQ(subarraySum(nums, k), output);
}

TEST(subarraySum, b) {
    auto nums = {1,2,3}; 
    int k = 3;
    int output = 2;
    EXPECT_EQ(subarraySum(nums, k), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}