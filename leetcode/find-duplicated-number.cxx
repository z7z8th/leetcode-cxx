/* 287. Find the Duplicate Number
Medium

Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.

Example 1:

Input: [1,3,4,2,2]
Output: 2

Example 2:

Input: [3,1,3,4,2]
Output: 3

Note:

    You must not modify the array (assume the array is read only).
    You must use only constant, O(1) extra space.
    Your runtime complexity should be less than O(n2).
    There is only one duplicate number in the array, but it could be repeated more than once.

Accepted
198,908
Submissions
397,040
 */

#include <bits/stdc++.h>

using namespace std;

/* Only brute force and linked list cycle didn't modify array*/
/*
Possible solution:
1. brute force, time O(n^2), space O(1)
2. sort, time O(nlogn), space O(1)
3. set, time O(n), space O(n)
4. linked list cycle detection, time O(n),space O(1)
 */
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        for (int i=0; i<nums.size(); i++) {
            for (int j=i+1; j<nums.size(); j++) {
                if (nums[i] == nums[j])
                    return nums[i];
            }
        }
        return nums[0];
    }
};

