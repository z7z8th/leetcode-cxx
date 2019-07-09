/* 260. Single Number III
Medium

Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once.

Example:

Input:  [1,2,1,3,2,5]
Output: [3,5]

Note:

    The order of the result is not important. So in the above example, [5, 3] is also correct.
    Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?

Accepted
109,580
Submissions
190,914
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        unordered_map<int, int> map_;
        for (int i=0; i<nums.size(); i++) {
            int n = nums[i];
            if (map_.find(n) != map_.end()) {
                map_[n]++;
                if (map_[n] == 2)
                    map_.erase(n);
            } else {
                map_[n] = 1;
            }
        }
        auto it = map_.begin();
        it++;
        return { map_.begin()->first, it->first};
    }
};