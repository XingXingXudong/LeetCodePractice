// https://leetcode.com/problems/sort-characters-by-frequency/

#include <iostream>
#include <vector>
#include <string>
#include <gtest/gtest.h>
#include <unordered_map>
#include <algorithm>
#include <queue>

bool is_valid(const std::string& str){
    if (str.size() < 2) {
        return true;
    }
    auto max_count = str.length();
    size_t count = 1;
    for (size_t i = 1; i < str.length(); ++i) {
        if (str[i] == str[i - 1]) {
            ++count;
            if (count > max_count) {
                return false;
            }
        } else {
            max_count = count;
            count = 1;
        }
    }
    return true;
}

// 桶排序
std::string sort_by_frequency(const std::string& str) {
    auto counts = std::unordered_map<char, int>();
    int buckets_size = 0;
    for (const auto& c: str) {
        if (counts.find(c) != counts.end()) {
            ++counts[c];
        } else {
            counts.insert(std::pair(c, 1));
        }
        buckets_size = std::max(buckets_size, counts[c]);
    }
    auto buckets = std::vector<std::vector<char>>(buckets_size + 1);
    // for (const auto& [k, v]: counts) {
    //     buckets[v].push_back(k);
    // }
    for (const auto& x: counts) {
        buckets[x.second].push_back(x.first);
    }

    std::string rtn{};
    size_t j = 0;
    for (size_t i = buckets.size() - 1; i != 0; --i) {
        for (const auto& c: buckets[i]) {
            j = i;
            while(j--) {
                rtn += c;
            }
        }
    }
    return rtn;
}

std::string sort_by_frequency_by_queue(const std::string& str) {
    auto counts = std::unordered_map<char, int>();
    for (const auto& c: str) {
        if (counts.find(c) != counts.end()) {
            ++counts[c];
        } else {
            counts.insert(std::pair(c, 1));
        }
    }
    using pair_t = std::pair<char, int>;
    using container_t = std::vector<pair_t>;
    auto comp_fun = [](const pair_t& p1, const pair_t& p2) {return p1.second < p2.second;};
    auto sort_queue = std::priority_queue<pair_t, container_t, decltype(comp_fun)>(comp_fun);

    for (const auto& x: counts) {
        sort_queue.push(x);
    }

    std::string rtn{};
    while(!sort_queue.empty()) {
        auto [k, v] = sort_queue.top();
        while(v--) {
            rtn += k;
        }
        sort_queue.pop();
    }
    return rtn;
}

TEST(is_valid, a) {
    auto str1 = "eert";
    EXPECT_TRUE(is_valid(str1));
    auto str2 = "cccaaa";
    EXPECT_TRUE(is_valid(str2));
    auto str3 = "bbAa";
    EXPECT_TRUE(is_valid(str3));
    auto str4 = "a";
    EXPECT_TRUE(is_valid(str4));
}

TEST(sort_by_frequency, a) {
    auto input = "tree";
    auto output = sort_by_frequency(input);
    EXPECT_TRUE(is_valid(output));
}

TEST(sort_by_frequency, b) {
    auto input = "cccaaa";
    auto output = sort_by_frequency(input);
    EXPECT_TRUE(is_valid(output));
}

TEST(sort_by_frequency, c) {
    auto input = "bbAa";
    auto output = sort_by_frequency(input);
    EXPECT_TRUE(is_valid(output));
}

TEST(sort_by_frequency, d) {
    auto input = "aa";
    auto output = sort_by_frequency(input);
    EXPECT_TRUE(is_valid(output));
}

TEST(sort_by_frequency, e) {
    auto input = "a";
    auto output = sort_by_frequency(input);
    EXPECT_TRUE(is_valid(output));
}

TEST(sort_by_frequency_by_queue, a) {
    auto input = "tree";
    auto output = sort_by_frequency_by_queue(input);
    EXPECT_TRUE(is_valid(output));
}

TEST(sort_by_frequency_by_queue, b) {
    auto input = "cccaaa";
    auto output = sort_by_frequency_by_queue(input);
    EXPECT_TRUE(is_valid(output));
}

TEST(sort_by_frequency_by_queue, c) {
    auto input = "bbAa";
    auto output = sort_by_frequency_by_queue(input);
    EXPECT_TRUE(is_valid(output));
}

TEST(sort_by_frequency_by_queue, d) {
    auto input = "aa";
    auto output = sort_by_frequency_by_queue(input);
    EXPECT_TRUE(is_valid(output));
}

TEST(sort_by_frequency_by_queue, e) {
    auto input = "a";
    auto output = sort_by_frequency_by_queue(input);
    EXPECT_TRUE(is_valid(output));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
