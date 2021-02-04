// https://leetcode.com/problems/linked-list-random-node/

#include <iostream>
#include <algorithm>
#include <vector>

/**
 * Definition for singly-linked list.
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* head_;
    /** @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node. */
    Solution(ListNode* head) : head_(head) {}
    
    /** Returns a random node's value. */
    int getRandom() {
        int ans = head_->val;
        ListNode* node = head_->next;
        int i = 2;
        while (node) {
            if (std::rand() % i == 0) {
                ans = node->val;
            }
            ++i;
            node = node->next;
        }
        return ans;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */

int main(int argc, char* []) {
    ListNode* head;
    ListNode* node = new ListNode(0);
    for (int i = 1; i < 10; ++i) {
        head = new ListNode(i, node);
        node = head;
    }
    
    auto count = std::vector<int>(10, 0);

    Solution* obj = new Solution(head);
    int total = 500000;
    std::cout << "total: " << total << std::endl;
    for (int i = 0; i < total; ++i) {
        ++count[obj->getRandom()];
    }
    for (auto x: count) {
        std::cout << x / (float)total << std::endl;
    }
}