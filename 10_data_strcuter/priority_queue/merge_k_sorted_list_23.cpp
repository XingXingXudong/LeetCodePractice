// https://leetcode.com/problems/merge-k-sorted-lists/

#include <vector>
#include <queue>
#include <gtest/gtest.h>

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

bool isEqual(ListNode* l1, ListNode* l2) {
    while (l1 != nullptr && l2 != nullptr) {
        if (l1->val != l2->val) {
            return false;
        }
        l1 = l1->next;
        l2 = l2->next;
    }
    if (l1 != nullptr || l2 != nullptr) {
        return false;
    }
    return true;
}

struct Comp {
    bool operator() (ListNode* l1, ListNode* l2) {
        return l1->val > l2->val;
    }
};

ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    if (lists.empty()) {
        return nullptr;
    }
    auto qs = std::priority_queue<ListNode*, std::vector<ListNode*>, Comp>{};
    for (ListNode* list: lists) {
        if (list) {
            qs.push(list);
        }
    }
    ListNode* dummy = new ListNode(0);
    ListNode* cur = dummy;
    while (!qs.empty()) {
        cur->next = qs.top();
        qs.pop();
        cur = cur->next;
        if (cur->next) {
            qs.push(cur->next);
        }
    }
    return dummy->next;
}

TEST(a, a) {
    // input: [[1,4,5],[1,3,4],[2,6]];
    // output: 1->1->2->3->4->4->5->6
    std::vector<ListNode*> inputs = {
        new ListNode(1, new ListNode(4, new ListNode(5))),
        new ListNode(1, new ListNode(3, new ListNode(4))),
        new ListNode(2, new ListNode(6))
    };
    ListNode* output = new ListNode(1);
    ListNode* cur = output;
    for (auto x: std::vector<int>{1, 2, 3, 4, 4, 5, 6}) {
        cur->next = new ListNode(x);
        cur = cur->next;
    }
    EXPECT_TRUE(isEqual(mergeKLists(inputs), output));
}

TEST(a, b) {
    std::vector<ListNode*> inputs{};
    EXPECT_EQ(mergeKLists(inputs), nullptr);
}

TEST(a, c) {
    std::vector<ListNode*> inputs{nullptr};
    EXPECT_EQ(mergeKLists(inputs), nullptr);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
