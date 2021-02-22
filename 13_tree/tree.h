#ifndef __TREE_H_
#define __TREE_H_

#include <vector>
#include <queue>
#include <string>
#include <iostream>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct Tree
{
    TreeNode* root;
    Tree(const std::vector<std::string>& nodes) {
        if (nodes.empty() || nodes[0] == "null") {
            root = nullptr;
        }
        auto queue_nodes = std::queue<TreeNode*>{};
        root = new TreeNode(std::stoi(nodes[0]));
        queue_nodes.push(root);
        size_t i = 1;
        while (i < nodes.size()) {
            TreeNode* cur = queue_nodes.front();
            queue_nodes.pop();
            if (nodes[i++] != "null") {
                cur->left = new TreeNode(std::stoi(nodes[i]));
                queue_nodes.push(cur->left);
            }
            if (nodes[i++] != "null") {
                cur->right = new TreeNode(std::stoi(nodes[i+1]));
                queue_nodes.push(cur->right);
            }
        }
    }
};

std::vector<int> Tree2Vec(TreeNode* root) {
    auto vec = std::vector<int>{};
    auto record = std::queue<int>{root};
    while (!record.empty()) {
        TreeNode* node = record.front();
        vec.push_back(node);
        record.pop();
        if (node) {
            record.push(vec->left);
            record.push(vec->right);
        } else {
            record.push(nullptr);
            record.push(nullptr);
        }
    }
}

void printTree(TreeNode* root) {
    
}

#endif