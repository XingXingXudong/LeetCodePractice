// https://leetcode.com/problems/combinations/

#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <stack>
#include <set>

void print(const std::vector<std::vector<int>>& arr) {
    for (const auto& x: arr) {
        for (auto y: x) {
            std::cout << y << " ";
        }
        std::cout << std::endl;
    }
}

bool is_equal(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b) {
    auto set_a = std::set<std::vector<int>>{};
    auto set_b = std::set<std::vector<int>>{};
    for (const auto& x: a) {
        set_a.insert(x);
    }
    for (const auto& x: b) {
        set_b.insert(x);
    }
    return set_a == set_b;
}

void backtracing(std::vector<std::vector<int>>& ans, std::vector<int>& comb, int& count, int pos, int n, int k) {
    if (count == k) {
        ans.push_back(comb);
        return;
    }
    for (int i = pos; i <= n; ++i) {
        comb[count++] = i;
        backtracing(ans, comb, count, i + 1, n, k);
        --count;
    }
}

std::vector<std::vector<int>> combine(int n, int k) {
    auto comb = std::vector<int>(k, 0);
    auto ans = std::vector<std::vector<int>>{};
    auto count = 0;
    backtracing(ans, comb, count, 1, n, k);
    return ans;
}

// 如何实现基于
std::vector<std::vector<int>> combine_stack(int n, int k) {
    auto ans = std::vector<std::vector<int>>{};
    auto count = 0;
    auto combs = std::stack<std::vector<int>>{};
    
    for (int i = 1; i <= n; ++i) {
        combs.push({i});
        while(!combs.empty()) {
        }
    }
    return ans;
}


TEST(combine, a) {
    int n = 4, k = 2;
    auto rtn = combine(n, k);
    auto output = std::vector<std::vector<int>>{
        {2,4}, {3,4}, {2,3}, {1,2}, {1,3}, {1,4}
    };
    print(rtn);
    EXPECT_TRUE(is_equal(rtn, output));
}

TEST(combine, b) {
    int n = 1, k = 1;
    auto rtn = combine(n, k);
    auto output = std::vector<std::vector<int>>{{1}};
    print(rtn);
    EXPECT_TRUE(is_equal(rtn, output));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
