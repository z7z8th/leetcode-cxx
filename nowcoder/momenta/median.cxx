/*  Momenta2019秋招技术岗笔试题
企业提供原题
01:57:53
30/37
[编程题]中位数

时间限制：1秒
空间限制：65536K

小M给你一个长度为n的数组，我们定义median数为该数组从小到大排序后，下标为(n-1)/2的数字。下标从0开始，(n-1)/2表示整数除法，即向下取整。现在我们已经得到了一个初始的数组，我们希望这个数组的median数是一个给定数字x。所以我们需要加入一些数到数组中从而完成我们的目标。数组中的元素可以重复，请问，最少需要加入多少个数字才能达成这个目标。

输入描述:
第一行输入两个整数n x (1 <= n <= 500, 1 <= x <= 10^5)。
接下来一行有n个正整数表示初始的数组，用空格分开，范围是[1, 10^5]。

输出描述:
输出需要加入最少的元素个数才能够使得新数组的median数成为x。

输入例子1:
3 2
2 3 4

输出例子1:
1

例子说明1:
样例一中，加入1，得到1 2 3 4，那么median数的下标为(4 - 1)/2 = 1, median数为2。加一个数字就可以了。

输入例子2:
3 4
1 2 3

输出例子2:
4

例子说明2:
样例二中，加入4 5 6 7，得到1 2 3 4 5 6 7，median数为4。最少加4个数字。

*/

#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
	int becomeMedian(vector<int> &vec, int x)
	{
		sort(vec.begin(), vec.end());
		auto median = vec[(vec.size()-1)/2];
		if (median == x)
			return 0;
		auto itl = lower_bound(vec.begin(), vec.end(), x);
		auto distbl = distance(vec.begin(), itl);
		auto ith = itl;
		while (ith != vec.end() && *ith == x)
			ith++;

		int ret = -1;
		auto disthe = distance(ith, vec.end());
		if (distbl < disthe) {
			auto distbh = distance(vec.begin(), ith);
			ret = disthe - distbh;
		} else if (distbl >= disthe) {
			auto distle = distance(itl, vec.end());
			ret = distbl - distle + 1;
		}
		return ret;
	}
};

int main()
{
	int n;
	int x;

	while (cin >> n >> x) {
		vector<int> vec(n);
		for (int i = 0; i < n; i++) {
			cin >> vec[i];
		}
		Solution sln;
		int ret = sln.becomeMedian(vec, x);
		cout << ret << endl;
	};
}


# if 0
3 2
2 3 4
1

3 1
2 3 4
3

3 4
1 2 3
4

3 3
1 2 3
2

3 2
1 2 3
0

10 3
1 1 2 2 3 3 4 4 5 5

14 3
1 1 1 1 2 2 2 2 2 3 3 3 3 3
5

14 1
1 1 1 2 2 2 3 4 5 6 7 8 9 10
8

# data of test case not sorted in nowcoder
10 229
109 80 520 390 542 572 342 605 208 65

#endif
