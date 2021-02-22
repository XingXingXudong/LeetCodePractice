// https://leetcode.com/problems/palindrome-linked-list/

#include <gtest/gtest.h>
#include "list_node.h"
#include <stack>

ListNode* findMid(ListNode* head) {
    ListNode* ps = head, *pf = head;
    while (pf) {
        pf = pf->next;
        if (pf) {  // 如果pf能继续往前走，则更新一步pf，保证pf指在中点的位置，奇偶性不同导致
            ps = ps->next;
            pf = pf->next;
        }
    }
    return ps;
}

ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr, *next = nullptr;
    while (head) {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

// 使用O(1)的空间，O(n)的算法
// 1. 使用快慢指针，找到列表的中点；
// 2. 反转列表的后半段；
// 3. 遍历比较
bool isPalindrome1(ListNode* head) {
    if (!head) {
        return false;
    }
    ListNode* mid = findMid(head);
    ListNode* midReversed = reverseList(mid);
    while (midReversed) {
        if (midReversed->val != head->val) {
            return false;
        }
        midReversed = midReversed->next;
        head = head->next;
    }
    return true;
}


// 使用O(n)的辅助空间，O(n)的算法
// 使用辅助栈
bool isPalindrome(ListNode* head) {
    if (!head) {
        return false;
    }
    ListNode* cur = head;
    auto record = std::stack<ListNode*>{};
    while (cur) {
        record.push(cur);
        cur = cur->next;
    }
    cur = head;
    for (size_t i = 0; i < record.size() / 2; ++i) {
        if (cur->val != record.top()->val) {
            return false;
        }
        cur = cur->next;
        record.pop();
    }
    return true;
}

TEST(reverseList, a) {
    List* list = new List({});
    EXPECT_EQ(reverseList(list->head), nullptr);
}

TEST(reverseList, b) {
    List* list = new List({1});
    printList(list->head);
    printList(reverseList(list->head));
}

TEST(reverseList, c) {
    List* list = new List({1, 2});
    printList(list->head);
    printList(reverseList(list->head));
}

TEST(reverseList, d) {
    List* list = new List({1, 2, 3});
    printList(list->head);
    printList(reverseList(list->head));
}

TEST(reverseList, e) {
    List* list = new List({1, 2, 3, 4});
    printList(list->head);
    printList(reverseList(list->head));
}

TEST(findMid, a) {
    List* list = new List({});
    EXPECT_EQ(findMid(list->head), nullptr);
}

TEST(findMid, b) {
    List* list = new List({1});
    EXPECT_EQ(findMid(list->head)->val, 1);
}

TEST(findMid, c) {
    List* list = new List({1, 2});
    EXPECT_EQ(findMid(list->head)->val, 2);
}

TEST(findMid, d) {
    List* list = new List({1, 2, 3});
    EXPECT_EQ(findMid(list->head)->val, 2);
}

TEST(findMid, e) {
    List* list = new List({1, 2, 3, 4});
    EXPECT_EQ(findMid(list->head)->val, 3);
}

TEST(isPalindrome, a) {
    List* list = new List({1, 2});
    EXPECT_FALSE(isPalindrome(list->head));
}

TEST(isPalindrome, b) {
    List* list = new List({1, 2, 2, 1});
    EXPECT_TRUE(isPalindrome(list->head));
}

TEST(isPalindrome, c) {
    List* list = new List({1, 2, 3, 2, 1});
    EXPECT_TRUE(isPalindrome(list->head));
}

TEST(isPalindrome, d) {
    List* list = new List({2});
    EXPECT_TRUE(isPalindrome(list->head));
}

TEST(isPalindrome, e) {
    List* list = new List({});
    EXPECT_FALSE(isPalindrome(list->head));
}

TEST(isPalindrome1, a) {
    List* list = new List({1, 2});
    EXPECT_FALSE(isPalindrome1(list->head));
}

TEST(isPalindrome1, b) {
    List* list = new List({1, 2, 2, 1});
    EXPECT_TRUE(isPalindrome1(list->head));
}

TEST(isPalindrome1, c) {
    List* list = new List({1, 2, 3, 2, 1});
    EXPECT_TRUE(isPalindrome1(list->head));
}

TEST(isPalindrome1, d) {
    List* list = new List({2});
    EXPECT_TRUE(isPalindrome1(list->head));
}

TEST(isPalindrome1, e) {
    List* list = new List({});
    EXPECT_FALSE(isPalindrome1(list->head));
}
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}