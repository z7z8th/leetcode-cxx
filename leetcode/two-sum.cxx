/*
1. Two Sum
Easy

Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].

Accepted
1,914,081
Submissions
4,321,067
 */

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for (auto i = nums.begin(); i != nums.end(); i++) {
            for (auto j = i+1; j != nums.end(); j++) {
                if (*i + *j == target)
                    return { i - nums.begin(), j - nums.begin() };
            }
        }
        return {};
    }
};