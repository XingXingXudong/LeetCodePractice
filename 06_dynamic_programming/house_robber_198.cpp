// https://leetcode.com/problems/house-robber/

#include <vector>
#include <iostream>
#include <gtest/gtest.h>
#include <algorithm>

int rob(const std::vector<int>& house) {
    if (house.size() == 1) {
        return house[0];
    } 
    if (house.size() == 2) {
        return std::max(house[1], house[0]);
    }
    int max_money_1 = house[0];
    int max_money_2 = std::max(house[0], house[1]);
    int current = 0;
    for (size_t i = 2; i < house.size(); ++i) {
        current = std::max(max_money_1 + house[i], max_money_2);
        max_money_1 = max_money_2;
        max_money_2 = current;
    }
    return current;
}

int rob_recursive_(const std::vector<int>& house, size_t i) {
    if (i == 0) {
        return house[0];
    } 
    if (i == 1) {
        return std::max(house[1], house[0]);
    }
    return std::max(rob_recursive_(house, i - 2) + house[i], rob_recursive_(house, i - 1));
}

int rob_recursive(const std::vector<int>& house) {
    return rob_recursive_(house, house.size() - 1);
}

TEST(rob, a) {
    auto input = std::vector<int>{1, 2, 3, 1};
    int output = 4;
    EXPECT_EQ(rob(input), output);
}

TEST(rob, b) {
    auto input = std::vector<int>{2, 7, 9, 3, 1};
    int output = 12;
    EXPECT_EQ(rob(input), output);
}

TEST(rob, c) {
    auto input = std::vector<int>{2, 7, 9, 3, 1, 10, 11, 1, 23, 22, 1, 22};
    int output = 68;
    EXPECT_EQ(rob(input), output);
}

TEST(rob_recursive, a) {
    auto input = std::vector<int>{1, 2, 3, 1};
    int output = 4;
    EXPECT_EQ(rob_recursive(input), output);
}

TEST(rob_recursive, b) {
    auto input = std::vector<int>{2, 7, 9, 3, 1};
    int output = 12;
    EXPECT_EQ(rob_recursive(input), output);
}

TEST(rob_recursive, c) {
    auto input = std::vector<int>{2, 7, 9, 3, 1, 10, 11, 1, 23, 22, 1, 22};
    int output = 68;
    EXPECT_EQ(rob_recursive(input), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}