/* 155. Min Stack
Easy

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

    push(x) -- Push element x onto stack.
    pop() -- Removes the element on top of the stack.
    top() -- Get the top element.
    getMin() -- Retrieve the minimum element in the stack.

 

Example:

MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2.

 
Accepted
346,936
Submissions
895,033 */

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
    
    void pop() {
        if (!stk.size())
            return;
        int val = stk.back().val;
        stk.pop_back();
    }
    
    int top() {
        return stk.back().val;
    }
    
    int getMin() {
        return stk.back().minval;
    }
    vector<MSNode> stk;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

