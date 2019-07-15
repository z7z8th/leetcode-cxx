/*
54. Spiral Matrix
Medium

Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

Example 1:

Input:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
Output: [1,2,3,6,9,8,7,4,5]

Example 2:

Input:
[
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9,10,11,12]
]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]

Accepted
245,399
Submissions
796,894
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void spiralCircle(vector<vector<int>>& m, int sidx, int eidx, vector<int>& vec) 
    {
        if (sidx > eidx)
            return;
        int mn = m.size();
        int n = eidx-sidx;
        int row_cnt = mn-1-sidx*2;
        for (int i=0; i<n; i++) {
            vec.emplace_back(m[sidx][sidx+i]);
        }
        for (int i=0; i<row_cnt; i++) {
            vec.emplace_back(m[sidx+i][eidx]);
        }
        for (int i=0; row_cnt>0 && i<n; i++) {
            vec.emplace_back(m[mn-1-sidx][eidx-i]);
        }
        n = eidx-sidx;
        for (int i=0; n>0 && i<row_cnt; i++) {
            vec.emplace_back(m[mn-1-sidx-i][sidx]);
        }
        /*
        if (!n && !row_cnt) {
            vec.emplace_back(m[sidx][eidx]);
        }
        */
    }
    vector<int> spiralOrder(vector<vector<int>>& m) {
        int row_cnt = m.size();
        vector<int> vec;
        if (row_cnt == 0)
            return vec;
        int col_cnt = m[0].size();
        if (row_cnt == 1){
            vec.resize(col_cnt);
            copy(m[0].begin(), m[0].end(), vec.begin());
            return vec;
        }
		// walk the out border
        for (int row=0; row < min(row_cnt/2, col_cnt/2); row++) {
            spiralCircle(m, row, col_cnt-1-row, vec);
        }

		// deal with inner single vertical line
        if (row_cnt >= col_cnt && (col_cnt & 1)) {
            int row_idx = col_cnt/2;
            for (int i=0; i<row_cnt-row_idx*2; i++) {
                vec.emplace_back(m[row_idx+i][row_idx]);
            }
        }
		// deal with inner single horizonal line
        if (row_cnt < col_cnt && (row_cnt & 1)) {
            int row_idx = row_cnt/2;
            for (int i=0; i<col_cnt-row_idx*2; i++) {
                vec.emplace_back(m[row_idx][row_idx+i]);
            }
        }
        
        return vec;
    }
};