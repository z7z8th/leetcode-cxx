/* 59. Spiral Matrix II
Medium

Given a positive integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

Example:

Input: 3
Output:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]

Accepted
140,937
Submissions
298,326
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void genCircle(vector<vector<int>> & vec, int row) {
        int mn = vec.size();
        int row_cnt = mn-1-row*2;
        for (int i=0; i<row_cnt; i++) {
            vec[row][row+i] = idx;
            vec[row+i][row+row_cnt] = idx+row_cnt;
            vec[row+row_cnt][row+row_cnt-i] = idx+row_cnt*2;
            vec[row+row_cnt-i][row] = idx+row_cnt*3;
            idx++;
        }
        idx += row_cnt * 3;
    }
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> vec;
        vec.resize(n);
        idx = 1;
        for(int i=0; i<n; i++)
            vec[i].resize(n);
        for (int i=0; i<n/2; i++) {
            genCircle(vec, i);
        }
        if (n&1) {
            vec[n/2][n/2] = idx++;
        }
        return vec;
    }
    int idx = 0;
};