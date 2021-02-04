// https://leetcode.com/problems/maximum-product-of-word-lengths/

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

int maxProductBit(const std::vector<std::string>& words) {
    std::unordered_map<int, int> hash{};
    int ans = 0;
    for (const auto& word: words) {
        int mask = 0, size = word.size();
        for (const char& c: word) {
            mask |= 1 << (c - 'a');
        }
        hash[mask] = std::max(hash[mask], size);    // 记录相同子母组成的串的长度，只需保留最大长度即可
        for (const auto & [h_mask, h_len]: hash) {
            if (!(mask & h_mask)) {
                ans = std::max(ans, size * h_len);
            }
        }
    }
    return ans;
}

bool has_same_char(const std::string& a, const std::string& b) {
    auto flag = std::vector<bool>(26, false);
    for (auto x: a) {
        flag[x-'a'] = true;
    }
    for (auto x: b) {
        if (flag[x-'a']) {
            return true;
        }
    }
    return false;
}

int maxProduct(const std::vector<std::string>& words) {
    int max_product = 0;
    if (words.size() < 2) {
        return 0;
    }
    for (size_t i = 0; i < words.size() - 1; ++i) {
        for (size_t j = i+1; j < words.size(); ++j) {
            if (!has_same_char(words[i], words[j])) {
                max_product = std::max(max_product, (int)(words[i].length() * words[j].length()));
            }
        }
    }
    return max_product;
}

TEST(maxProductBit, a) {
    auto words = std::vector<std::string>{"abcw","baz","foo","bar","xtfn","abcdef"};
    int output = 16;
    EXPECT_EQ(maxProductBit(words), output);
}

TEST(maxProductBit, b) {
    auto words = std::vector<std::string>{"a","ab","abc","d","cd","bcd","abcd"};
    int output = 4;
    EXPECT_EQ(maxProductBit(words), output);
}

TEST(maxProductBit, c) {
    auto words = std::vector<std::string>{"a","aa","aaa","aaaa"};
    int output = 0;
    EXPECT_EQ(maxProductBit(words), output);
}

TEST(maxProductBit, d) {
    auto words = std::vector<std::string>{};
    int output = 0;
    EXPECT_EQ(maxProductBit(words), output);
}

TEST(maxProduct, a) {
    auto words = std::vector<std::string>{"abcw","baz","foo","bar","xtfn","abcdef"};
    int output = 16;
    EXPECT_EQ(maxProduct(words), output);
}

TEST(maxProduct, b) {
    auto words = std::vector<std::string>{"a","ab","abc","d","cd","bcd","abcd"};
    int output = 4;
    EXPECT_EQ(maxProduct(words), output);
}

TEST(maxProduct, c) {
    auto words = std::vector<std::string>{"a","aa","aaa","aaaa"};
    int output = 0;
    EXPECT_EQ(maxProduct(words), output);
}

TEST(maxProduct, d) {
    auto words = std::vector<std::string>{};
    int output = 0;
    EXPECT_EQ(maxProduct(words), output);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}