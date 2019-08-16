/* 145. Binary Tree Postorder Traversal
Hard

Given a binary tree, return the postorder traversal of its nodes' values.

Example:

Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [3,2,1]

Follow up: Recursive solution is trivial, could you do it iteratively?
Accepted
279,785
Submissions
562,913 */

#include <bits/stdc++.h>

using namespace std;


/* Definition for a binary tree node. */
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/* Recursive */
class Solution {
public:
    void postorderTraversalEx(TreeNode* root) {
        if (!root)
            return;
        if (root->left)
            postorderTraversalEx(root->left);
        if (root->right)
            postorderTraversalEx(root->right);
        trav.push_back(root->val);
    }
    vector<int> postorderTraversal(TreeNode* root) {
        trav.clear();
        postorderTraversalEx(root);
        //return std::move(trav); // 4ms
        return trav; // 0ms
    }
    vector<int> trav;
};

