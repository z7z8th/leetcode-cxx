/* 46. Permutations
Medium

Given a collection of distinct integers, return all possible permutations.

Example:

Input: [1,2,3]
Output:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]

Accepted
419,174
Submissions
737,798 */

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void permuteEx(vector<int>& nums, vector<bool>& bs, vector<int>& onePmt) {
        for (int i=0; i<nums.size(); i++) {
            if (bs[i])
                continue;
            bs[i] = true;
            onePmt.push_back(nums[i]);
            if (onePmt.size() >= nums.size())
                pmt.emplace_back(onePmt);
            else
                permuteEx(nums, bs, onePmt);
            onePmt.pop_back();
            bs[i] = false;
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        pmt.clear();
        vector<bool> bs(nums.size(), false);
        vector<int> onePmt;
        permuteEx(nums, bs, onePmt);

        return pmt;
    }
    int cnt = 0;
    vector<vector<int>> pmt;
};