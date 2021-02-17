// https://leetcode.com/problems/the-skyline-problem/

#include <gtest/gtest.h>
#include <vector>



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