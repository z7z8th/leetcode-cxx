#if 0
Momenta2019秋招技术岗笔试题
企业提供原题
00:05:08
37/37
[编程题]二叉搜索树判定

时间限制：1秒

空间限制：131072K
给定一个二叉树，判断其是否是一个有效的二叉搜索树。
假设一个二叉搜索树具有如下特征：
节点的左子树只包含小于当前节点的数。
节点的右子树只包含大于当前节点的数。
所有左子树和右子树自身必须也是二叉搜索树。
例如：
输入：
    5
   / \
  1   3
     / \
    4   6
输出: false
二叉树节点定义如下，如果使用其他语言，其二叉树节点定义类似：
/**
 * C++
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
# Python
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None
 
/**
 * Go
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */

输入描述:

第一行两个数n,root，分别表示二叉树有n个节点，第root个节点时二叉树的根
接下来共n行，第i行三个数val_i,left_i,right_i，分别表示第i个节点的值val是val_i,左儿子left是第left_i个节点，右儿子right是第right_i个节点。
节点0表示空。
1<=n<=100000,保证是合法的二叉树


输出描述:

输出"true"如果给定二叉树是二叉搜索树，否则输出"false"


输入例子1:

5 1
5 2 3
1 0 0
3 4 5
4 0 0
6 0 0


输出例子1:

false


输入例子2:

5 1
2 2 3
1 0 0
4 4 5
3 0 0
6 0 0


输出例子2:

true

#endif

#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isValidBSTRange(TreeNode* root, int minVal, int maxVal, bool negInfi = false, bool posiInfi = false) {
        /*if (!root)
            return true;
            */
        /* if (root->val == INT_MIN && root->left ||
            root->val == INT_MAX && root->right)
            return false;
            */
        if (!negInfi && root->val <= minVal ||
            !posiInfi && root->val >= maxVal)
            return false;
        return (!root->left ||
                isValidBSTRange(root->left, minVal, root->val, negInfi, false)) &&
                (!root->right || 
                isValidBSTRange(root->right, root->val, maxVal, false, posiInfi));
    }
    bool isValidBST(TreeNode* root) {
        if (!root)
            return true;
        return isValidBSTRange(root, INT_MIN, INT_MAX, true, true);
    }
};

int main() {
    int n;
    int root_i;
    while (cin >> n >> root_i) {
        vector<TreeNode> tree(n, 0);
        for (int i=0; i<n; i++) {
            unsigned int l_i;
            unsigned int r_i;
            cin >> tree[i].val;
            cin >> l_i >> r_i;
            if (l_i)
                tree[i].left = &tree[l_i-1];
            if (r_i)
                tree[i].right = &tree[r_i-1];
        }
        TreeNode *root = nullptr;
        if (root_i)
            root = &tree[root_i-1];
        Solution sln;
        bool valid = sln.isValidBST(root);
        cout << (valid ? "true" : "false") << endl;
    };
}