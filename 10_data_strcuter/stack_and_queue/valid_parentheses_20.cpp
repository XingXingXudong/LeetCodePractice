// https://leetcode.com/problems/valid-parentheses/

#include <gtest/gtest.h>
#include <stack>
#include <string>
#include <unordered_map>

bool isValid(const std::string& ps) {
    if (ps.length() % 2 != 0) {
        return false;
    }
    auto pms = std::unordered_map<char, char>{{'}', '{'}, {']', '['}, {')', '('}};
    auto cs = std::stack<char>{};
    for (size_t i = 0; i < ps.length(); ++i) {
        if (cs.empty() || cs.top() != pms[ps[i]]) {
            cs.push(ps[i]);
        } else {
            cs.pop();
        }
    }
    return cs.empty();
}

TEST(isValid, a1) {
    auto ipt = "{";
    EXPECT_FALSE(isValid(ipt));
}

TEST(isValid, a) {
    auto ipt = "()";
    EXPECT_TRUE(isValid(ipt));
}

TEST(isValid, b) {
    auto ipt = "(]";
    EXPECT_FALSE(isValid(ipt));
}

TEST(isValid, c) {
    auto ipt = "()[]{}";
    EXPECT_TRUE(isValid(ipt));
}

TEST(isValid, d) {
    auto ipt = "([)]";
    EXPECT_FALSE(isValid(ipt));
}

TEST(isValid, e) {
    auto ipt = "{[]}";
    EXPECT_TRUE(isValid(ipt));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}