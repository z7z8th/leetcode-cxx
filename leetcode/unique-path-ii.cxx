/* 63. Unique Paths II
Medium

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

Note: m and n will be at most 100.

Example 1:

Input:
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
Output: 2
Explanation:
There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right

Accepted
212,878
Submissions
633,793 */

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
	Solution()
	{
	}
	void clearDP() {
		dp.clear();
		dp.resize(gridSizeX+1);
		for (size_t i=0; i<dp.size(); i++) {
			dp[i].clear();
			dp[i].resize(gridSizeY+1, -1);
		}
	}

	void initMinClear(vector<vector<int>>& grid) {
		minClearXm = gridSizeX;
		for (int i=gridSizeX-1; i>=0; i--) {
			if (grid.back()[i] > 0) {
				minClearXm = gridSizeX - 1 - i;
				break;
			}
		}

		minClearYn = gridSizeY;
		for (int i=gridSizeY-1; i>=0; i--) {
			if (grid[i].back() > 0) {
				minClearYn = gridSizeY - 1 - i;
				break;
			}
		}
	}
	bool isFinalPathClear(vector<vector<int>>& grid, int xm, int yn) {
		if (yn == 1)
			return xm <= minClearXm;
		if (xm == 1)
			return yn <= minClearYn;
		// wont reach here
		// warning
		cout << "*** WARN: should not reach here" << endl;
		return false;
	}
	bool isPosObstacle(vector<vector<int>>& grid, int xm, int yn) {
		return grid[gridSizeY-yn][gridSizeX-xm] > 0;
	}
    int64_t initMatrixStep(vector<vector<int>>& grid, int xm, int yn) {
		if (dp[xm][yn] >= 0)
			return dp[xm][yn];
		
		if (grid[gridSizeY-yn][gridSizeX-xm] > 0)
			return dp[xm][yn] = 0;

		if (xm == 1 || yn == 1) {
			return dp[xm][yn] = (isFinalPathClear(grid, xm, yn) ? 1 : 0);
		}

		int64_t step = 0;
		for (int i=xm; i>0; i--) {
			if (isPosObstacle(grid, i, yn))
				break;
			step += initMatrixStep(grid, i, yn-1);
		}
		return dp[xm][yn] = step;
    }

    int64_t uniquePathsWithObstacles(vector<vector<int>>& grid) {
		int m = grid[0].size();
		int n = grid.size();
		gridSizeX = m;
		gridSizeY = n;

		initMinClear(grid);
		clearDP();

		if (dp[m][n] < 0) {
			initMatrixStep(grid, m, n);
		}
		return dp[m][n];
    }

	static const int MAX_DEPTH  = 101;
protected:
    vector<vector<int64_t>> dp;
	int minClearXm = INT_MAX;
	int minClearYn = INT_MAX;
	int gridSizeX;
	int gridSizeY;
};

void printMatrix(vector<vector<int>>& nums) {
	for (size_t i=0; i<nums.size(); i++) {
		for (size_t j=0; j<nums[i].size(); j++) {
			cout << nums[i][j] << ", ";
		}
		cout << endl;
	}
}

int main() {
	tuple<vector<vector<int>>, int> tcs[] {
		{{{0, 0}}, 1},
		{{{0, 0}, {0, 0}}, 2},
		{{{0, 1}, {0, 0}}, 1},
		{{{0, 0}, {1, 0}}, 1},
		{{{0, 1}, {1, 0}}, 0},
		{{{0,0,0},{0,1,0},{0,0,0}}, 2},
		{
			{
				{0,0,0,0},
				{0,1,0,0},
				{0,0,0,0},
				{0,0,0,0}
			},
			8
		},
	};
	int tcIdx = 0;
	for (auto tc : tcs) {
		Solution sln;
		cout << "case " << tcIdx++ << ": ";
		auto& grid = get<0>(tc);
		int steps = get<1>(tc);
		cout << "size " << grid[0].size() << " x " << grid.size() << " steps " << steps << endl;
		printMatrix(grid);
		int ret = sln.uniquePathsWithObstacles(grid);
		cout << "ret " << ret << (ret != steps ? " ** WRONG **" : " OK") << endl;
		cout << endl;
	}
}