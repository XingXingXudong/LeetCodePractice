#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <unordered_set>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x): val(x), next(nullptr) {}
};

void delete_list(ListNode* p) {
    ListNode* next = nullptr;
    auto ps = std::unordered_set<ListNode*>{};
    while (p && ps.find(p) == ps.end()) {
        ps.insert(p);
        std::cout << "delete: " << p->val << std::endl;
        next = p->next;
        delete p;
        p = next;
    }
}

ListNode* find_sycle_start(ListNode* p) {
    if (p == nullptr || p->next == nullptr || p->next->next == nullptr) {
        return nullptr;
    }

    ListNode* p_fast = p->next->next;
    ListNode* p_slow = p->next;

    while (p_fast != p_slow) {
        if (p_fast == nullptr || p_fast->next == nullptr || p_fast->next->next == nullptr) {
            return nullptr;
        }
        p_fast = p_fast->next->next;
        p_slow = p_slow->next;
    }

    p_fast = p;
    while (p_fast != p_slow) {
        p_fast = p_fast->next;
        p_slow = p_slow->next;
    }

    return p_fast;
}


TEST(cycle, a) {
    ListNode* p = nullptr;
    ListNode* head = nullptr;
    p = new ListNode(3);
    head = p;
    for (auto x: std::vector<int>{2, 0, -4}) {
        p->next = new ListNode(x);
        p = p->next;
    }
    p->next = head->next;

    auto rtn = find_sycle_start(head);

    EXPECT_NE(rtn, nullptr);

    EXPECT_EQ(rtn->val, 2);

    delete_list(head);
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}