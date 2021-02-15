// https://leetcode.com/problems/max-chunks-to-make-sorted/

#include <gtest/gtest.h>
#include <vector>

int maxTrucksToSorted(const std::vector<int>& arr) {
    int curMax = arr[0];
    int splits = 0;
    for (int i = 0; i < (int) arr.size(); ++i) {
        if (arr[i] > curMax) {
            curMax = arr[i];
        }
        if (curMax == i) {
            ++splits;
        }
    }
    return splits;
}

TEST(maxTrucksToSorted, a) {
    auto arr = std::vector<int>{4,3,2,1,0};
    int output = 1;
    EXPECT_EQ(maxTrucksToSorted(arr), output);
}

TEST(maxTrucksToSorted, b) {
    auto arr = std::vector<int>{1,0,2,3,4};
    int output = 4;
    EXPECT_EQ(maxTrucksToSorted(arr), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}