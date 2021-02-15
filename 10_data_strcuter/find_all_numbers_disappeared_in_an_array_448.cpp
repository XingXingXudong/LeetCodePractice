//https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
#include <gtest/gtest.h>
#include <vector>
#include <set>

void print_vec(const std::vector<int>& vec) {
    for (auto x: vec) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

bool is_equal(const std::vector<int>& a, const std::vector<int>& b) {
    // std::cout << "a ";
    // print_vec(a);
    if (a.size() != b.size()) {
        return false;
    }
    auto set_a = std::set<int>(a.begin(), a.end());
    auto set_b = std::set<int>(b.begin(), b.end());
    return set_a == set_b;
}

std::vector<int> findDisappearedNumbers(std::vector<int>& nums) {
    auto record = std::vector<int>(nums.size() + 1, 0);
    for (auto x: nums) {
        ++record[x];
    }
    auto rtn = std::vector<int>{};
    for (int i = 1; i < (int)record.size(); ++i) {
        if (record[i] == 0) {
            rtn.push_back(i);
        }
    }
    return rtn;
}

std::vector<int> findDisappearedNumbers1(std::vector<int>& nums) {
    auto rtn = std::vector<int>{};
    for (auto n: nums) {
        int pos = (n > 0 ? n : -n) - 1;
        if (nums[pos] > 0) {
            nums[pos] = -nums[pos];
        }
    }
    for (int i = 0; i < (int)nums.size(); ++i) {
        if (nums[i] > 0) {
            rtn.push_back(i + 1);
        }
    }
    return rtn;
}

TEST(findDisappearedNumbers, a) {
    auto inputs = std::vector<int>{4,3,2,7,8,2,3,1};
    auto outputs = std::vector<int>{5,6};
    EXPECT_TRUE(is_equal(findDisappearedNumbers(inputs), outputs));
}

TEST(findDisappearedNumbers1, a) {
    auto inputs = std::vector<int>{4,3,2,7,8,2,3,1};
    auto outputs = std::vector<int>{5,6};
    EXPECT_TRUE(is_equal(findDisappearedNumbers1(inputs), outputs));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}