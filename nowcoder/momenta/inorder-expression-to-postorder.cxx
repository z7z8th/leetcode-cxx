#if 0
 Momenta2019秋招技术岗笔试题
企业提供原题
00:03:26
35/37
[编程题]中缀表达式转后缀表达式

时间限制：1秒
空间限制：131072K

将中缀表达式转为后缀表达式，输入 a+b*c/d-a+f/b 输出 abc*d/+a-fb/+
要求：语言不限；输入输出均为单个字符串；操作数用单个小写字母表示，操作符只需支持 +-*/，按照四则运算顺序确定优先级，不包含括号

输入描述:
一个字符串为合法的中缀表达式
字符串长度不超过200000

输出描述:
对应的后缀表达式

输入例子1:
a+b*c/d-a+f/b

输出例子1:
abc*d/+a-fb/+
#endif

#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *parent;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int v, TreeNode *p = nullptr) : val(v), parent(p), left(nullptr), right(nullptr) {}
};

class Solution
{
public:
	/* 
	TreeNode *rotateLeft(TreeNode *top)
	{
		TreeNode *newTop = top->right;
		//TreeNode *left = top->left;
		TreeNode *parent = top->parent;


		top->parent = newTop;
		top->right = nullptr;

		newTop->left = top;
		newTop->parent = parent;

		if (parent) {
			if (parent->left == top) {
				parent->left = newTop;
			} else if (parent->right == top) {
				parent->right = newTop;
			}
		}
		return newTop;
	}
	bool isOp(char ch) {
		switch (ch) {
			case '+':
			case '-':
			case '*':
			case '/':
				return true;
			default:
				return false;
		}
	}
	*/

	bool isPlusMinus(char ch) {
		return ch == '+' || ch == '-';
	}
	bool isMulDiv(char ch) {
		return ch == '*' || ch == '/';
	}
	TreeNode *constructTree(const string &s)
	{
		TreeNode *root;
		root = new TreeNode(s[0]);
		TreeNode *parent = root;
		TreeNode **p = &root->right;
		for (size_t i = 1; i < s.length(); i++) {
			char ch = s[i];
			TreeNode *node = new TreeNode(ch /* , parent */);
			if (isPlusMinus(ch)) {
				node->left = root;
				root->parent = node;
				root = node;
				//p = &node->right;
			} else if (isMulDiv(ch)) {
				TreeNode *tmp = parent;
				while (tmp && !isPlusMinus(tmp->val)) {

					tmp = tmp->parent;
				}
				if (tmp) {
					TreeNode *prevRight = tmp->right;
					tmp->right = node;
					node->left = prevRight;
					node->parent = tmp;
					prevRight->parent = node;
				} else {
					node->left = root;
					root->parent = node;
					root = node;
				}
			} else {
				*p = node;
				node->parent = parent;
			}
			parent = node;
			//parent = rotateLeft((*p)->parent);
			p = &parent->right;
		}
		return root;
	}
	void destructTree(TreeNode *root) {
		if (!root)
			return;

		if (root->left)
			destructTree(root->left);
		if (root->right)
			destructTree(root->right);
		delete root;
	}
	void printTreePostOrder(TreeNode *root, string &out) {
		if (root->left) {
			printTreePostOrder(root->left, out);
		}
		if (root->right) {
			printTreePostOrder(root->right, out);
		}
		out.push_back(static_cast<char>(root->val));
		//cout << root->val;
	}
	string inorderToPostOrder(const string &inorder)
	{
		TreeNode *inorderTree = constructTree(inorder);
		string postorderExpression;
		printTreePostOrder(inorderTree, postorderExpression);
		//cout << endl;
		destructTree(inorderTree);
		return postorderExpression;
	}
};

int main()
{
	string expression;
	while (cin >> expression) {
		Solution sln;
		auto ret = std::move(sln.inorderToPostOrder(expression));
		cout << ret << endl;
	}
}

#if 0
a+b*c/d-a+f/b
abc*d/+a-fb/+

a+b*c/d*e/g-a+f/b*h/i+j-k*m/n

#endif