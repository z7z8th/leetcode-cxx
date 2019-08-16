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
	void postorderTraversalEx(TreeNode *root) {
		if (!root)
			return;
		if (root->left)
			postorderTraversalEx(root->left);
		if (root->right)
			postorderTraversalEx(root->right);
		trav.push_back(root->val);
	}
	vector<int> postorderTraversal(TreeNode *root) {
		trav.clear();
		postorderTraversalEx(root);
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
	vector<int> postorderTraversal(TreeNode *root) {
		vector<int> trav;
		deque<TreeNode *> que;
		TreeNode *node = root;
		while (node) {
			que.push_back(node);
			//trav.push_back(node->val);
			node = node->left;
		}
		deque<TreeNode *> postQue;
		while (!que.empty()) {
			TreeNode *node = que.back();
			que.pop_back();
			if (!node) {
				node = postQue.back();
				postQue.pop_back();
				trav.push_back(node->val);
				continue;
			}
			if (!node->right) {
				trav.push_back(node->val);
				continue;
			} else {
				postQue.push_back(node);
			}
			que.push_back(nullptr);

			node = node->right;
			while (node) {
				que.push_back(node);
				//trav.push_back(node->val);
				node = node->left;
			}
		}
		return trav;
	}
};
