// https://leetcode.com/problems/pacific-atlantic-water-flow/

#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <set>

using namespace std;

// using matrix_t = std::vector<std::vector<int>>;
// using matrix_tb = std::vector<std::vector<bool>>;
// const auto direction = std::vector<int>{-1, 0, 1, 0, -1};

using matrix_t = vector<vector<int>>;
using matrix_tb = vector<vector<bool>>;
std::vector<int> direction = {-1, 0, 1, 0, -1};
    
void dfs(const matrix_t& matrix, matrix_tb& can_reach, int r, int c) {
    if (can_reach[r][c]) {
        return;
    }
    can_reach[r][c] = true;
    int x, y;
    int row = matrix.size(), col = matrix[0].size();
    for (size_t k = 0; k < 4; ++k) {
        x = r + direction[k];
        y = c + direction[k+1];
        //从四个边开始搜索，则靠近边的坐标先遍历到，matrix[r][c] <= matrix[x][y]，即可保证四个边外的海水（倒流）到[x][y]
        if (x >= 0 && x < row && y >= 0 && y <= col && matrix[r][c] <= matrix[x][y]) {
            dfs(matrix, can_reach, x, y);
        }
    }
}

matrix_t pacificAtlantic(const matrix_t& matrix) {
    if (matrix.empty() || matrix[0].empty()) {
        return {}; 
    }
    matrix_t ans;
    int row = matrix.size(), col = matrix[0].size();
    matrix_tb can_reach_p(row, std::vector<bool>(col, false));
    matrix_tb can_reach_a(row, std::vector<bool>(col, false));
    // 从四个边开始搜索，海水能够（倒流）到的地方，做标记
    for (int i = 0; i < row; ++i) {
        dfs(matrix, can_reach_p, i, 0);
        dfs(matrix, can_reach_a, i, col - 1);
    }
    for (int i = 0; i < col; ++i) {
        dfs(matrix, can_reach_p, 0, i);
        dfs(matrix, can_reach_a, row - 1, i);
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (can_reach_p[i][j] && can_reach_a[i][j]) {
                ans.push_back(std::vector<int>{i, j});
            }
        }
    }
    return ans;
}

bool is_same_my(const matrix_t& a, const matrix_t& b) {
    auto set_a = std::set<std::vector<int>>{};
    auto set_b = std::set<std::vector<int>>{};
    for (const auto& x: a) {
        set_a.insert(x);
    }
    for (const auto& x: b) {
        set_b.insert(x);
    }
    for (const auto& x: set_a) {
        if (set_b.find(x) == set_b.end()) return false;
    }
    for (const auto& x: set_b) {
        if (set_a.find(x) == set_a.end()) return false;
    }
    return true;
}

// void dfs(const matrix_t& matrix, matrix_tb& can_reach, int r, int c) {
//     if (can_reach[r][c]) {
//         return;
//     }
//     can_reach[r][c] = true;
//     int x, y;
//     int row = matrix.size(), col = matrix[0].size();
//     for (size_t k = 0; k < 4; ++k) {
//         x = r + direction[k];
//         y = c + direction[k+1];
//         //从四个边开始搜索，则靠近边的坐标先遍历到，matrix[r][c] <= matrix[x][y]，即可保证四个边外的海水（倒流）到[x][y]
//         if (x >= 0 && x < row && y >= 0 && y <= col && matrix[r][c] <= matrix[x][y]) {
//             dfs(matrix, can_reach, x, y);
//         }
//     }
// }

// matrix_t pacificAtlantic(const matrix_t& matrix) {
//     if (matrix.empty() || matrix[0].empty()) {
//         return {}; 
//     }
//     matrix_t ans;
//     int row = matrix.size(), col = matrix[0].size();
//     matrix_tb can_reach_p(row, std::vector<bool>(col, false));
//     matrix_tb can_reach_a(row, std::vector<bool>(col, false));
//     // 从四个边开始搜索，海水能够（倒流）到的地方，做标记
//     for (int i = 0; i < row; ++i) {
//         dfs(matrix, can_reach_p, i, 0);
//         dfs(matrix, can_reach_a, i, col - 1);
//     }
//     for (int i = 0; i < col; ++i) {
//         dfs(matrix, can_reach_p, 0, i);
//         dfs(matrix, can_reach_a, row - 1, i);
//     }
//     for (int i = 0; i < row; ++i) {
//         for (int j = 0; j < col; ++j) {
//             if (can_reach_p[i][j] && can_reach_a[i][j]) {
//                 ans.push_back(std::vector<int>{i, j});
//             }
//         }
//     }
//     // for (const auto& row: can_reach_a) {
//     //     for (auto x: row) {
//     //         std::cout << x << " ";
//     //     }
//     //     std::cout << std::endl;
//     // }
//     // std::cout << "====================" << std::endl;
//     // for (const auto& row: can_reach_p) {
//     //     for (auto x: row) {
//     //         std::cout << x << " ";
//     //     }
//     //     std::cout << std::endl;
//     // }
//     return ans;
// }



TEST(pacificAtlantic, b) {
    auto input = matrix_t{{1}};
    auto output = matrix_t{{0, 0}};
    EXPECT_TRUE(is_same_my(pacificAtlantic(input), output));
}


TEST(pacificAtlantic, a) {
    auto input = matrix_t{
//       *, *, *, *, *
/* * */ {1, 2, 2, 3, 5}, //~
/* * */ {3, 2, 3, 4, 4}, //~
/* * */ {2, 4, 5, 3, 1}, //~
/* * */ {6, 7, 1, 4, 5}, //~
/* * */ {5, 1, 1, 2, 4}  //~
//       ~, ~, ~, ~, ~ 
    };
    auto output = matrix_t{{0, 4}, {1, 3}, {1, 4}, {2, 2}, {3, 0}, {3, 1}, {4, 0}};
    EXPECT_TRUE(is_same_my(pacificAtlantic(input), output));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}