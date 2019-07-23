/* 40. Combination Sum II
Medium

Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.

Each number in candidates may only be used once in the combination.

Note:

    All numbers (including target) will be positive integers.
    The solution set must not contain duplicate combinations.

Example 1:

Input: candidates = [10,1,2,7,6,1,5], target = 8,
A solution set is:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]

Example 2:

Input: candidates = [2,5,2,1,2], target = 5,
A solution set is:
[
  [1,2,2],
  [5]
]

Accepted
234,219
Submissions
551,036 */


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
				combBT(cand, i+1, target-cval, oneComb);
				oneComb.pop_back();
			}
			while (i+1 < cand.size() && cand[i] == cand[i+1])
				i++;
		}
    }
	
    vector<vector<int>> combinationSum2(vector<int>& cand, int target) {
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
		{{10,1,2,7,6,1,5}, 8},
		{{2,5,2,1,2}, 5},
		{{1,2,2,2,2,2,3,4}, 9},
		{{}, 0},
		{{}, 1},
	};

	int tcIdx = 0;
	for (auto tc : tcs) {
		cout << "case " << tcIdx++ << endl;
		Solution sln;
		auto ret = sln.combinationSum2(get<0>(tc), get<1>(tc));
		printMatrix(ret);
	}
}