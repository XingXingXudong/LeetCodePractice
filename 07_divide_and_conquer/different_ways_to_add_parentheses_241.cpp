// https://leetcode.com/problems/different-ways-to-add-parentheses/

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <gtest/gtest.h>

bool is_equal(const std::vector<int>& a, const std::vector<int>& b) {
    auto set_a = std::set<int>(a.begin(), a.end());
    auto set_b = std::set<int>(b.begin(), b.end());
    return set_a == set_b;
}

std::vector<int> diffWays(const std::string& input) {
    std::vector<int> ways;
    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];
        if (c == '*' || c == '+' || c == '-') {
            auto left = diffWays(input.substr(0, i));
            auto right = diffWays(input.substr(i+1, input.length()));
            for (auto l : left) {
                for (auto r: right) {
                    switch(c) {
                        case '+': ways.push_back(l + r); break;
                        case '-': ways.push_back(l - r); break;
                        case '*': ways.push_back(l * r); break;
                    }
                }
            }
        }
    }
    if (ways.empty()) {
        ways.push_back(std::stoi(input));
    }
    return ways;
}

TEST(diffWays, a) {
    const std::string input("2-1-1");
    const std::vector<int> output{0, 2};
    EXPECT_TRUE(is_equal(diffWays(input), output));
}

TEST(diffWays, b) {
    const std::string input("2*3-4*5");
    const std::vector<int> output{-34, -14, -10, -10, 10};
    EXPECT_TRUE(is_equal(diffWays(input), output));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
