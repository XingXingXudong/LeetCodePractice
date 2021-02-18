// https://leetcode.com/problems/the-skyline-problem/

#include <gtest/gtest.h>
#include <vector>
#include <queue>

std::vector<std::vector<int>> getSkyline(const std::vector<std::vector<int>>& buildings) {
    std::vector<std::vector<int>> ans;
    std::priority_queue<std::pair<int, int>> max_heap;   // 高度，右端
    int i = 0, len = buildings.size();
    int cur_x, cur_h;
    while (i < len || !max_heap.empty()) {
        if (max_heap.empty() || (i < len && buildings[i][0] <= max_heap.top().second)) {
            cur_x = buildings[i][0];
            while (i < len && cur_x == buildings[i][0]) {
                max_heap.emplace(buildings[i][2], buildings[i][1]);
                ++i; // 高度没有变化，max_heap堆定的元素；
            }
        } else {
            cur_x = max_heap.top().second;
            while (!max_heap.empty() && cur_x >= max_heap.top().second) {
                max_heap.pop();
            }
        }
        cur_h = max_heap.empty() ? 0: max_heap.top().first;
        if (ans.empty() || cur_h != ans.back()[1]) {
            ans.push_back({cur_x, cur_h});
        }
    }
    return ans;
}


TEST(getSkyline, a) {
    auto buildings = std::vector<std::vector<int>>{{2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}};
    auto output = std::vector<std::vector<int>>{{2,10},{3,15},{7,12},{12,0},{15,10},{20,8},{24,0}};
    EXPECT_TRUE(getSkyline(buildings) == output);
}

TEST(getSkyline, b) {
    auto buildings = std::vector<std::vector<int>>{{0,2,3},{2,5,3}};
    auto output = std::vector<std::vector<int>>{{0,3},{5,0}};
    EXPECT_TRUE(getSkyline(buildings) == output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}