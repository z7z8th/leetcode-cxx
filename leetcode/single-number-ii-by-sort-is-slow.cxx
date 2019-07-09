/* 137. Single Number II
Medium

Given a non-empty array of integers, every element appears three times except for one, which appears exactly once. Find that single one.

Note:

Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

Example 1:

Input: [2,2,3,2]
Output: 3

Example 2:

Input: [0,1,0,1,0,1,99]
Output: 99

Accepted
170,928
Submissions
368,905
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int prev = ~nums[0];
        int cnt = 3;
        for (int i=0; i<nums.size(); i++) {
			cout << i << ", " << nums[i] << endl;
            if (nums[i] == prev)
                cnt++;
            else if (cnt != 3) {
                return prev;
            } else {
                cnt = 1;
                prev = nums[i];
            }
        }
        
        return prev;
    }
};

int main() {
	tuple<vector<int>, int> tcs[] {
		{{2,2,3,2}, 3},
		{{0,1,0,1,0,1,99}, 99},
		{{-2,-2,1,1,-3,1,-3,-3,-4,-2}, -4},
	};
	int tcIdx = 0;
	for (auto tc : tcs) {
		Solution sln;
		cout << "case " << tcIdx++ << endl;
		int ret = sln.singleNumber(get<0>(tc));
		cout << "answer " << get<1>(tc) << " return " << ret << " "
			 << (ret == get<1>(tc) ? "PASS" : "*** FAIL ***") << endl;
		cout << endl;
	}
}