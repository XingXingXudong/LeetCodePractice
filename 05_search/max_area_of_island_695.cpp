// https://leetcode.com/problems/max-area-of-island/

#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <set>
#include <stack>
#include <queue>

using matrix_t = std::vector<std::vector<int>>;
using pair_t = std::pair<int, int>;
auto direction = std::vector<int>{-1, 0, 1, 0, -1};


std::vector<std::pair<int, int>> neighbors(const std::vector<std::vector<int>>& grid, int i, int j) {
    int row = grid.size(), col = row > 0 ? grid[0].size() : 0;
    auto rtn = std::vector<std::pair<int, int>>{};
    if (j - 1 >= 0 && grid[i][j - 1] == 1) rtn.push_back(std::pair(i, j-1));
    if (i - 1 >= 0 && grid[i - 1][j] == 1) rtn.push_back(std::pair(i-1, j));
    if (j + 1 < col && grid[i][j+1] == 1) rtn.push_back(std::pair(i, j+1));
    if (i + 1 < row && grid[i+1][j] == 1) rtn.push_back(std::pair(i+1, j));
    return rtn;
}

int max_area_queue(const std::vector<std::vector<int>>& grid) {
    int max_count = 0, count = 0;
    int row = grid.size(), col = row > 0 ? grid[0].size() : 0;

    auto has_contain = std::set<std::pair<int, int>>{};
    auto cells = std::queue<std::pair<int, int>>{};

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (grid[i][j] == 1) {
                count = 0;
                has_contain.clear();
                has_contain.insert(std::pair(i, j));
                cells.push(std::pair(i, j));
                while (!cells.empty()) {
                    auto [r, c] = cells.front();
                    cells.pop();
                    ++count;
                    for (const auto& n: neighbors(grid, r, c)) {
                        if (has_contain.find(n) == has_contain.end()) {
                            cells.push(n);
                            has_contain.insert(n);
                        }
                    }
                }
                max_count = std::max(max_count, count);
            }
        }
    }
    return max_count;
}

int max_area_stack(matrix_t& grid) {
    int row = grid.size(), col = row ? grid[0].size() : 0; 
    int area = 0, local_area = 0;
    int idx_row = 0, idx_col = 0;
    auto island = std::stack<pair_t>{};
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (grid[i][j]) {
                local_area = 1;
                grid[i][j] = 0;
                island.push(std::pair{i, j});
                while (!island.empty()) {
                    auto [r, c] = island.top();
                    island.pop();
                    for (size_t k = 0; k < 4; ++k) {
                        idx_row = r + direction[k];
                        idx_col = c + direction[k + 1];
                        if (idx_row >= 0 && idx_row < row && idx_col >= 0 && idx_col < col && grid[idx_row][idx_col] == 1) {
                            grid[idx_row][idx_col] = 0;
                            ++local_area;
                            island.push(std::pair{idx_row, idx_col});
                        }
                    }
                }
                area = std::max(area, local_area);
            }
        }
    }
    return area;
}

int max_area_dfs_(matrix_t& grid, int i, int j) {
    if (grid[i][j] == 0) return 0;
    int row = grid.size(), col = row ? grid[0].size() : 0;
    grid[i][j] = 0;
    int x, y, area = 1;
    for (int k = 0; k < 4; ++k) {
        x = i + direction[k];
        y = j + direction[k + 1];
        if (x >= 0 && x < row && y >= 0 && y < col && grid[x][y] == 1) {
            area += max_area_dfs_(grid, x, y);
        }
    }
    return area;
}

// 先调用搜索，在搜索中处理边界条件
int max_area_dfs(matrix_t& grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    int row = grid.size(), col = row ? grid[0].size() : 0;
    int area = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (grid[i][j] == 1) {
                area = std::max(area, max_area_dfs_(grid, i, j));
            }
        }
    }
    return area;
}

int max_area_dfs1_(matrix_t& grid, int i, int j) {
    int row = grid.size(), col = row ? grid[0].size() : 0;
    if (i < 0 || j <0 || i >= row || j >= col || grid[i][j] == 0) return 0;
    grid[i][j] = 0;
    return 1 + max_area_dfs1_(grid, i-1, j) + max_area_dfs1_(grid, i+1, j) + max_area_dfs1_(grid, i, j-1) + max_area_dfs1_(grid, i, j+1);
}
// 先处理边界条件，有效时再调用搜索
int max_area_dfs1(matrix_t& grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    int row = grid.size(), col = row ? grid[0].size() : 0;
    int area = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (grid[i][j] == 1) {
                area = std::max(area, max_area_dfs1_(grid, i, j));
            }
        }
    }
    return area;
}

TEST(max_area_queue, a) {
    auto input = std::vector<std::vector<int>>{
         {0,0,1,0,0,0,0,1,0,0,0,0,0},
         {0,0,0,0,0,0,0,1,1,1,0,0,0},
         {0,1,1,0,1,0,0,0,0,0,0,0,0},
         {0,1,0,0,1,1,0,0,1,0,1,0,0},
         {0,1,0,0,1,1,0,0,1,1,1,0,0},
         {0,0,0,0,0,0,0,0,0,0,1,0,0},
         {0,0,0,0,0,0,0,1,1,1,0,0,0},
         {0,0,0,0,0,0,0,1,1,0,0,0,0}};
    EXPECT_EQ(max_area_queue(input), 6);
}

TEST(max_area_queue, b) {
    auto input = std::vector<std::vector<int>> {{0,0,0,0,0,0,0,0}};
    EXPECT_EQ(max_area_queue(input), 0);
}

TEST(max_area_queue, c1) {
    auto input = std::vector<std::vector<int>>{};
    EXPECT_EQ(max_area_queue(input), 0);
}

TEST(max_area_queue, c2) {
    auto input = std::vector<std::vector<int>>{{}};
    EXPECT_EQ(max_area_queue(input), 0);
}

TEST(max_area_stack, a) {
    auto input = std::vector<std::vector<int>>{
         {0,0,1,0,0,0,0,1,0,0,0,0,0},
         {0,0,0,0,0,0,0,1,1,1,0,0,0},
         {0,1,1,0,1,0,0,0,0,0,0,0,0},
         {0,1,0,0,1,1,0,0,1,0,1,0,0},
         {0,1,0,0,1,1,0,0,1,1,1,0,0},
         {0,0,0,0,0,0,0,0,0,0,1,0,0},
         {0,0,0,0,0,0,0,1,1,1,0,0,0},
         {0,0,0,0,0,0,0,1,1,0,0,0,0}};
    EXPECT_EQ(max_area_stack(input), 6);
}

TEST(max_area_stack, b) {
    auto input = std::vector<std::vector<int>> {{0,0,0,0,0,0,0,0}};
    EXPECT_EQ(max_area_stack(input), 0);
}

TEST(max_area_stack, c1) {
    auto input = std::vector<std::vector<int>>{};
    EXPECT_EQ(max_area_stack(input), 0);
}

TEST(max_area_stack, c2) {
    auto input = std::vector<std::vector<int>>{{}};
    EXPECT_EQ(max_area_stack(input), 0);
}

TEST(max_area_dfs, a) {
    auto input = std::vector<std::vector<int>>{
         {0,0,1,0,0,0,0,1,0,0,0,0,0},
         {0,0,0,0,0,0,0,1,1,1,0,0,0},
         {0,1,1,0,1,0,0,0,0,0,0,0,0},
         {0,1,0,0,1,1,0,0,1,0,1,0,0},
         {0,1,0,0,1,1,0,0,1,1,1,0,0},
         {0,0,0,0,0,0,0,0,0,0,1,0,0},
         {0,0,0,0,0,0,0,1,1,1,0,0,0},
         {0,0,0,0,0,0,0,1,1,0,0,0,0}};
    EXPECT_EQ(max_area_dfs(input), 6);
}

TEST(max_area_dfs, b) {
    auto input = std::vector<std::vector<int>> {{0,0,0,0,0,0,0,0}};
    EXPECT_EQ(max_area_dfs(input), 0);
}

TEST(max_area_dfs, c1) {
    auto input = std::vector<std::vector<int>>{};
    EXPECT_EQ(max_area_dfs(input), 0);
}

TEST(max_area_dfs, c2) {
    auto input = std::vector<std::vector<int>>{{}};
    EXPECT_EQ(max_area_dfs(input), 0);
}

TEST(max_area_dfs1, a) {
    auto input = std::vector<std::vector<int>>{
         {0,0,1,0,0,0,0,1,0,0,0,0,0},
         {0,0,0,0,0,0,0,1,1,1,0,0,0},
         {0,1,1,0,1,0,0,0,0,0,0,0,0},
         {0,1,0,0,1,1,0,0,1,0,1,0,0},
         {0,1,0,0,1,1,0,0,1,1,1,0,0},
         {0,0,0,0,0,0,0,0,0,0,1,0,0},
         {0,0,0,0,0,0,0,1,1,1,0,0,0},
         {0,0,0,0,0,0,0,1,1,0,0,0,0}};
    EXPECT_EQ(max_area_dfs1(input), 6);
}

TEST(max_area_dfs1, b) {
    auto input = std::vector<std::vector<int>> {{0,0,0,0,0,0,0,0}};
    EXPECT_EQ(max_area_dfs1(input), 0);
}

TEST(max_area_dfs1, c1) {
    auto input = std::vector<std::vector<int>>{};
    EXPECT_EQ(max_area_dfs1(input), 0);
}

TEST(max_area_dfs1, c2) {
    auto input = std::vector<std::vector<int>>{{}};
    EXPECT_EQ(max_area_dfs1(input), 0);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}