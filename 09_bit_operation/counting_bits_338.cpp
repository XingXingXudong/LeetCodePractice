// https://leetcode.com/problems/counting-bits/

#include <gtest/gtest.h>
#include <vector>

bool is_equal(const std::vector<int>& a, const std::vector<int>& b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

std::vector<int> countBits(int num) {
    if (num < 0) {
        return {};
    }
    std::vector<int> rtn(num+1, 0);
    for (int i = 1; i <= num; ++i) {
        rtn[i] = i & 1 ? rtn[i-1] + 1 : rtn[i >> 1];
    }
    return rtn;
}

TEST(countBits, a) {
    int input = 2;
    auto output = std::vector<int>{0,1,1};
    EXPECT_TRUE(is_equal(countBits(input), output));
}

TEST(countBits, b) {
    int input = 0;
    auto output = std::vector<int>{0};
    EXPECT_TRUE(is_equal(countBits(input), output));
}

TEST(countBits, c) {
    int input = 5;
    auto output = std::vector<int>{0, 1, 1, 2, 1, 2};
    EXPECT_TRUE(is_equal(countBits(input), output));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}