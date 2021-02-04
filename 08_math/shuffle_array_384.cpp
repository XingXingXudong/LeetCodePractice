// https://leetcode.com/problems/shuffle-an-array/
#include <vector>
#include <iostream>
#include <gtest/gtest.h>

class Solution{
    public:
    std::vector<int> arr;
    Solution(std::vector<int>& nums) : arr(std::move(nums)) {}
    std::vector<int> reset() {
        return arr;
    }
    std::vector<int> shuffle() {
        if (arr.empty()) {
            return {};
        }
        std::vector<int> shuffled(arr);
        int n = shuffled.size();
        for (int i = n - 1; i >= 0; --i) {
            std::swap(shuffled[i], shuffled[std::rand() % (i + 1)]);
        }
        return shuffled;
    }
};

template<typename T>
void print_vec(std::vector<T> nums) {
    std::cout << "------------------------------" << std::endl;
    for (auto x: nums) {
        std::cout << x << " ";
    }
    std::cout << "\n------------------------------" << std::endl;
}

int main(int argc, char* argv[]) {
    auto input = std::vector<int>{1, 2, 3, 4, 5};
    Solution * solution = new Solution(input);
    auto shuffle_vec = solution->shuffle();
    print_vec(shuffle_vec);
    auto reset_vec = solution->reset();
    print_vec(reset_vec);

    std::cout << "==============================" << std::endl;

    shuffle_vec = solution->shuffle();
    print_vec(shuffle_vec);
    reset_vec = solution->reset();
    print_vec(reset_vec);
}