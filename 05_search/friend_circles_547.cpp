// https://leetcode.com/problems/number-of-provinces/

#include <gtest/gtest.h>
#include <vector>
#include <stack>

using matrix_t = std::vector<std::vector<int>>;

int findCircleNum(std::vector<std::vector<int>>& isConnected) {
    if (isConnected.empty() || isConnected[0].empty()) {
        return 0;
    }
    auto connected = std::stack<int>{};
    int count = 0;
    for (int i = 0; i < (int)isConnected.size(); ++i) {
        if (isConnected[i][i] == 1) {
            isConnected[i][i] = 0;
            connected.push(i);
            while (!connected.empty()) {
                int cur = connected.top();
                connected.pop();
                for (int j = 0; j < (int)isConnected[cur].size(); ++j) {
                    if (isConnected[cur][j] == 1 && isConnected[j][j] == 1) {
                        isConnected[j][j] = 0;
                        connected.push(j);
                    }
                }
            }
            ++count;
        }
    }
    return count;
}

void findCircleNumDfs_(std::vector<std::vector<int>>& isConnected, int i) {
    if (isConnected[i][i] == 0) {
        return;
    }
    isConnected[i][i] = 0;
    for (int j = 0; j < (int)isConnected[i].size(); ++j) {
        if (isConnected[i][j] == 1) {
            findCircleNumDfs_(isConnected, j);
        }
    }
}

int findCircleNumDfs(std::vector<std::vector<int>>& isConnected) {
    if (isConnected.empty() || isConnected[0].empty()) {
        return 0;
    }
    auto connected = std::stack<int>{};
    int count = 0;
    for (int i = 0; i < (int)isConnected.size(); ++i) {
        if (isConnected[i][i] == 1) {
            findCircleNumDfs_(isConnected, i);
            ++count;
        }
    }
    return count;
}

void findCircleNumsDfsVisited_(const std::vector<std::vector<int>>& isConnected, size_t i, std::vector<bool>& visited) {
    visited[i] = true; // 标记已经访问了该节点；
    for (size_t j = 0; j < isConnected[i].size(); ++j) {
        if (isConnected[i][j] == 1 && !visited[j]) {
            findCircleNumsDfsVisited_(isConnected, j, visited);
        }
    }
}

size_t findCircleNumDfsVisited(const std::vector<std::vector<int>>& isConnected) {
    size_t count = 0;
    auto visited = std::vector<bool>(isConnected.size(), false);
    for (size_t i = 0; i < isConnected.size(); ++i) {
        if (!visited[i]) {
            ++count;
            findCircleNumsDfsVisited_(isConnected, i, visited);
        }
    }
    return count;
}

TEST(isConnected, a) {
    auto input = matrix_t{{1,1,0},{1,1,0},{0,0,1}};
    auto output = 2;
    EXPECT_EQ(findCircleNum(input), output);
}

TEST(isConnected, b) {
    auto input = matrix_t{{1,0,0},{0,1,0},{0,0,1}};
    auto output = 3;
    EXPECT_EQ(findCircleNum(input), output);
}

TEST(isConnected, c) {
    auto input = matrix_t{{1,0,0,1},{0,1,1,0},{0,1,1,1},{1,0,1,1}};
    auto output = 1;
    EXPECT_EQ(findCircleNum(input), output);
}

TEST(isConnectedDfs, a) {
    auto input = matrix_t{{1,1,0},{1,1,0},{0,0,1}};
    auto output = 2;
    EXPECT_EQ(findCircleNumDfs(input), output);
}

TEST(isConnectedDfs, b) {
    auto input = matrix_t{{1,0,0},{0,1,0},{0,0,1}};
    auto output = 3;
    EXPECT_EQ(findCircleNumDfs(input), output);
}

TEST(isConnectedDfs, c) {
    auto input = matrix_t{{1,0,0,1},{0,1,1,0},{0,1,1,1},{1,0,1,1}};
    auto output = 1;
    EXPECT_EQ(findCircleNumDfs(input), output);
}

TEST(isConnectedDfsv, a) {
    auto input = matrix_t{{1,1,0},{1,1,0},{0,0,1}};
    auto output = 2;
    EXPECT_EQ(findCircleNumDfsVisited(input), output);
}

TEST(isConnectedDfsv, b) {
    auto input = matrix_t{{1,0,0},{0,1,0},{0,0,1}};
    auto output = 3;
    EXPECT_EQ(findCircleNumDfsVisited(input), output);
}

TEST(isConnectedDfsv, c) {
    auto input = matrix_t{{1,0,0,1},{0,1,1,0},{0,1,1,1},{1,0,1,1}};
    auto output = 1;
    EXPECT_EQ(findCircleNumDfsVisited(input), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


