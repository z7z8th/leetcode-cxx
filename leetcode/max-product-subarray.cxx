/* 152. Maximum Product Subarray
Medium

Given an integer array nums, find the contiguous subarray within an array (containing at least one number) which has the largest product.

Example 1:

Input: [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.

Example 2:

Input: [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.

Accepted
224,177
Submissions
756,352 */

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if (nums.size() == 0)
            return 0;
        int maxProd = nums[0];
        int prod;
        int firstNegIdx = -1;
        int nextZeroIdx = -1;
        for (int si=0; si<nums.size(); si++) {
            prod = nums[si];
            if (prod == 0)
                continue;
            firstNegIdx = -1;
            nextZeroIdx = -1;
            if (prod < 0)
                firstNegIdx = si;
			if (prod > maxProd)
				maxProd = prod;
            for (int i=si+1; i<nums.size(); i++) {
                int n = nums[i];

                if (n > maxProd)
                    maxProd = n;
                if (n == 0) {
                    nextZeroIdx = i;
                    break;
                }
				prod *= n;
                if (prod > maxProd)
                    maxProd = prod;
                if (firstNegIdx < 0 && n < 0)
                    firstNegIdx = i;
            }
            if (firstNegIdx != -1 && prod < 0) // negtive prod, try from the one after first neg
                si = firstNegIdx;
            else if (nextZeroIdx != -1) // positive prod, try from the one after zero
                si = nextZeroIdx;
            else // positive and no zero, then done, !!!IMPORTANT!!!
                break;
        }
        return maxProd;
    }
};

/*
[2, -5,-2,-3,4]
[-2,0,-3,-3]
[2,3,-2,4]
[-2,0,-1]
 */