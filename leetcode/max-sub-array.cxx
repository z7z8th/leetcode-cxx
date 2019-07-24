/* 53. Maximum Subarray
Easy

Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

Example:

Input: [-2,1,-3,4,-1,2,1,-5,4],
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.

Follow up:

If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
Accepted
574,820
Submissions
1,304,876 */

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.size() == 0)
            return 0;
        int maxSum = nums[0];
        int sum = nums[0];
        for (int i=1; i<nums.size(); i++) {
            if (sum > maxSum)
                maxSum = sum;
			/* add next num only when sum > 0, 
			   otherwise we drop it and begin another round
			 */
            if (sum > 0)
                sum += nums[i];
            else
                sum = nums[i];
        }
        if (sum > maxSum)
            maxSum = sum;
        return maxSum;
    }
};