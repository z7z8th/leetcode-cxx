/* Momenta2019秋招技术岗笔试题
企业提供原题
00:04:32
36/37
[编程题]最小栈

时间限制：1秒

空间限制：131072K
实现一个最小栈，有三种操作，min：得到栈中的最小值，push：在栈顶插入一个元素，pop：弹出栈顶元素，使这三种操作的时间复杂度都是O(1)
要求：语言不限

输入描述:

第一行是一个数Q，接下来Q行每行表示一个操作，每行首先是操作op
若op==0,则输出当前栈中的最小值；
若op==1，表示push，接着正整数x，把在x放进栈顶；
若op==2，表示pop，弹出栈顶元素
保证Q<=500000,保证op==0或2时（即min操作和pop操作时）栈不为空。
你可以假设一开始栈的空的。


输出描述:

对应每个op==0或2，如果是op==0输出当前栈中的最小值，如果是op==2输出弹出的元素。

输入例子1:
7
1 3
1 4
0
1 2
0
2
0

输出例子1:
3
2
2
3

例子说明1:

第一个操作为push 3,此时栈元素为3
第二个操作为push 4,此时栈元素为3,4
第三个操作为min,此时栈元素为3,4，输出最小值3
第四个操作为push 2,此时栈元素为3,4,2
第五个操作为min,此时栈元素为3,4,2，输出最小值2
第六个操作为pop,弹出元素2，此时栈元素为3,4，输出弹出的元素2
第七个操作为min,此时栈元素为3,4，输出最小值3
*/

#include <bits/stdc++.h>

using namespace std;

class MinStack {
public:
    int min(int a, int b) {
        return a < b ? a : b;
    }
    struct MSNode {
        int val;
        int minval;
        MSNode(int x) : val(x), minval(x) {
        }
    };
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        MSNode node(x);
        if (stk.size())
            node.minval = min(node.minval, stk.back().minval);
        stk.emplace_back(node);
    }
    
    int pop() {
        if (!stk.size())
            return -1;
        int val = stk.back().val;
        stk.pop_back();
		return val;
    }
    
    int top() {
        return stk.back().val;
    }
    
    int getMin() {
        return stk.back().minval;
    }
    vector<MSNode> stk;
};

int main() {
	int n;
	enum MIN_STACK_OP {
		STK_GET_MIN = 0,
		STK_PUSH = 1,
		STK_POP = 2,
	};
	while (cin >> n) {
		MinStack mstk;
		for (int i=0; i<n; i++) {
			int op;
			int val;
			cin >> op;
			switch (op) {
				case STK_GET_MIN:
					cout << mstk.getMin() << endl;
					break;
				case STK_PUSH:
					cin >> val;
					mstk.push(val);
					break;
				case STK_POP:
					cout << mstk.pop() << endl;
					break;
				default:
					cout << "unknown op " << op << endl;
			};
		}
	}
}