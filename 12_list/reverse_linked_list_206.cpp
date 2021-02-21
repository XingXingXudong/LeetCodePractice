// https://leetcode.com/problems/reverse-linked-list/

#include <gtest/gtest.h>
#include "list_node.h"

ListNode* reverseList(ListNode* head) {
    ListNode *cur = head, *reversedHead = nullptr, *next = nullptr, *prev = nullptr;
    while (cur) {
        next = cur->next;
        if (next == nullptr) {
            reversedHead = cur;
        }
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return reversedHead;
}

ListNode* reverseListRe(ListNode* head, ListNode* prev = nullptr) {
    if (!head) {
        return prev;
    }
    ListNode* next = head->next;
    head->next = prev;
    return reverseListRe(next, head);
}

TEST(reverseListRe, a) {
    auto inputs = std::vector<int>{1,2,3,4,5};
    auto exp = std::vector<int>{5,4,3,2,1};
    List* pList = new List(inputs);
    printList(pList->head);
    ListNode* reversed_list_head = reverseListRe(pList->head);
    printList(reversed_list_head);
    auto output = List2Vec(reversed_list_head);
    EXPECT_TRUE(output == exp);
}

TEST(reverseListRe, b) {
    auto inputs = std::vector<int>{1,2};
    auto exp = std::vector<int>{2,1};
    List* pList = new List(inputs);
    printList(pList->head);
    ListNode* reversed_list_head = reverseListRe(pList->head);
    printList(reversed_list_head);
    auto output = List2Vec(reversed_list_head);
    EXPECT_TRUE(output == exp);
}

TEST(reverseListRe, c) {
    auto inputs = std::vector<int>{};
    auto exp = std::vector<int>{};
    List* pList = new List(inputs);
    printList(pList->head);
    ListNode* reversed_list_head = reverseListRe(pList->head);
    printList(reversed_list_head);
    auto output = List2Vec(reversed_list_head);
    EXPECT_TRUE(output == exp);
}

TEST(reverseList, a) {
    auto inputs = std::vector<int>{1,2,3,4,5};
    auto exp = std::vector<int>{5,4,3,2,1};
    List* pList = new List(inputs);
    printList(pList->head);
    ListNode* reversed_list_head = reverseList(pList->head);
    printList(reversed_list_head);
    auto output = List2Vec(reversed_list_head);
    EXPECT_TRUE(output == exp);
}

TEST(reverseList, b) {
    auto inputs = std::vector<int>{1,2};
    auto exp = std::vector<int>{2,1};
    List* pList = new List(inputs);
    printList(pList->head);
    ListNode* reversed_list_head = reverseList(pList->head);
    printList(reversed_list_head);
    auto output = List2Vec(reversed_list_head);
    EXPECT_TRUE(output == exp);
}

TEST(reverseList, c) {
    auto inputs = std::vector<int>{};
    auto exp = std::vector<int>{};
    List* pList = new List(inputs);
    printList(pList->head);
    ListNode* reversed_list_head = reverseList(pList->head);
    printList(reversed_list_head);
    auto output = List2Vec(reversed_list_head);
    EXPECT_TRUE(output == exp);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
