/* 47. Permutations II
Medium

Given a collection of numbers that might contain duplicates, return all possible unique permutations.

Example:

Input: [1,1,2]
Output:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]

Accepted
264,739
Submissions
634,169
 */

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void permuteEx(vector<int>& nums, vector<bool>& bs, vector<int>& onePmt, vector<vector<int>>& pmt) {
        for (int i=0; i<nums.size(); i++) {
            if (bs[i])
                continue;
            // already visited a same one, move on to the next different number
            // if we still visit this one, we have to visit the previous one, which will result in duplicates
            if (i>0 && bs[i-1] == false && nums[i] == nums[i-1])
                continue;
            bs[i] = true;
            onePmt.push_back(nums[i]);
            if (onePmt.size() >= nums.size())
                pmt.push_back(onePmt);
            else
                permuteEx(nums, bs, onePmt, pmt);
            onePmt.pop_back();
            bs[i] = false;
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> pmt;
        //pmt.clear();
        vector<bool> bs(nums.size(), false);
        vector<int> onePmt;
        permuteEx(nums, bs, onePmt, pmt);

        return pmt;
    }
};