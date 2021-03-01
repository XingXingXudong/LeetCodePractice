// https://leetcode.com/problems/split-array-largest-sum/

#include <gtest/gtest.h>
#include <vector>
#include <numeric>

bool check(std::vector<int>nums, int m, int mid) {
    int sum = 0, cnt = 1;
    for (int x: nums) {
        if (x > mid) {
            return false;
        }
        if (sum + x <= mid) {
            sum += x;
        } else {
            sum = x;
            ++cnt;  // 增加分计数
        }
    }
    return cnt <= m;
}

int split(std::vector<int>nums, int m) {
    int l = 0; 
    int r = std::accumulate(nums.begin(), nums.end(), 0);
    int ans = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(nums, m, mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

TEST(split, a) {
    auto nums = std::vector<int>{7,2,5,10,8};
    int m = 2, output = 18;
    EXPECT_EQ(split(nums, m), output);
}

TEST(split, b) {
    auto nums = std::vector<int>{1,2,3,4,5};
    int m = 2, output = 9;
    EXPECT_EQ(split(nums, m), output);
}

TEST(split, c) {
    auto nums = std::vector<int>{1,4,4};
    int m = 3, output = 4;
    EXPECT_EQ(split(nums, m), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}