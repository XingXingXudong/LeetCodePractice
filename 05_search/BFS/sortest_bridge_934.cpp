// https://leetcode.com/problems/shortest-bridge/

#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <queue>


std::vector<std::pair<int, int>> get_neighbors(const std::pair<int, int>& xy, std::vector<std::vector<bool>>& visited) {
    auto directions = std::vector<int>{-1, 0, 1, 0, -1};
    auto rtn = std::vector<std::pair<int, int>>{};
    int i, j;
    for (int k = 0; k < 4; ++k) {
        i = xy.first + directions[k];
        j = xy.second + directions[k+1];
        if (i >= 0 && i < (int)visited.size() && j >= 0 && j < (int)visited[i].size() && !visited[i][j]) {
            visited[i][j] = true;
            rtn.push_back({i, j});
            
        }
    }
    return rtn;
}

int sortestBridge(std::vector<std::vector<int>>& A) {
    if (A.empty() || A[0].empty()) {
        throw std::invalid_argument("Invalid input.");
    }
    auto visited = std::vector<std::vector<bool>>(A.size(), std::vector<bool>(A[0].size(), false));
    auto island1 = std::queue<std::pair<int, int>>{};
    auto ocean = std::queue<std::pair<int, int>>{};
    // 找到属于其中一个岛屿的位置
    for(size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < A[i].size(); ++j) {
            if (A[i][j] == 1) {
                island1.push({i, j});
                visited[i][j] = true;
                break;
            }
        }
        if (!island1.empty()) {
            break;
        }
    }
    // 遍历属于该岛屿的所有位置，标记为已经访问；
    // 并且，记录该岛屿邻接的海洋位置，标记为已经访问；
    while(!island1.empty()){
        for (const auto& coord: get_neighbors(island1.front(), visited)) {
            if (A[coord.first][coord.second] == 1) {
                island1.push(coord);
            } else {
                ocean.push(coord);
            }
        }
        island1.pop();
    }
    if (ocean.empty()) {
        return 0;
    }
    ocean.push({-1, -1});    // 插入广度搜索中，层的标识
    int sortest_bridge = 1;
    while (!ocean.empty()) {
        if (ocean.front().first == -1) {
            ++sortest_bridge;
            if (ocean.empty()) {
                return sortest_bridge; // 队列为空，遍历结束；如果不存在第二个岛屿，这个是遍历的最大层数
            } else {
                ocean.push(ocean.front());  // 添加层标识
                ocean.pop();
            }
        }
        for (const auto& coord: get_neighbors(ocean.front(), visited)) {
            if (A[coord.first][coord.second] == 1) {
                return sortest_bridge;    // 搜索到了最短路，已经连接上了另一岛屿
            } else {
                ocean.push(coord);
            }
        }
        ocean.pop();
    }
    return sortest_bridge;
}

TEST(sortestBridge, a) {
    auto input = std::vector<std::vector<int>>{{0, 1}, {1, 0}};
    auto output = 1;
    EXPECT_EQ(sortestBridge(input), output);
}

TEST(sortestBridge, b) {
    auto input = std::vector<std::vector<int>>{{0,1,0},{0,0,0},{0,0,1}};
    auto output = 2;
    EXPECT_EQ(sortestBridge(input), output);
}

TEST(sortestBridge, c) {
    auto input = std::vector<std::vector<int>>{{1,1,1,1,1},{1,0,0,0,1},{1,0,1,0,1},{1,0,0,0,1},{1,1,1,1,1}};
    auto output = 1;
    EXPECT_EQ(sortestBridge(input), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}