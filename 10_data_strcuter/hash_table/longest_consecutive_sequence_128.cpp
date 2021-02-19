// https://leetcode.com/problems/longest-consecutive-sequence/

#include <gtest/gtest.h>
#include <vector>
#include <unordered_set>
#include <algorithm>

int longsetConsecutive(const std::vector<int>& nums) {
    int longset = 0;
    auto hash_set = std::unordered_set<int>(nums.begin(), nums.end());
    while (!hash_set.empty()) {
        int cur = *(hash_set.begin());
        hash_set.erase(cur);
        int next = cur + 1, prev = cur - 1;
        while (hash_set.count(next)) {
            hash_set.erase(next++);
        }
        while (hash_set.count(prev)) {
            hash_set.erase(prev--);
        }
        longset = std::max(longset, next - prev - 1);
    }
    return longset;
}

TEST(longestConsecutive, a) {
    auto nums = std::vector<int>{100,4,200,1,3,2};
    int output = 4;
    EXPECT_EQ(longsetConsecutive(nums), output);
}

TEST(longestConsecutive, b) {
    auto nums = std::vector<int>{0,3,7,2,5,8,4,6,0,1};
    int output = 9;
    EXPECT_EQ(longsetConsecutive(nums), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}