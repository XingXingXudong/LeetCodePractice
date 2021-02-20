// https://leetcode.com/problems/isomorphic-strings/

#include <gtest/gtest.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

bool isomorphic(const std::string& s, const std::string& t) {
    if (s.length() != t.length()) {
        return false;
    }
    auto map = std::unordered_map<char, char>{};
    auto set = std::unordered_set<char>{};
    for (size_t i = 0; i < s.length(); ++i) {
        if (!map.count(s[i]) && !set.count(t[i])) {
            map[s[i]] = t[i];
            set.insert(t[i]);
        } else {
            if (map[s[i]] != t[i]) {
                return false;
            }
        }
    }
    return true;
}

bool isomorphic_idx(const std::string& s, const std::string& t) {
    if (s.length() != t.length()) {
        return false;
    }
    auto s_idx = std::vector<int>(256, 0);
    auto t_idx = std::vector<int>(256, 0);
    for (size_t i = 0; i < s.length(); ++i) {
        if (s_idx[s[i]] != t_idx[t[i]]) {
            return false;
        }
        s_idx[s[i]] = t_idx[t[i]] = i + 1;
    }
    return true;
}

TEST(isomorphic, a) {
    std::string s = "egg", t = "add";
    EXPECT_TRUE(isomorphic(s, t));
}

TEST(isomorphic, b) {
    std::string s = "foo", t = "bar";
    EXPECT_FALSE(isomorphic(s, t));
}

TEST(isomorphic, c) {
    std::string s = "paper", t = "title";
    EXPECT_TRUE(isomorphic(s, t));
}

TEST(isomorphic, d) {
    std::string s = "badc", t = "baba";
    EXPECT_FALSE(isomorphic(s, t));
}

TEST(isomorphic_idx, a) {
    std::string s = "egg", t = "add";
    EXPECT_TRUE(isomorphic_idx(s, t));
}

TEST(isomorphic_idx, b) {
    std::string s = "foo", t = "bar";
    EXPECT_FALSE(isomorphic_idx(s, t));
}

TEST(isomorphic_idx, c) {
    std::string s = "paper", t = "title";
    EXPECT_TRUE(isomorphic_idx(s, t));
}

TEST(isomorphic_idx, d) {
    std::string s = "badc", t = "baba";
    EXPECT_FALSE(isomorphic_idx(s, t));
}
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}