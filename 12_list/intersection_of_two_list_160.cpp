// https://leetcode.com/problems/intersection-of-two-linked-lists/

#include <gtest/gtest.h>
#include "list_node.h"
#include <iostream>

// 如果两个列表的长度相同，则以此向后移动比较即可；
// 如果连个列表的长度不同，在长列表上头指针先移动“多出来的长度的步数",使得起始比较的节点的到尾部节点的长度一致
ListNode* intersection(ListNode* headA, ListNode* headB) {
    if (!headA || !headB) {
        return nullptr;
    }
    int len_a=0, len_b=0;
    ListNode* cur_a = headA, *cur_b = headB;
    while (cur_a) {
        ++len_a;
        cur_a = cur_a->next;
    }
    while (cur_b) {
        ++len_b;
        cur_b = cur_b->next;
    }
    cur_a = headA;
    cur_b = headB;
    if (len_a > len_b) {
        for (int i = 0; i < len_a - len_b; ++i) {
            cur_a = cur_a->next;
        }
    }
    if (len_b > len_a) {
        for (int i = 0; i < len_b - len_a; ++i) {
            cur_b = cur_b->next;
        }
    }

    while(cur_a != cur_b) {
        cur_a = cur_a->next;
        cur_b = cur_b->next;
    }
    return cur_a;
}

// 设列表A的头节点到相交节点的的长度为a，列表B的头节点到相交节点的长度为b，公共部分的长度为c。
// 两个指针同时从两个列表的头节点开始向后移动，若达到尾部节点，则从头节点开始继续下一次移动；
// 则经过a+b+c次移动达到公共节点，或者经过a*b的最小公倍数次，同时达到为列表尾部（没有公共节点
ListNode* intersectionA(ListNode* headA, ListNode* headB) {
    ListNode *curA = headA, *curB = headB;
    while (curA != curB) {
        curA = curA ? curA->next : headA;
        curB = curB ? curB->next : headB;
    }
    return curA;   // 或者在a+b+c步后，满足curA == curB，找到公共节点；或者同时到达尾部节点，没有公共节点；
}

TEST(intersection, a) {
    List* com_list = new List({2,4});
    List* list_a = new List({1, 9, 1});
    list_a->head->next->next->next = com_list->head;
    List* list_b = new List({3});
    list_b->head->next = com_list->head;
    printList(list_a->head);
    printList(list_b->head);
    ListNode* node = intersection(list_a->head, list_b->head);
    EXPECT_EQ(node->val, 2);
}

TEST(intersection, b) {
    List* com_list = new List({8,4,5});
    List* list_a = new List({4, 1});
    list_a->head->next->next = com_list->head;
    List* list_b = new List({5, 6, 1});
    list_b->head->next->next->next = com_list->head;
    printList(list_a->head);
    printList(list_b->head);
    ListNode* node = intersection(list_a->head, list_b->head);
    EXPECT_EQ(node->val, 8);
}

TEST(intersection, c) {
    List* com_list = new List({});
    List* list_a = new List({4, 1});
    list_a->head->next->next = com_list->head;
    List* list_b = new List({5, 6, 1});
    list_b->head->next->next->next = com_list->head;
    printList(list_a->head);
    printList(list_b->head);
    ListNode* node = intersection(list_a->head, list_b->head);
    EXPECT_EQ(node, nullptr);
}

TEST(intersectionA, a) {
    List* com_list = new List({2,4});
    List* list_a = new List({1, 9, 1});
    list_a->head->next->next->next = com_list->head;
    List* list_b = new List({3});
    list_b->head->next = com_list->head;
    printList(list_a->head);
    printList(list_b->head);
    ListNode* node = intersectionA(list_a->head, list_b->head);
    EXPECT_EQ(node->val, 2);
}

TEST(intersectionA, b) {
    List* com_list = new List({8,4,5});
    List* list_a = new List({4, 1});
    list_a->head->next->next = com_list->head;
    List* list_b = new List({5, 6, 1});
    list_b->head->next->next->next = com_list->head;
    printList(list_a->head);
    printList(list_b->head);
    ListNode* node = intersectionA(list_a->head, list_b->head);
    EXPECT_EQ(node->val, 8);
}

TEST(intersectionA, c) {
    List* com_list = new List({});
    List* list_a = new List({4, 1});
    list_a->head->next->next = com_list->head;
    List* list_b = new List({5, 6, 1});
    list_b->head->next->next->next = com_list->head;
    printList(list_a->head);
    printList(list_b->head);
    ListNode* node = intersectionA(list_a->head, list_b->head);
    EXPECT_EQ(node, nullptr);
}
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}