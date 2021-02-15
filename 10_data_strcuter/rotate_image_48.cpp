//https://leetcode.com/problems/rotate-image/
#include <gtest/gtest.h>
#include <vector>

void print_matrix(const std::vector<std::vector<int>>& m) {
    std::cout << "------------------------------" << std::endl;
    for (size_t i = 0; i < m.size(); ++i) {
        for (size_t j = 0; j < m[i].size(); ++j) {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "------------------------------" << std::endl;
}

void rotateImage(std::vector<std::vector<int>>& matrix) {
    int temp = 0, n = matrix.size() - 1;
    for (int i = 0; i <= n / 2; ++i) {
        for (int j = i; j < n - i; ++j) {
            temp = matrix[i][j];
            matrix[i][j] = matrix[n-j][i];
            matrix[n-j][i] = matrix[n-i][n-j];
            matrix[n-i][n-j] = matrix[j][n-i];
            matrix[j][n-i] = temp;
        }
    }
    return;
}

TEST(rotateImage, a) {
    auto inputs = std::vector<std::vector<int>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto output = std::vector<std::vector<int>>{{7, 4, 1}, {8, 5, 2}, {9, 6, 3}};
    rotateImage(inputs);
    EXPECT_TRUE(inputs == output);
}

TEST(rotateImage, b) {
    auto inputs = std::vector<std::vector<int>>{{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}};
    auto output = std::vector<std::vector<int>>{{15,13,2,5},{14,3,4,1},{12,6,8,9},{16,7,10,11}};
    rotateImage(inputs);
    EXPECT_TRUE(inputs == output);
}

TEST(rotateImage, c) {
    auto inputs = std::vector<std::vector<int>>{{1}};
    auto output = std::vector<std::vector<int>>{{1}};
    rotateImage(inputs);
    EXPECT_TRUE(inputs == output);
}

TEST(rotateImage, d) {
    auto inputs = std::vector<std::vector<int>>{{1,2},{3,4}};
    auto output = std::vector<std::vector<int>>{{3,1},{4,2}};
    rotateImage(inputs);
    EXPECT_TRUE(inputs == output);
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}