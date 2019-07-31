/* 62. Unique Paths
Medium

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?


Above is a 7 x 3 grid. How many possible unique paths are there?

Note: m and n will be at most 100.

Example 1:

Input: m = 3, n = 2
Output: 3
Explanation:
From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Right -> Down
2. Right -> Down -> Right
3. Down -> Right -> Right

Example 2:

Input: m = 7, n = 3
Output: 28

Accepted
310,241
Submissions
640,779 */

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
	Solution()
	{
		if (dp.size() > 0)
			return;
		dp.resize(MAX_DEPTH);
		for (size_t i=0; i<dp.size(); i++) {
			dp[i].resize(MAX_DEPTH, 0);
		}
		//initMatrixStep(MAX_DEPTH-1, MAX_DEPTH-1);
	}
    int64_t initMatrixStep(int xm, int yn) {
		if (xm == 1 || yn == 1)
			return dp[yn][xm] = dp[xm][yn] = 1;
		if (dp[xm][yn] > 0 || dp[yn][xm] > 0)
			return dp[xm][yn];
		int64_t step = 0;
		for (int i=xm; i>0; i--)
			step += initMatrixStep(i, yn-1);
		return dp[yn][xm] = dp[xm][yn] = step;
    }
    int64_t uniquePaths(int m, int n) {
		if (dp[m][n] == 0 || dp[n][m] == 0) {
			initMatrixStep(m, n);
		}
		return dp[m][n];
    }

	static const int MAX_DEPTH;
protected:
    static vector<vector<int64_t>> dp;
};
const int Solution::MAX_DEPTH = 101;
vector<vector<int64_t>> Solution::dp;

int main() {


	tuple<pair<int, int>, int> tcs[] {
		{{1, 2}, 1},
		{{3, 2}, 3},
		{{7, 3}, 28},
		{{10, 10}, 48620},
 		{{20, 20}, 985525432},  // 985525432
/*		{{30, 30}, },
		{{40, 40}, },
		{{50, 50}, },
		{{60, 60}, },
		{{70, 70}, },
		{{80, 80}, },
		{{90, 90}, },
		{{100, 100}, }, */
		{{100, 1}, 1},
		{{1, 100}, 1},
		{{1, 1}, 1},
		{{0, 0}, 1},
	};
	int tcIdx = 0;
	for (auto tc : tcs) {
		Solution sln;
		cout << "case " << tcIdx++ << ": ";
		int m = get<0>(tc).first;
		int n = get<0>(tc).second;
		int steps = get<1>(tc);
		cout << "size " << m << " x " << n << " steps " << steps << endl;
		int ret = sln.uniquePaths(m, n);
		cout << "ret " << ret << (ret != steps ? " ** WRONG **" : " OK") << endl;
	}
}