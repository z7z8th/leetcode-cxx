/* 198. House Robber
Easy

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

Example 1:

Input: [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
             Total amount you can rob = 1 + 3 = 4.

Example 2:

Input: [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
             Total amount you can rob = 2 + 9 + 1 = 12.

Accepted
344,428
Submissions
836,232 */

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int robEx(vector<int>& nums, size_t si, int leftRobbed) {
		if (dp[leftRobbed][si] >= 0)
			return dp[leftRobbed][si];
		if (si >= nums.size()) {
			return dp[leftRobbed][si] = 0;
		}
        if (leftRobbed) {
            return dp[leftRobbed][si] = robEx(nums, si+1, 0);
        } else {
            // rob si
            int val1 = nums[si] + robEx(nums, si+1, 1);
            // not rob si
            int val2 = robEx(nums, si+1, 0);
            return dp[leftRobbed][si] = max(val1, val2);
        }
    }
    int rob(vector<int>& nums) {
		dp.clear();
		dp.resize(2);
		for (size_t i=0; i<dp.size(); i++) {
			dp[i].clear();
			dp[i].resize(nums.size()+1, -1);
		}

        int val1 = robEx(nums, 0, 0);
        return val1;
    }
	vector<vector<int>> dp;
};

int main() {
	tuple<vector<int>, int> tcs[] {
		{{1,2,3,1}, 4},
		{{2,7,9,3,1}, 12},
		{{1,1,2,7,9,3,1,9,2,100,99,17,200,2,1}, 322},
		{{
			104,209,137,52,158,67,213,86,141,110,151,127,238,147,169,138,240,185,246,225,147,203,83,83,131,227,54,78,165,180,214,151,111,161,233,147,124,143
		 },
		 3176
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