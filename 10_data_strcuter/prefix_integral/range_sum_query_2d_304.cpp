// https://leetcode.com/problems/range-sum-query-2d-immutable/

#include <gtest/gtest.h>
#include <vector>

class NumMatrix {
private:
    std::vector<std::vector<int>> acc;
public:
    NumMatrix(std::vector<std::vector<int>>& matrix) {
        int row = matrix.size();
        int col = matrix.empty() ? 0: matrix[0].size();
        acc = std::vector<std::vector<int>>(row + 1, std::vector<int>(col + 1, 0));
        // 注意这条语句中的错误，在matrix为空的情况下matrix[0]会发生越界错误
        // acc = std::vector<std::vector<int>>(matrix.size() + 1, std::vector<int>(matrix[0].size() + 1, 0));
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[i].size(); ++j) {
                acc[i+1][j+1] = acc[i+1][j] + acc[i][j+1] - acc[i][j] + matrix[i][j];
            }
        }
    }
    int sumRegion(int row1, int col1, int row2, int col2) {
        return acc[row2 + 1][col2 + 1] - acc[row1][col2 + 1] - acc[row2 + 1][col1] + acc[row1][col1];
    }
};

TEST(NumMatrix, b) {
    auto matrix = std::vector<std::vector<int>>{};
    NumMatrix* obj = new NumMatrix(matrix);
}

TEST(NumMatrix, a) {
    auto matrix = std::vector<std::vector<int>>{
        {3, 0, 1, 4, 2},
        {5, 6, 3, 2, 1},
        {1, 2, 0, 1, 5},
        {4, 1, 0, 1, 7},
        {1, 0, 3, 0, 5}
    };
    NumMatrix* obj = new NumMatrix(matrix);
    EXPECT_EQ(obj->sumRegion(2, 1, 4, 3), 8);
    EXPECT_EQ(obj->sumRegion(1, 1, 2, 2), 11);
    EXPECT_EQ(obj->sumRegion(1, 2, 2, 4), 12);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */