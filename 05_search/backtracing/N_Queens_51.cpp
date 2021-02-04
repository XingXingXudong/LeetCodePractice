// https://leetcode.com/problems/n-queens/

#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

void print(const std::vector<std::vector<int>> nums) {
    for (const auto & row: nums) {
        for (auto x: row) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
}

bool is_equal(const std::vector<std::vector<std::string>>& a, const std::vector<std::vector<std::string>>& b)  {
    auto set_a = std::set<std::vector<std::string>>{};
    auto set_b = std::set<std::vector<std::string>>{};
    for (const auto& x: a) {
        set_a.insert(x);
    }
    for (const auto& x: b) {
        set_b.insert(x);
    }
    return set_a == set_b;
}

bool is_valide(const std::vector<int>& nums) {
    for (int i = 0; i < nums.size() - 1; ++i) {
        for (int j = i + 1; j < nums.size(); ++j) {
            if (i - j == nums[i] - nums[j] || i - j == nums[j] - nums[i]) {
                return false;
            }
        }
    }
    return true;
}

void solve_recursive(std::vector<std::vector<int>>& col_idxs, std::vector<int>& col_idx, int pos) {
    if (pos == (int)(col_idx.size() - 1)) {
        if (is_valide(col_idx)) {
            col_idxs.push_back(col_idx);
            for (auto x: col_idx) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
            return;
        }
    }

    for (int i = pos; i < col_idx.size(); ++i) {
        std::swap(col_idx[i], col_idx[pos]);
        solve_recursive(col_idxs, col_idx, pos+1);
        std::swap(col_idx[i], col_idx[pos]);
    }
}

std::vector<std::string> idx_to_solve(const std::vector<int>& nums) {
    auto rtn = std::vector<std::string>{};
    for (int i = 0; i < nums.size(); ++i) {
        auto ans = std::string(nums.size(), '.');
        ans[nums[i]] = 'Q';
        rtn.push_back(ans);
    }
    return rtn;
}

std::vector<std::vector<std::string>> solve(int n) {
    auto col_idxs = std::vector<std::vector<int>>{};
    auto col_idx = std::vector<int>{};
    for (int i = 0; i < n; ++i) {
        col_idx.push_back(i);
    }
    solve_recursive(col_idxs, col_idx, 0);
    auto rtn = std::vector<std::vector<std::string>>{};
    for (const auto& x: col_idxs) {
        rtn.push_back(idx_to_solve(x));
    }
    return rtn;
}

std::vector<std::vector<std::string>> solve1(int n) {
    auto col_idxs = std::vector<std::vector<int>>{};
    auto col_idx = std::vector<int>{};
    for (int i = 0; i < n; ++i) {
        col_idx.push_back(i);
    }
    do {
        if (is_valide(col_idx)) {
            col_idxs.push_back(col_idx);
        }
    } while (std::next_permutation(col_idx.begin(), col_idx.end()));
    solve_recursive(col_idxs, col_idx, 0);
    auto rtn = std::vector<std::vector<std::string>>{};
    for (const auto& x: col_idxs) {
        auto ans = std::vector<std::string>{};
        for (int i = 0; i < n; ++i) {
            auto line = std::string(n, '.');
            line[x[i]] = 'Q';
            ans.push_back(line);
        }
        rtn.push_back(ans);
    }
    return rtn;
}

void set_valid(std::vector<std::vector<int>>& valid, int i, int j, int val) {
    int n = valid.size();
    if (i < 0 || j < 0 || i >= n || j >= n) {
        return;
    }
    for (int k = 0; k < n; ++k) {
        valid[i][k] += val;
        valid[k][j] += val;
    }
    valid[i][j] -= val; // [i][j]被加了两次

    int k = i, l = j;
    while(++k < n && ++l < n) {
        valid[k][l] += val;
    }
    k = i, l = j;
    while(--k >= 0 && --l >= 0) {
        valid[k][l] += val;
    }
    k = i, l = j;
    while(--k >= 0 && ++l < n)  {
        valid[k][l] += val;
    }
    k = i, l = j;
    while(++k < n && --l >= 0)  {
        valid[k][l] += val;
    }
}

void solve_backtransing_(std::vector<std::string>& ans, std::vector<std::vector<int>>& valid, int start, std::vector<std::vector<std::string>>& anss) {
    if (start == (int)ans.size()) {
        anss.push_back(ans);
        return;
    } 
    for (int i = 0; i < ans.size(); ++i) {
        if (valid[start][i] == 0) {
            ans[start][i] = 'Q';
            set_valid(valid, start, i, 1);
            solve_backtransing_(ans, valid, start + 1, anss);
            ans[start][i] = '.';
            set_valid(valid, start, i, -1);
        }
    }
}

std::vector<std::vector<std::string>> solve_backtransing(int n) {
    auto anss = std::vector<std::vector<std::string>>{};
    auto ans = std::vector<std::string>(n, std::string(n, '.'));
    auto valid = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
    std::cout << "ans.size(): (" << ans.size() << ", " << ans[0].size() << ")" << std::endl;
    std::cout << "valid.size(): (" << valid.size() << ", " << valid[0].size() << ")" << std::endl;
    for (int i = 0; i < n; ++i) {
        ans[0][i] = 'Q';
        set_valid(valid, 0, i, 1);
        solve_backtransing_(ans, valid, 1, anss);
        ans[0][i] = '.';
        set_valid(valid, 0, i, -1);
    }
    return anss;
}

TEST(set_valid, a) {
    int n = 5;
    auto valid = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
    print(valid);
    set_valid(valid, 0, 0, 1);
    print(valid);
    set_valid(valid, 1, 2, 1);
    print(valid);
    set_valid(valid, 0, 0, -1);
    print(valid);
    set_valid(valid, 1, 2, -1);
    print(valid);
}

TEST(is_equal, a) {
    auto output1 = std::vector<std::vector<std::string>>{{".Q..", "...Q", "Q...", "..Q."},{"..Q.", "Q...", "...Q", ".Q.."}};
    auto output2 = std::vector<std::vector<std::string>>{{"..Q.", "Q...", "...Q", ".Q.."},{".Q..", "...Q", "Q...", "..Q."}};
    auto output3 = std::vector<std::vector<std::string>>{{".Q..", "...Q", "Q...", "...."},{"..Q.", "Q...", "...Q", ".Q.."}};
    EXPECT_TRUE(is_equal(output1, output2));
    EXPECT_FALSE(is_equal(output1, output3));
}

TEST(sovle, a) {
    int input = 4;
    auto output = std::vector<std::vector<std::string>>{{".Q..", "...Q", "Q...", "..Q."},{"..Q.", "Q...", "...Q", ".Q.."}};
    auto rtn = solve(input);
    EXPECT_TRUE(is_equal(output, rtn));
}

TEST(sovle, b) {
    int input = 1;
    auto output = std::vector<std::vector<std::string>>{{"Q"}};
    auto rtn = solve(input);
    EXPECT_TRUE(is_equal(output, rtn));
}

TEST(sovle1, a) {
    int input = 4;
    auto output = std::vector<std::vector<std::string>>{{".Q..", "...Q", "Q...", "..Q."},{"..Q.", "Q...", "...Q", ".Q.."}};
    auto rtn = solve1(input);
    EXPECT_TRUE(is_equal(output, rtn));
}

TEST(sovle1, b) {
    int input = 1;
    auto output = std::vector<std::vector<std::string>>{{"Q"}};
    auto rtn = solve1(input);
    EXPECT_TRUE(is_equal(output, rtn));
}

TEST(solve_backtransing, a) {
    int input = 4;
    auto output = std::vector<std::vector<std::string>>{{".Q..", "...Q", "Q...", "..Q."},{"..Q.", "Q...", "...Q", ".Q.."}};
    auto rtn = solve_backtransing(input);
    EXPECT_TRUE(is_equal(output, rtn));
}

TEST(solve_backtransing, b) {
    int input = 1;
    auto output = std::vector<std::vector<std::string>>{{"Q"}};
    auto rtn = solve_backtransing(input);
    EXPECT_TRUE(is_equal(output, rtn));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}