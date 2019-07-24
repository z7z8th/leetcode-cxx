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


class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if (nums.size() == 0)
            return 0;
        int maxProd = nums[0];
        int prod;
        int firstNegIdx = -1;
        for (int si=0; si<nums.size(); si++) {
            prod = nums[si];
            firstNegIdx = -1;
            if (prod == 0)
                continue;
            if (prod < 0)
                firstNegIdx = si;
            for (int i=si+1; i<nums.size(); i++) {
                int n = nums[i];
                if (firstNegIdx < 0 && n < 0)
                    firstNegIdx = i;
                if (prod > maxProd)
                    maxProd = prod;
                if (nums[i] > maxProd)
                    maxProd = n;
                if (prod != 0)
                    prod *= n;
                else
                    prod = n;
            }
            if (prod > maxProd)
                maxProd = prod;
            if (firstNegIdx >= 0)
                si = firstNegIdx;
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