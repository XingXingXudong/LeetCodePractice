// https://leetcode.com/problems/range-sum-query-immutable/

#include <vector>
#include <gtest/gtest.h>
#include <iostream>

class NumArray {
private:
    std::vector<int> acc_sum;
public:
    NumArray(std::vector<int>& nums) {
        acc_sum = std::vector<int>(nums.size() + 1, 0);
        for (int i = 0; i < (int)nums.size(); ++i) {
            acc_sum[i + 1] = acc_sum[i] + nums[i];
        }
    }
    int sumRange(int i, int j) {
        return acc_sum[j+1] - acc_sum[i];
    }
};

TEST(numArray, a) {
    auto inputs = std::vector<int>{-2, 0, 3, -5, 2, -1};
    NumArray* numArray = new NumArray(inputs);
    EXPECT_EQ(numArray->sumRange(0, 2), 1);    // return 1 ((-2) + 0 + 3)
    EXPECT_EQ(numArray->sumRange(2, 5), -1);   // return -1 (3 + (-5) + 2 + (-1)) 
    EXPECT_EQ(numArray->sumRange(0, 5), -3);   // return -3 ((-2) + 0 + 3 + (-5) + 2 + (-1))
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}