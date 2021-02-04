// https://leetcode.com/problems/top-k-frequent-elements/
// 桶排序、优先队列

#include <gtest/gtest.h>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iostream>
#include <utility>
#include <algorithm>

void print_num(const std::vector<int>& nums) {
    for (auto x: nums) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

bool is_equal(const std::vector<int>& arr_a, const std::vector<int>& arr_b) {
    if (arr_a.size() != arr_b.size()) {
        return false;
    }
    auto set_a = std::unordered_set<int>(arr_a.begin(), arr_a.end());
    auto set_b = std::unordered_set<int>(arr_b.begin(), arr_b.end());
    if (set_a.size() != set_b.size()) {
        return false;
    }
    for (auto iter = set_a.begin(); iter != set_a.end(); ++iter) {
        if (set_b.find(*iter) == set_b.end()) {
            return false;
        }
    }
    return true;
}

std::vector<int> topk_frequent_elements(const std::vector<int>& nums, size_t topk) {
    auto counts = std::unordered_map<size_t, int>{};
    int max_count = 0;
    for (auto x: nums) {
        if (counts.find(x) != counts.end()) {
            ++counts[x];
        } else {
            counts.insert({x, 1});
        }
        max_count = std::max(max_count, counts[x]);
    }

    std::vector<std::vector<int>> buckets(max_count + 1);
    for (const auto& p: counts) {
        buckets[p.second].push_back(p.first);
    }

    auto ans = std::vector<int>{};
    for(auto p = buckets.end()-1; p >= buckets.begin() && ans.size() < topk; --p) {
        for (auto x: *p) {
            ans.push_back(x);
            if (ans.size() == topk) {
                break;
            }
        }
    }
    return ans;
}

std::vector<int> topk_frequent_elements_by_queue(const std::vector<int>& nums, int topk) {
    auto counts = std::unordered_map<int, int>{};
    for (auto x: nums) {
        if (counts.find(x) != counts.end()) {
            ++counts[x];
        } else {
            counts.insert({x, 1});
        }
    }

    using pair_t = std::pair<int, int>;
    using container_t = std::vector<pair_t>;
    auto comp = [](const pair_t& pa, const pair_t& pb) {
        return pa.second < pb.second;
    };
    auto topk_queue = std::priority_queue<pair_t, container_t, decltype(comp)>(comp);

    for (auto [k, v]: counts){
        topk_queue.push({k, v});
    }

    auto rtn = std::vector<int>{};
    while(topk--) {
        rtn.push_back(topk_queue.top().first);
        topk_queue.pop();
    }
    return rtn;
}


TEST(topk_frequent_elements, a) {
    auto input = std::vector<int>{1,1,1,2,2,3};
    auto topk = 2;
    auto rtn = topk_frequent_elements(input, topk);
    EXPECT_TRUE(is_equal(rtn, std::vector<int>{1, 2}));
}

TEST(topk_frequent_elements, b) {
    auto input = std::vector<int>{1};
    auto topk = 1;
    auto rtn = topk_frequent_elements(input, topk);
    EXPECT_TRUE(is_equal(rtn, std::vector<int>{1}));
}

TEST(topk_frequent_elements, c) {
    auto input = std::vector<int>{1, 2};
    auto topk = 2;
    auto rtn = topk_frequent_elements(input, topk);
    EXPECT_TRUE(is_equal(rtn, std::vector<int>{1, 2}));
}

TEST(topk_frequent_elements_by_queue, a) {
    auto input = std::vector<int>{1,1,1,2,2,3};
    auto topk = 2;
    auto rtn = topk_frequent_elements_by_queue(input, topk);
    print_num(rtn);
    EXPECT_TRUE(is_equal(rtn, std::vector<int>{1, 2}));
}

TEST(topk_frequent_elements_by_queue, b) {
    auto input = std::vector<int>{1};
    auto topk = 1;
    auto rtn = topk_frequent_elements_by_queue(input, topk);
    EXPECT_TRUE(is_equal(rtn, std::vector<int>{1}));
}

TEST(topk_frequent_elements_by_queue, c) {
    auto input = std::vector<int>{1, 2};
    auto topk = 2;
    auto rtn = topk_frequent_elements_by_queue(input, topk);
    EXPECT_TRUE(is_equal(rtn, std::vector<int>{1, 2}));
}
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
