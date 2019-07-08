/*
33. Search in Rotated Sorted Array
Medium

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.

Your algorithm's runtime complexity must be in the order of O(log n).

Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1

*/

class Solution {
public:
    vector<int>::iterator findPivot(vector<int>& nums) {
        if (nums.size() == 0)
            return nums.end();
        int pivot_val = nums[0];
        for (auto it = nums.begin(); it != nums.end(); it++) {
            if (pivot_val > *it)
                return it;
            else
                pivot_val = *it;
        }
        return nums.end();
    }
    int search(vector<int>& nums, int target) {
        auto pivot_idx = findPivot(nums);
        //return pivot_idx;
        auto ret = lower_bound(pivot_idx, nums.end(), target);
        if (ret == nums.end())
            ret = lower_bound(nums.begin(), pivot_idx, target);
        if (ret == nums.end() || *ret != target)
            return -1;
        return ret - nums.begin();
    }
};