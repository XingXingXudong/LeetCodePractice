// https://leetcode.com/problems/random-pick-with-weight/

#include <vector>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <algorithm>

class Solution {
    public:
    std::vector<int> partial_sum_;
    Solution(std::vector<int>& w) : partial_sum_(std::move(w)){
        std::partial_sum(partial_sum_.begin(), partial_sum_.end(), partial_sum_.begin());
    }
    int pickIndex() {
        int rand_pos = (std::rand() % partial_sum_.back()) + 1;
        return std::lower_bound(partial_sum_.begin(), partial_sum_.end(), rand_pos) - partial_sum_.begin();
    }
};


int main(int argc, char* argv[]) {
    std::srand(20);
    auto w = std::vector<int>{1, 1, 2, 3, 3};
    auto count = std::unordered_map<int, int>{};
    Solution* obj = new Solution(w);
    int total = 1000;
    for (int i = 0; i < total; ++i) {
        ++count[obj->pickIndex()];
    }
    for (auto [key, val]: count) {
        std::cout << "count[" << key << "] = " << val / (float)total << std::endl;
    }
    return 0;
}