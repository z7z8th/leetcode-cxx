/* 279. Perfect Squares
Medium

Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.

Example 1:

Input: n = 12
Output: 3 
Explanation: 12 = 4 + 4 + 4.

Example 2:

Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.

Accepted
199,871
Submissions
467,548
 */

#include <bits/stdc++.h>

using namespace std;
/* 
class Solution {
public:
    int numSquaresEx(int n, int maxSq) {
		if (dp[n])
			return dp[n];
        int cnt = n/(maxSq*maxSq);
        if (!cnt)
            return numSquaresEx(n, maxSq-1);
		int minSqCnt = INT_MAX;
        for (int i=cnt; i>=0; i--) {
			//cout << "n " << n << ", maxSq " << maxSq << "^2 * i " << i << endl;
            int remain = n-i*(maxSq*maxSq);
            if (remain == 0) {
                //return i;
				if (i<minSqCnt) {
					minSqCnt = i;
					//cout << n << " <= " << maxSq << "^2 * " << i << endl;
				}
				break;
			}
			//cout << "remain " << remain << endl;
            int ret = numSquaresEx(remain, maxSq-1);
            if (ret > 0) {
				if (ret == 1)
					return dp[n] = ret+i;
				//ret += i;
				if (ret+i < minSqCnt) {
					minSqCnt = ret+i;
					//cout << n << " <= " << maxSq << "^2 * " << i << endl;
				}

				//break;
			}
        }
		if (minSqCnt != INT_MAX)
			dp[n] = minSqCnt;

        return (minSqCnt == INT_MAX ? -1 : minSqCnt);
    }
    int numSquares(int n) {
        int maxSq = sqrt(n);
		dp.clear();
		dp.resize(n+1, 0);
        return numSquaresEx(n, maxSq);
    }
	vector<int> dp;
};
 */

class Solution {
public:
	int numSquares(int n) {
        int maxSq = sqrt(n);
		vector<int> dp(n+1);
		dp[0] = 0;
		dp[1] = 1;
        for (int i=1; i<=n; i++) {
			dp[i] = INT_MAX;
			int prevSq = 0;
			for (int s=1; s<=maxSq; s++) {
				int sq = prevSq + 2*s - 1;
				if (sq > i) break;
				dp[i] = min(dp[i], dp[i-sq]+1);
				prevSq = sq;
			}
		}
		return dp[n];
    };
};


int main() {
	pair<int, int> tcs[] {
		{ 12, 3 },
		{ 13, 2 },
		{ 20, 2 },
		{ 30, 3 },
		{ 80, 2 },
		{ 90, 2 },
		{ 500, 2 },
		{ 1000, 2 },
		{ 5000, 2 },
		{ 10000, 1 },
		{ 100000, 2 },
		{ 123456, 3 },
	};

	for (auto& tc : tcs) {
		cout << "case " << tc.first << endl;
		cout << "expect " << tc.second << endl;
		Solution sln;
		auto ret = sln.numSquares(tc.first);
		cout << "return " << ret << " " << (ret != tc.second ? "** WRONG **" : "OK") << endl;
		cout << endl;
	}
}

/* 
// 0ms sample solution from leetcode.
class Solution {
public:
    bool dfs(int n, int d)
    {
        if(d==0) return !n;
       // int sqr = sqrt(n);
        for(int i=sqrt(n);i>=1;i--)
        {
            int sq = i * i;
            if(sq * d < n) break;
            if(dfs(n-sq,d-1)) return true;
        }
        return false;
    }
    int numSquares(int n) {
        for(int d=1; ;d++)
        {
            if(dfs(n,d))
                return d;
        }
    }
}; */