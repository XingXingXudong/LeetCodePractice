// https://leetcode.com/problems/daily-temperatures/
#include <gtest/gtest.h>
#include <vector>
#include <stack>

std::vector<int> dailyTemperatures(std::vector<int>& T) {
    auto rtn = std::vector<int>(T.size(), 0);
    auto current_min = std::stack<int>{};
    for (int i = 0; i < (int)T.size(); ++i) {
        while(!current_min.empty() && T[current_min.top()] < T[i]) {
            rtn[current_min.top()] = i - current_min.top();
            current_min.pop();
        }
        current_min.push(i);
    }
    return rtn;
}

TEST(dailyTemperatures, a) {
    auto ipt = std::vector<int>{73, 74, 75, 71, 69, 72, 76, 73};
    auto output = std::vector<int>{1, 1, 4, 2, 1, 1, 0, 0};
    EXPECT_TRUE(output == dailyTemperatures(ipt));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}