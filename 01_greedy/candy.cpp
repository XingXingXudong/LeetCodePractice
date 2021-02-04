#include <vector>
#include <iostream>
// #include <functional>
#include <numeric>
#include <gtest/gtest.h>

using namespace std;

int min_candy(const vector<int>& inputs) {

    if (inputs.size() < 2) {
        return inputs.size();
    }

    auto candys = vector<int>(inputs.size(), 1);

    for (size_t idx = 1; idx < inputs.size(); ++idx) {
        if (inputs[idx] > inputs[idx - 1]) {
            candys[idx] = candys[idx - 1] + 1;
        }
    }

    for (size_t idx = inputs.size() - 1; idx != 0; --idx) {
        if (inputs[idx - 1] > inputs[idx] && candys[idx - 1] <= candys[idx]) {
            candys[idx - 1] = candys[idx] + 1;
        }
    }

    return accumulate(candys.begin(), candys.end(), 0);
}

TEST(candy, test1) {
    auto inputs = vector<int>{1, 0, 1};
    EXPECT_EQ(min_candy(inputs), 5);
}

TEST(candy, test2) {
    auto inputs = vector<int>{1, 2, 3, 4};
    EXPECT_EQ(min_candy(inputs), 10);
}

TEST(candy, test3) {
    auto inputs = vector<int>{4};
    EXPECT_EQ(min_candy(inputs), 1);
}

TEST(candy, test4) {
    auto inputs = vector<int>{4, 3, 2, 1, 1, 2, 3, 4};
    EXPECT_EQ(min_candy(inputs), 20);
}

TEST(candy, test5) {
    auto inputs = vector<int>{};
    EXPECT_EQ(min_candy(inputs), 0);
}

TEST(candy, test6) {
    auto inputs = vector<int>{1, 2};
    EXPECT_EQ(min_candy(inputs), 3);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}