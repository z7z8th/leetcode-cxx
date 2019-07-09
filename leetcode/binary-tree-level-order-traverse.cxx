/* 102. Binary Tree Level Order Traversal
Medium

Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7

return its level order traversal as:

[
  [3],
  [9,20],
  [15,7]
]

Accepted
395,306
Submissions
805,398
 */

/* Definition for a binary tree node. */

#define NULL nullptr

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void levelOrder_ex(TreeNode* root, int level = 0) {
        if (!root)
            return;
        if (vec_.size() < level + 1)
            vec_.resize(level+1);
        vec_[level].push_back(root->val);
        levelOrder_ex(root->left, level + 1);
        levelOrder_ex(root->right, level + 1);
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        levelOrder_ex(root);
        return vec_;
    }
    vector<vector<int>> vec_;
};

