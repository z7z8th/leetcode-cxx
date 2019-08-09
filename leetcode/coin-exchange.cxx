/* 322. Coin Change
Medium

You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:

Input: coins = [1, 2, 5], amount = 11
Output: 3 
Explanation: 11 = 5 + 5 + 1

Example 2:

Input: coins = [2], amount = 3
Output: -1

Note:
You may assume that you have an infinite number of each kind of coin.
Accepted
222,874
Submissions
711,897 */

#include <bits/stdc++.h>

using namespace std;

template<typename Type>
void printVector(vector<Type> vec) {
	cout << "[ ";
	for (size_t i=0; i<vec.size(); i++) {
		auto& val = vec[i];
		cout << val;
		if (i != vec.size()-1)
			cout << ", ";
	}
	cout << " ]" << endl;
}

class Solution {
public:
    int coinChangeEx(vector<int>& coins, int amount) {
		if (dp[amount])
			return dp[amount];
		int minCount = INT_MAX;
        for (auto it=coins.rbegin(); it!=coins.rend(); it++) {
			int cnt = 0;
			if (*it == amount)
				return 1;
			if (*it < amount) {
				cnt = coinChangeEx(coins, amount-*it);
				if (cnt > 0) {
					cnt += 1;
					//return cnt;
					if (cnt < minCount)
						minCount = cnt;
				}
			}
		}
		return dp[amount] = (minCount == INT_MAX ? -1 : minCount);
    }
	int coinChange(vector<int>& coins, int amount) {
		if (amount == 0)
			return 0;
		dp.clear();
		dp.resize(amount+1, 0);
		sort(coins.begin(), coins.end());
		//printVector(coins);
		return coinChangeEx(coins, amount);
	}
	vector<int>	dp;
};


int main() {
	tuple<vector<int>, int, int> tcs[] {
		{ {1}, 0, 0},
		{ {1, 2, 5}, 11, 3},
		{ {2}, 3, -1},
		{ {2, 4, 5}, 8, 2},
		{ {3, 5, 7}, 9, 3},
		{ {186,419,83,408}, 6249, 20},
		{ {3,7,405,436}, 8839, 25 },
		{ {1, 2, 5}, 10000, 0},
		//{ {}, , },
	};
	int tcIdx = 0;
	for (auto tc : tcs) {
		cout << "case " << tcIdx++ << endl;
		auto& coins = get<0>(tc);
		printVector(coins);
		cout << "exchang for " << get<1>(tc) << endl;
		cout << "expect " << get<2>(tc) << endl;
		Solution sln;
		auto ret = sln.coinChange(coins, get<1>(tc));
		cout << "return " << ret << " " << (ret != get<2>(tc) ? "** WRONG **" : "OK") << endl;
		cout << endl;
	}
}
