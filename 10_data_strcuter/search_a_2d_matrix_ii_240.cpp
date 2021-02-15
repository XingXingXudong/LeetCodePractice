// https://leetcode.com/problems/search-a-2d-matrix-ii/
#include <gtest/gtest.h>
#include <vector>

bool searchMatrix(const std::vector<std::vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) {
        return false;
    }
    int nRow = matrix.size() - 1, nCol = matrix[0].size() - 1;
    int rowIdx = 0, colIdx = nCol;
    while (0 <= rowIdx && rowIdx <= nRow && 0 <= colIdx && colIdx <= nCol) {
        if (matrix[rowIdx][colIdx] == target) {
            return true;
        } else if (matrix[rowIdx][colIdx] < target) {
            ++rowIdx;
        } else {
            --colIdx;
        }
    }
    return false;
}

TEST(searchMatrix, a) {
    auto matrix = std::vector<std::vector<int>>{{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}};
    int target = 5;
    EXPECT_TRUE(searchMatrix(matrix, target));
}

TEST(searchMatrix, b) {
    auto matrix = std::vector<std::vector<int>>{{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}};
    int target = 20;
    EXPECT_FALSE(searchMatrix(matrix, target));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}