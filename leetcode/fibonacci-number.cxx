/* 509. Fibonacci Number
Easy

The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, such that each number is the sum of the two preceding ones, starting from 0 and 1. That is,

F(0) = 0,   F(1) = 1
F(N) = F(N - 1) + F(N - 2), for N > 1.

Given N, calculate F(N).

 

Example 1:

Input: 2
Output: 1
Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.

Example 2:

Input: 3
Output: 2
Explanation: F(3) = F(2) + F(1) = 1 + 1 = 2.

Example 3:

Input: 4
Output: 3
Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3.

 

Note:

0 ≤ N ≤ 30.
Accepted
81,358
Submissions
122,263 */

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    Solution() {
        if (fibs[1])
            return;
        fibs[1] = 1;
        for (int i=2; i<31; i++) {
            fibs[i] = fibs[i-1] + fibs[i-2];
        }
    }
    int fib(int N) {
        return fibs[N];
    }
    static int fibs[31];
};
int Solution::fibs[31];

/* 
input:
2
3
7
15
25
30
output:
1
2
13
610
75025
832040
*/