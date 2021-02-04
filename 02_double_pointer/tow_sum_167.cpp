#include <gtest/gtest.h>
#include <vector>
#include <iostream>

using namespace std;

vector<int> two_sum(const vector<int>& sorted_array, int target) {

    if (sorted_array.size() < 2) {
        return vector<int>{};
    }

    size_t start_idx = 0;
    size_t end_idx = sorted_array.size() - 1;
    int sum = 0;
    while (start_idx < end_idx) {
        sum = sorted_array[start_idx] + sorted_array[end_idx];
        if (sum == target) {
            return vector<int>{static_cast<int>(start_idx+1), static_cast<int>(end_idx+1)};
        } else if (sum > target) {
            --end_idx;
        } else {
            ++start_idx;
        }
    }

    return vector<int>{};
}

TEST(baidu, a) 
{
    auto input = vector<int>{2,7,11,15};
    auto target = 9;
    auto rtn = two_sum(input, target);
    EXPECT_EQ(rtn[0], 1);
    EXPECT_EQ(rtn[1], 2);
}

TEST(baidu, b) 
{
    auto input = vector<int>{1,2,7,11,15};
    auto target = 9;
    auto rtn = two_sum(input, target);
    EXPECT_EQ(rtn[0], 2);
    EXPECT_EQ(rtn[1], 3);
}

TEST(baidu, c) 
{
    auto input = vector<int>{1,2,7,11,15};
    auto target = 8;
    auto rtn = two_sum(input, target);
    EXPECT_EQ(rtn[0], 1);
    EXPECT_EQ(rtn[1], 3);
}

TEST(baidu, d) 
{
    auto input = vector<int>{1};
    auto target = 8;
    auto rtn = two_sum(input, target);
    EXPECT_TRUE(rtn.empty());
}

TEST(baidu, e) 
{
    auto input = vector<int>{1, 2, 3};
    auto target = 8;
    auto rtn = two_sum(input, target);
    EXPECT_TRUE(rtn.empty());
}

TEST(baidu, f) 
{
    auto input = vector<int>{1, 2, 3};
    auto target = 2;
    auto rtn = two_sum(input, target);
    EXPECT_TRUE(rtn.empty());
}

int main(int argc, char* argv[]) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}