/* 98. Validate Binary Search Tree
Medium

Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

    The left subtree of a node contains only nodes with keys less than the node's key.
    The right subtree of a node contains only nodes with keys greater than the node's key.
    Both the left and right subtrees must also be binary search trees.

 

Example 1:

    2
   / \
  1   3

Input: [2,1,3]
Output: true

Example 2:

    5
   / \
  1   4
     / \
    3   6

Input: [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.

Accepted
446,336
Submissions
1,709,198 */

#include <bits/stdc++.h>

using namespace std;

/* Definition for a binary tree node. */
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isValidBSTRange(TreeNode* root, int minVal, int maxVal, bool negInfi = false, bool posiInfi = false) {
        if (!root)
            return true;
        /* if (root->val == INT_MIN && root->left ||
            root->val == INT_MAX && root->right)
            return false;
            */
        if (!negInfi && root->val <= minVal ||
            !posiInfi && root->val >= maxVal)
            return false;
        return isValidBSTRange(root->left, minVal, root->val, negInfi, false) &&
            isValidBSTRange(root->right, root->val, maxVal, false, posiInfi);
    }
    bool isValidBST(TreeNode* root) {
        if (!root)
            return true;
        return isValidBSTRange(root, INT_MIN, INT_MAX, true, true);
    }
};

/* 
[2,1,3]
[5,1,4,null,null,3,6]
[1,1] false
[] true
[2147483647]
[10,5,15,null,null,6,20]
[2147483647]
[-2147483648]
[2147483647, -2147483648]
[-2147483648, null, 2147483647]
 */