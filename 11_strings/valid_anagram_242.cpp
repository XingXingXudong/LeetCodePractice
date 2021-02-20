// https://leetcode.com/problems/valid-anagram/

#include <string>
#include <gtest/gtest.h>

bool valid(const std::string& s, const std::string& t) {
    auto count = std::vector<int>(26, 0);
    for (auto c: s) {
        ++count[c - 'a'];
    }
    for (auto c: t) {
        --count[c - 'a'];
    }
    for (auto x: count) {
        if (x != 0) {
            return false;
        }
    }
    return true;
}

TEST(valid, a) {
    std::string s = "anagram";
    std::string t = "nagaram";
    EXPECT_TRUE(valid(s, t));
}

TEST(valid, b) {
    std::string s = "rat";
    std::string t = "cat";
    EXPECT_FALSE(valid(s, t));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}