/* 101. Symmetric Tree
Easy

Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3

 

But the following [1,2,2,null,3,null,3] is not:

    1
   / \
  2   2
   \   \
   3    3

 

Note:
Bonus points if you could solve it both recursively and iteratively.
Accepted
440,695
Submissions
1,000,187 */

/*  Definition for a binary tree node. */
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

#include <bits/stdc++.h>

using namespace std;

/* recursive solution */
class Solution {
public:
    bool isSymmetric(TreeNode* left, TreeNode* right) {
        if (!left && !right)
            return true;
        if (!left || !right || left->val != right->val)
            return false;
        return isSymmetric(left->left, right->right) &&
            isSymmetric(left->right, right->left);
    }

    bool isSymmetric(TreeNode* root) {
        if (!root)
            return true;
        return isSymmetric(root->left, root->right);
    }
};

