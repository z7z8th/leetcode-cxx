/* Momenta2019秋招技术岗笔试题
企业提供原题
00:07:25
31/37
[编程题]k倍多重正整数集合

时间限制：1秒
空间限制：131072K

k 倍多重正整数集合的定义是：在一个多重集合（元素可以重复）中，不存在一个正整数是另一个正整数的k倍。
现在小M有 n 个正整数，你可以选择其中一些数构成 k 倍多重正整数集合。请求出最多能选出多少数来构成它。

输入描述:
第一行有两个整数 n, k (1 <= n <= 10^5, 1 <= k <= 10^9)。
接下来一行有 n 个正整数 a1, a2, ..., an (1 <= ai <= 10^9)。

输出描述:
最多能选出多少数构成k倍多重正整数集合。

输入例子1:
6 2
2 3 6 5 4 10

输出例子1:
3

例子说明1:
第一个样例中，我们选择2，3，5即可满足要求，因为k == 2，不存在一个数是另一个数的两倍。

输入例子2:
2 2
2 2

输出例子2:
2

例子说明2:
第二个样例中，我们选择2，2即可满足要求，因为k == 2，2也不是2的两倍，注意多重集合元素可以重复。
*/

#include <bits/stdc++.h>

using namespace std;

enum {
	USED = 0x1,
	EXCLUDE = 0x2,
	NO_K_MULTI = 0x4,
};

struct elem {
	using value_type = struct elem;
	int cnt;
	unsigned flag;
	elem(int cnt2, unsigned flag2 = 0U) : cnt(cnt2), flag(flag2)
	{
	}
};

class Solution
{
public:
	map<int, elem> constructCntSet(vector<int> &vec, int k)
	{
		sort(vec.begin(), vec.end());
		map<int, elem> valmap;
		for (size_t i = 0; i < vec.size(); /* i++ */) {
			int cnt = 0;
			for (size_t j = i; j < vec.size(); j++) {
				if (vec[j] == vec[i])
					++cnt;
				else
					break;
			}
			valmap.emplace(vec[i], elem(cnt, 0U));
			i += cnt;
		}
		return valmap;
	}
	void maxKMultiSet_ex(map<int, elem> &valmap, map<int, elem>::iterator it, int k, int cnt)
	{
		for (/* auto it = valmap.begin() */; it != valmap.end(); it++) {
			if (it->second.flag & EXCLUDE)
				continue;
			it->second.flag |= USED;
			auto itk  = valmap.find(k * it->first);
			itk->second.flag |=  EXCLUDE;
			int ncnt = cnt+it->second.cnt;
			if (ncnt > maxCnt)
				maxCnt = ncnt;
			auto nit = it;
			maxKMultiSet_ex(valmap, ++nit, k, ncnt);
			itk->second.flag &=  ~EXCLUDE;
			it->second.flag &= ~USED;
		}
	}
	int maxKMultiSet(vector<int> &vec, int k)
	{
		maxCnt = 0;
		map<int, elem> valmap = std::move(constructCntSet(vec, k));
		if (k == 1)
			return valmap.size();
		maxKMultiSet_ex(valmap, valmap.begin(), k, 0);
		return maxCnt;
	}
	int maxCnt;
};

int main()
{
	int n;
	int k;
	while (cin >> n >> k) {
		vector<int> vec(n);
		for (int i = 0; i < n; i++)
			cin >> vec[i];
		Solution sln;
		auto ret = sln.maxKMultiSet(vec, k);
		cout << ret;
	}
}

#if 0
6 2
2 3 6 5 4 10
3

2 2
2 2
2

12 2
2 2 4 4 4 4 8 8 8 8 8 8
8

2 1
2 2
1
#endif