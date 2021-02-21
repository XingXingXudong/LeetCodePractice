// https://leetcode.com/problems/merge-two-sorted-lists/

#include <gtest/gtest.h>
#include "list_node.h"

ListNode* merge(ListNode* l1, ListNode* l2) {
    ListNode* dummy = new ListNode(0);
    ListNode* node = dummy;
    while (l1 && l2) {
        if (l1->val <= l2->val) {
            node->next = l1;
            l1 = l1->next;
        } else {
            node->next = l2;
            l2 = l2->next;
        }
        node = node->next;
    }
    node->next = l1 ? l1 : l2;
    return dummy->next;
}

// 递归写法
ListNode* mergeRe(ListNode*l1, ListNode* l2) {
    if (!l1) {
        return l2;
    }
    if (!l2) {
        return l1;
    }
    if (l1->val > l2->val) {
        l2->next = mergeRe(l1, l2->next);
        return l2;
    }
    l1->next = mergeRe(l1->next, l2);
    return l1;
}


TEST(merge, a) {
    auto l1 = std::vector<int>{1,2,4}; 
    auto l2 = std::vector<int>{1,3,4};
    auto exp = std::vector<int>{1,1,2,3,4,4};
    List* list_l1 = new List(l1);
    List* list_l2 = new List(l2);
    ListNode* out = merge(list_l1->head, list_l2->head);
    auto out_list = List2Vec(out);
    EXPECT_TRUE(out_list == exp);
}

TEST(merge, b) {
    auto l1 = std::vector<int>{}; 
    auto l2 = std::vector<int>{0};
    auto exp = std::vector<int>{0};
    List* list_l1 = new List(l1);
    List* list_l2 = new List(l2);
    ListNode* out = merge(list_l1->head, list_l2->head);
    auto out_list = List2Vec(out);
    EXPECT_TRUE(out_list == exp);
}

TEST(merge, c) {
    auto l1 = std::vector<int>{}; 
    auto l2 = std::vector<int>{};
    auto exp = std::vector<int>{};
    List* list_l1 = new List(l1);
    List* list_l2 = new List(l2);
    ListNode* out = merge(list_l1->head, list_l2->head);
    auto out_list = List2Vec(out);
    EXPECT_TRUE(out_list == exp);
}

TEST(mergeRe, a) {
    auto l1 = std::vector<int>{1,2,4}; 
    auto l2 = std::vector<int>{1,3,4};
    auto exp = std::vector<int>{1,1,2,3,4,4};
    List* list_l1 = new List(l1);
    List* list_l2 = new List(l2);
    ListNode* out = mergeRe(list_l1->head, list_l2->head);
    printList(out);
    auto out_list = List2Vec(out);
    EXPECT_TRUE(out_list == exp);
}

TEST(mergeRe, b) {
    auto l1 = std::vector<int>{}; 
    auto l2 = std::vector<int>{0};
    auto exp = std::vector<int>{0};
    List* list_l1 = new List(l1);
    List* list_l2 = new List(l2);
    ListNode* out = mergeRe(list_l1->head, list_l2->head);
    auto out_list = List2Vec(out);
    EXPECT_TRUE(out_list == exp);
}

TEST(mergeRe, c) {
    auto l1 = std::vector<int>{}; 
    auto l2 = std::vector<int>{};
    auto exp = std::vector<int>{};
    List* list_l1 = new List(l1);
    List* list_l2 = new List(l2);
    ListNode* out = mergeRe(list_l1->head, list_l2->head);
    auto out_list = List2Vec(out);
    EXPECT_TRUE(out_list == exp);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}