/* 213. House Robber II
Medium

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed. All houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

Example 1:

Input: [2,3,2]
Output: 3
Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2),
             because they are adjacent houses.

Example 2:

Input: [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
             Total amount you can rob = 1 + 3 = 4.

Accepted
122,950
Submissions
346,875 */

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int robEx(vector<int>& nums, size_t si, int leftRobbed, int firstRobbed) {
		if (dp[firstRobbed*2 + leftRobbed][si] >= 0)
			return dp[firstRobbed*2 + leftRobbed][si];
		if (si >= nums.size()) {
			if (leftRobbed && firstRobbed)
				return -min(nums.back(), nums.front());
			return 0;
			//return dp[leftRobbed][si] = 0;
		}
        if (leftRobbed) {
            return dp[firstRobbed*2 + leftRobbed][si] = robEx(nums, si+1, 0, firstRobbed);
        } else {
            // rob si
            int val1 = nums[si] + robEx(nums, si+1, 1, si == 0 ? 1 : firstRobbed);
            // not rob si
            int val2 = robEx(nums, si+1, 0, si == 0 ? 0 : firstRobbed);
            if (val1 > val2 && si == 0)
				firstRobbed = 1;
			return dp[firstRobbed*2 + leftRobbed][si] = max(val1, val2);
        }
    }
    int rob(vector<int>& nums) {
		if (nums.size() == 1)
			return nums.back();
		dp.clear();
		dp.resize(4);
		for (size_t i=0; i<dp.size(); i++) {
			dp[i].clear();
			dp[i].resize(nums.size()+1, -1);
		}

        int val1 = robEx(nums, 0, 0, 0);
        return val1;
    }
	vector<vector<int>> dp;
};

int main() {
	tuple<vector<int>, int> tcs[] {
		//{{2,3,2}, 3},
		//{{1,2,3,1}, 4},
		{{1,2,1,1}, 3},
		{{2,7,9,3,1}, 11},
		{{1,1,2,7,9,3,1,9,2,100,99,17,200,2,1}, 321},
		{{
			104,209,137,52,158,67,213,86,141,110,151,127,238,147,169,138,240,185,246,225,147,203,83,83,131,227,54,78,165,180,214,151,111,161,233,147,124,143
		 },
		 3157
		},
		{{1}, 1},
		{{}, 0},
	};
	int tcIdx;
	for (auto tc : tcs) {
		cout << "case " << tcIdx++ << " : ";
		Solution sln;
		int ret = sln.rob(get<0>(tc));
		cout << "ret " << ret << " " << (ret != get<1>(tc) ? "** WRONG **" : "OK") << endl;
		cout << endl;
	}
}

/*
Sample 0ms solution from leetcode:
One pass dp.

class Solution {
public:
    int rob(vector<int>& nums) {
        
        int len = nums.size();
        if(len==0)
            return 0;
        
        vector<int> dp(len,0);
        if(len == 1)
            return nums[0];
        dp[0] = nums[0];
        dp[1] = max(nums[0],nums[1]);
        for(int i = 2;i<len;i++)
        {
            dp[i] = max(nums[i]+dp[i-2],dp[i-1]);
        }
        
        return dp.back();
    }
};
 */