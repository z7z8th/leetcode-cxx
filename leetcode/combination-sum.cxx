/* 39. Combination Sum
Medium

Given a set of candidate numbers (candidates) (without duplicates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.

The same repeated number may be chosen from candidates unlimited number of times.

Note:

    All numbers (including target) will be positive integers.
    The solution set must not contain duplicate combinations.

Example 1:

Input: candidates = [2,3,6,7], target = 7,
A solution set is:
[
  [7],
  [2,2,3]
]

Example 2:

Input: candidates = [2,3,5], target = 8,
A solution set is:
[
  [2,2,2,2],
  [2,3,3],
  [3,5]
]

Accepted
366,051
Submissions
738,596 */


#include <bits/stdc++.h>

using namespace std;


void printMatrix(vector<vector<int>>& nums) {
	for (int i=0; i<nums.size(); i++) {
		for (int j=0; j<nums[i].size(); j++) {
			cout << nums[i][j] << ", ";
		}
		cout << endl;
	}
}


class Solution {
public:
	void combBT(vector<int>& cand, int si, int target, vector<int>& oneComb) {
        if (target == 0)
			return;
		for (int i=si; i<cand.size(); i++) {
			int cval = cand[i];
			if (cval > target)
				return;
			if (cval == target) {
				oneComb.push_back(cval);
				combs.push_back(oneComb);
				oneComb.pop_back();
				return;
			} else {
				oneComb.push_back(cval);
				combBT(cand, i, target-cval, oneComb);
				oneComb.pop_back();
			}
		}
    }
	
    vector<vector<int>> combinationSum(vector<int>& cand, int target) {
        sort(cand.begin(), cand.end());
		combs.clear();
		vector<int> oneComb;
		combBT(cand, 0, target, oneComb);
		return std::move(combs);
    }
	vector<vector<int>> combs;
};

int main() {
	tuple<vector<int>, int> tcs[] {
		{{2,3,6,7}, 7},
		{{2,3,5}, 8},
		{{}, 0},
		{{}, 1},
	};

	int tcIdx = 0;
	for (auto tc : tcs) {
		cout << "case " << tcIdx++ << endl;
		Solution sln;
		auto ret = sln.combinationSum(get<0>(tc), get<1>(tc));
		printMatrix(ret);
	}
}