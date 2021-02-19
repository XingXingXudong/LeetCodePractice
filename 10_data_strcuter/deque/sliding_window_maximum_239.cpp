// https://leetcode.com/problems/sliding-window-maximum/
#include <gtest/gtest.h>
#include <vector>
#include <deque>

std::vector<int> slidingWindow(const std::vector<int>& nums, int k) {
    // max_deque中存放窗口中最大值的索引
    auto max_deque = std::deque<int>{};
    auto ans = std::vector<int>{};
    for (int i = 0; i < (int)nums.size(); ++i) {
        // 如果队列不为空，且窗口左端已经到了之前窗口中最大值所在的索引处，则需要删除队列左端的值
        if (!max_deque.empty() && max_deque.front() == i - k) {
            max_deque.pop_front();
        }
        // 如果队列右端的索引处的值，小于当前位置处的值，则从右端弹出；
        while (!max_deque.empty() && nums[max_deque.back()] < nums[i]) {
            max_deque.pop_back();
        }
        // 从右侧入队
        max_deque.push_back(i);
        if (i >= k - 1) {
            // 在窗口内，压入结果中
            ans.push_back(nums[max_deque.front()]);
        }
    }
    return ans;
}

TEST(slidingWindow, a) {
    auto nums = std::vector<int>{1,3,-1,-3,5,3,6,7};
    int k = 3;
    auto output = std::vector<int>{3,3,5,5,6,7};
    EXPECT_TRUE(output == slidingWindow(nums, k));
}

TEST(slidingWindow, b) {
    auto nums = std::vector<int>{1};
    int k = 1;
    auto output = std::vector<int>{1};
    EXPECT_TRUE(output == slidingWindow(nums, k));
}

TEST(slidingWindow, c) {
    auto nums = std::vector<int>{9, 11};
    int k = 2;
    auto output = std::vector<int>{11};
    EXPECT_TRUE(output == slidingWindow(nums, k));
}

TEST(slidingWindow, d) {
    auto nums = std::vector<int>{1, -1};
    int k = 1;
    auto output = std::vector<int>{1, -1};
    EXPECT_TRUE(output == slidingWindow(nums, k));
}

TEST(slidingWindow, e) {
    auto nums = std::vector<int>{4, -2};
    int k = 1;
    auto output = std::vector<int>{4, -2};
    EXPECT_TRUE(output == slidingWindow(nums, k));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}