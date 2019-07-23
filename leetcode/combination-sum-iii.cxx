/* 216. Combination Sum III
Medium

Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.

Note:

    All numbers will be positive integers.
    The solution set must not contain duplicate combinations.

Example 1:

Input: k = 3, n = 7
Output: [[1,2,4]]

Example 2:

Input: k = 3, n = 9
Output: [[1,2,6], [1,3,5], [2,3,4]]

Accepted
127,330
Submissions
244,012 */


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
	void combBT(vector<int>& comb, int k, int n, int si) {
		if (k == 0)
			return;
		for (int i=si; i<=9; i++) {
			if (i > n)
				return;
			if (i == n) {
				if ( k > 1) {
					return;
				} else {
					comb.push_back(i);
					vec_.push_back(comb);
					comb.pop_back();
					return;
				}
			}
			comb.push_back(i);
			combBT(comb, k-1, n-i, i+1);
			comb.pop_back();
		}
	}
    vector<vector<int>> combinationSum3(int k, int n) {
		vec_.clear();
		vector<int> comb;
		combBT(comb, k, n, 1);
        return std::move(vec_);
    }
	vector<vector<int>> vec_;
};

int main() {
	tuple<int, int> tcs[] {
		{3, 7},
		{3, 9},
		{4, 10},
		{3, 1},
		{3, 2},
		{9, 45},
		{0, 1},
		{0, 0},
		{1, 0},
		{1, 5},
		{100, 500},
	};

	int tcIdx = 0;
	for (auto tc : tcs) {
		cout << "case " << tcIdx++ << ": k " << get<0>(tc) << " n " << get<1>(tc) << endl;
		Solution sln;
		auto ret = sln.combinationSum3(get<0>(tc), get<1>(tc));
		printMatrix(ret);
	}
}
