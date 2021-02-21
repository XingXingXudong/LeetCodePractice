#ifndef __LIST_NODE_H
#define __LIST_NODE_H

#include <vector>
#include <iostream>

struct ListNode
{
    /* data */
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x): val(x), next(nullptr) {}
    ListNode(int x, ListNode* next): val(x), next(next) {}
};

struct List
{
    ListNode* head;
    List(const std::vector<int>& init) {
        if (init.empty()) {
            head = nullptr;
        } else {
            head = new ListNode(init[0]);
            ListNode* cur = head;
            for (size_t i = 1; i < init.size(); ++i) {
                cur->next = new ListNode(init[i]);
                cur = cur->next;
            }
        }
    }
};

std::vector<int> List2Vec(ListNode* head) {
    auto vec = std::vector<int>{};
    while (head) {
        vec.push_back(head->val);
        head = head->next;
    }
    return vec;
}

void printList(ListNode* head) {
    while (head) {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

#endif