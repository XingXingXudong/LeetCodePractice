// https://leetcode.com/problems/word-break/

#include <iostream>
#include <string>
#include <vector>
#include <gtest/gtest.h>
#include <queue>
#include <set>

bool word_seg(const std::string& word, const std::vector<std::string>& word_dict) {
    auto dict = std::set<std::string>(word_dict.begin(), word_dict.end());
    if (word.length() == 0 || dict.empty()) {
        return false;
    }
    auto dp = std::queue<size_t>{};
    dp.push(0);
    while (!dp.empty()) {
        size_t start = dp.front();
        dp.pop();
        for (size_t i = 1; i <= word.length() - start; ++i) {
            if (dict.count(word.substr(start, i))) {
                if (start + i >= word.length()) {
                    return true;
                }
                dp.push(start + i);
            }
        }
    }
    return false;
}

bool word_seg_dp(const std::string& word, const std::vector<std::string>& word_dict) {
    size_t n = word.length();
    auto dp = std::vector<bool>(n+1, false);
    dp[0] = true; 
    for (size_t i = 1; i <= n; ++i) {
        for (const auto & w: word_dict) {
            size_t len = w.length();
            if (i >= len && word.substr(i-len, len) == w) {
                dp[i] = dp[i] || dp[i - len];
            }
        }
    }
    return dp[n];
}

// time limit exceeded
// TEST(word_seg, b1) {
//     auto word = std::string{"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"};
//     auto word_dict = std::vector<std::string>{"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
//     EXPECT_TRUE(word_seg(word, word_dict));
// }

TEST(word_seg, a1) {
    auto word_dict = std::vector<std::string>{"l", "ll"};
    auto word = std::string{"ll"};
    EXPECT_TRUE(word_seg(word, word_dict));
}

TEST(word_seg, a2) {
    auto word_dict = std::vector<std::string>{"l", "b"};
    auto word = std::string{"llb"};
    EXPECT_TRUE(word_seg(word, word_dict));
}

TEST(word_seg, a3) {
    auto word_dict = std::vector<std::string>{"l", "b"};
    auto word = std::string{"l"};
    EXPECT_TRUE(word_seg(word, word_dict));
}

TEST(word_seg, a4) {
    auto word_dict = std::vector<std::string>{"l", "b"};
    auto word = std::string{"a"};
    EXPECT_FALSE(word_seg(word, word_dict));
}

TEST(word_seg, a) {
    auto word_dict = std::vector<std::string>{"leet", "code"};
    auto word = std::string{"leetcode"};
    EXPECT_TRUE(word_seg(word, word_dict));
}

TEST(word_seg, b) {
    auto word_dict = std::vector<std::string>{"apple", "pen"};
    auto word = std::string("applepenapple");
    EXPECT_TRUE(word_seg(word, word_dict));
}

TEST(word_seg, c) {
    auto word_dict = std::vector<std::string>{"cats", "dog", "sand", "and", "cat"};
    std::string word("catsandog");
    EXPECT_FALSE(word_seg(word, word_dict));
}

TEST(word_seg_dp, b1) {
    auto word = std::string{"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"};
    auto word_dict = std::vector<std::string>{"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
    EXPECT_TRUE(word_seg_dp(word, word_dict));
}

TEST(word_seg_dp, a1) {
    auto word_dict = std::vector<std::string>{"l", "ll"};
    auto word = std::string{"ll"};
    EXPECT_TRUE(word_seg_dp(word, word_dict));
}

TEST(word_seg_dp, a2) {
    auto word_dict = std::vector<std::string>{"l", "b"};
    auto word = std::string{"llb"};
    EXPECT_TRUE(word_seg_dp(word, word_dict));
}

TEST(word_seg_dp, a3) {
    auto word_dict = std::vector<std::string>{"l", "b"};
    auto word = std::string{"l"};
    EXPECT_TRUE(word_seg_dp(word, word_dict));
}

TEST(word_seg_dp, a4) {
    auto word_dict = std::vector<std::string>{"l", "b"};
    auto word = std::string{"a"};
    EXPECT_FALSE(word_seg_dp(word, word_dict));
}

TEST(word_seg_dp, a) {
    auto word_dict = std::vector<std::string>{"leet", "code"};
    auto word = std::string{"leetcode"};
    EXPECT_TRUE(word_seg_dp(word, word_dict));
}

TEST(word_seg_dp, b) {
    auto word_dict = std::vector<std::string>{"apple", "pen"};
    auto word = std::string("applepenapple");
    EXPECT_TRUE(word_seg_dp(word, word_dict));
}

TEST(word_seg_dp, c) {
    auto word_dict = std::vector<std::string>{"cats", "dog", "sand", "and", "cat"};
    std::string word("catsandog");
    EXPECT_FALSE(word_seg_dp(word, word_dict));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}