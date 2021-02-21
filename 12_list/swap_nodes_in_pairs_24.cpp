// https://leetcode.com/problems/swap-nodes-in-pairs/

#include <gtest/gtest.h>
#include "list_node.h"

ListNode* swapNode(ListNode* head) {
    // ListNode *p = head, *s;
    // if (p && p->next) {
    //    s = p->next;
    //    p->next = s->next;
    //    s->next = p;
    //    head = s;
    //    while (p->next && p->next->next) {
    //        s = p->next->next;
    //        p->next->next = s->next;
    //        s->next = p->next;
    //        p->next = s;
    //        p = s->next; 
    //     }
    // }
    // return head;
    ListNode *cp = head, *np = nullptr;
    if (cp && cp->next) {
        np = cp->next;
        cp->next = np->next;
        np->next = cp;
        head = np;
        while (cp->next && cp->next->next) {
            np = cp->next->next;
            cp->next->next = np->next;
            np->next = cp->next;
            cp->next = np; 
            cp = np->next;
        }
    }
    return head;
}

TEST(swapNode, a) {
    auto inputs = std::vector<int>{1, 2, 3, 4};
    auto exp_out = std::vector<int>{2, 1, 4, 3};
    List* inputs_list = new List(inputs);
    ListNode* out = swapNode(inputs_list->head);
    printList(out);
    auto out_vec = List2Vec(out);
    EXPECT_TRUE(out_vec == exp_out);
}

TEST(swapNode, b) {
    auto inputs = std::vector<int>{1};
    auto exp_out = std::vector<int>{1};
    List* inputs_list = new List(inputs);
    ListNode* out = swapNode(inputs_list->head);
    auto out_vec = List2Vec(out);
    EXPECT_TRUE(out_vec == exp_out);
}

TEST(swapNode, c) {
    auto inputs = std::vector<int>{};
    auto exp_out = std::vector<int>{};
    List* inputs_list = new List(inputs);
    ListNode* out = swapNode(inputs_list->head);
    auto out_vec = List2Vec(out);
    EXPECT_TRUE(out_vec == exp_out);
}
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}