/* 144. Binary Tree Preorder Traversal
Medium

Given a binary tree, return the preorder traversal of its nodes' values.

Example:

Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [1,2,3]

Follow up: Recursive solution is trivial, could you do it iteratively?
Accepted
364,477
Submissions
697,858 */

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
    void preorderTraversalEx(TreeNode* root) {
        if (!root)
            return;
        trav.push_back(root->val);
        if (root->left)
            preorderTraversalEx(root->left);
        if (root->right)
            preorderTraversalEx(root->right);
    }
    vector<int> preorderTraversal(TreeNode* root) {
        trav.clear();
        preorderTraversalEx(root);
        //return std::move(trav); // 4ms
        return trav; // 0ms
    }
    vector<int> trav;
};

/* Iterative 
 * 0ms < 100%, 9.1MB < 100%.
 */

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> trav;
        deque<TreeNode *> que;
		TreeNode* node = root;
        while (node)  {
            que.push_back(node);
			trav.push_back(node->val);
			node = node->left;
		}
        while(!que.empty()) {
            TreeNode *node = que.back();
            que.pop_back();
			node = node->right;
            while (node)  {
				que.push_back(node);
				trav.push_back(node->val);
				node = node->left;
			}
        }
        return trav;
    }
};

/*
[1,null,2,3] -> [1,2,3]
[2,1,3,null,4] -> [2,1,4,3]
 */