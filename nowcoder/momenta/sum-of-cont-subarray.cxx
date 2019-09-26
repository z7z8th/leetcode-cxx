/* Momenta2019秋招技术岗笔试题
企业提供原题
00:07:51
32/37
[编程题]连续子区间和

时间限制：1秒
空间限制：131072K

小M给你一串含有c个正整数的数组, 想让你帮忙求出有多少个下标的连续区间, 它们的和大于等于x。

输入描述:
第一行两个整数c x（0 < c <= 1,000,000, 0 <= x <= 100,000,000)
第二行有c个正整数（每个正整数小于等于100)。

输出描述:
输出一个整数，表示所求的个数。

输入例子1:
3 6
2 4 7

输出例子1:
4

例子说明1:
对于有3个整数构成的数组而言，总共有6个下标连续的区间，他们的和分别为：
2 = 2
4 = 4
7 = 7
2 + 4 = 6
4 + 7 = 11
2 + 4 + 7 = 13

其中有4个和大于等于6，所以答案等于4。
*/

#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
	int sumOfContSubArrayCount(vector<int> &vec, int x)
	{
		vector<int> dp(vec.size());
		for (size_t i=0; i<vec.size(); i++) {
			int sum = 0;
			dp[i] = 0;
			for (int j = i; j>=0; j--) {
				sum += vec[j];
				if (sum >= x)
					++dp[i];
			}
			if (i>0)
				dp[i] += dp[i-1];
		}
		return dp.back();
	}
};

int main()
{
	int c;
	int x;
	while (cin >> c >> x) {
		vector<int> vec(c);
		for (int i=0; i<c; i++)
			cin >> vec[i];
		Solution sln;
		auto ret = sln.sumOfContSubArrayCount(vec, x);
		cout << ret << endl;
	}
}

#if 0
3 6
2 4 7

9 10
1 2 3 4 5 6 7 8 9 10

#endif