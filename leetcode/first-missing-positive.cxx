/* 41. First Missing Positive
Hard

Given an unsorted integer array, find the smallest missing positive integer.

Example 1:

Input: [1,2,0]
Output: 3

Example 2:

Input: [3,4,-1,1]
Output: 2

Example 3:

Input: [7,8,9,11,12]
Output: 1

Note:

Your algorithm should run in O(n) time and uses constant extra space.
Accepted
228,351
Submissions
777,612 */

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        auto it = lower_bound(nums.begin(), nums.end(), 1);
        if (it == nums.end() || *it != 1)
            return 1;
        
        for (size_t i=it-nums.begin(); i<nums.size(); i++) {
            if (i < nums.size()-1) {
                if (nums[i+1] != nums[i] && nums[i+1] != nums[i]+1)
                    return nums[i]+1;
            }
        }
        return nums.back()+1;
    }
};

/* 
[1,2,0]
[3,4,-1,1]
[7,8,9,11,12]
 */

/*
Possible tune clue:
1. move value at any index to nums[value-1] if value is positive.
2. walk through the fixed nums[]
 */