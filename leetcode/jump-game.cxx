/* 55. Jump Game
Medium

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

Example 1:

Input: [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:

Input: [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum
             jump length is 0, which makes it impossible to reach the last index.

Accepted
309,587
Submissions
948,950

Topics: Array, Greedy
 */

#include <bits/stdc++.h>

using namespace std;

static auto fast=[]()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

class Solution {
public:
    bool canJump(vector<int>& nums) {
        if (nums.size() <= 1)
            return true;
        int update = 0;
        int to = 0 + nums[0];
        while (update <= to && update < nums.size()) {
            int reach = nums[update] + update;
            if (reach > to)
                to = reach;
            if (to >= nums.size() - 1)
                return true;
            ++update;
        }
        //cout << "to " << to <<endl;
        return false;
    }
};