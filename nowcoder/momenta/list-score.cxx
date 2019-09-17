/* Momenta2019秋招技术岗笔试题
企业提供原题
00:13:56
27/37
[编程题]队列得分

时间限制：1秒
空间限制：65536K

小M和大M要通过选择元素组成队列进行得分pk。
目前存在队列 S1,S2,S3...Sn, 每个元素包括2个正整数属性 set 和 value.
从中选出任意 K 个元素 S[i1], S[i2] ... S[ik], 保证顺序不变即 i1 < i2 < i3< ... < ik, 组成新的队列 P1,P2,P3......Pk.
我们通过一个机制评价队列的好坏:
Base = P1.value + P2.value + ... Pk.value,
Bonus = 10*t; t为新队列中 Pi.set = P(i+1).set 的 i 个数.
最终得分 Score = Base - Bonus; 求 Score 的最大值 和 取最大值时新队列元素个数的最小值.

输入描述:
第一行包含一个数 N (0 < N <= 500)
接下来N行每一行两个数表示 S1,S2,...,Sn 的 set 和 value 值 (0 < set,value <= 20)

输出描述:
Score 的最大值 和 新队列元素个数的最小值

输入例子1:
5
1 10
1 5
2 4
3 9
4 8

输出例子1:

31 4

例子说明1:

选S1,S3,S4,S5

*/

#include <bits/stdc++.h>

using namespace std;

struct node {
	int set;
	int val;
};

struct lookAheadState {
	vector<int> cmp10Cnt {0, 0, 0};
	int gt10Sum = 0;
	int lt10Max = 0;
};

void printVector(vector<int> &vec) {
	for (auto &val : vec) {
		cout << val << " ";
	}
	cout << endl;
}
void printNodeList(vector<node> &nl) {
	for (auto &n : nl) {
		cout << n.set << " " << n.val << endl;
	}
	cout << endl;
}

class Solution {
public:
	void updateCmp10Cnt(node &n, lookAheadState &ls) {
		auto &cmp10Cnt = ls.cmp10Cnt;
		int val = n.val;
		if (val < 10) {
			++cmp10Cnt[0];
			if (val > ls.lt10Max)
				ls.lt10Max = val;
		} else if (val == 10) {
			++cmp10Cnt[1];
		} else {
			++cmp10Cnt[2];
			ls.gt10Sum += val;
		}
	}
	int sumCmp10Cnt(vector<int> &cmp10Cnt) {
		return cmp10Cnt[0] + cmp10Cnt[1] + cmp10Cnt[2];
	}
	void lookAhead(vector<node> &vec, int si, lookAheadState &ls) {
		auto &cmp10Cnt = ls.cmp10Cnt;
		cmp10Cnt[0] = cmp10Cnt[1] = cmp10Cnt[2] = 0;
		int set_s = vec[si].set;
		updateCmp10Cnt(vec[si], ls);
		for (int i=si+1; i<vec.size(); i++) {
			int set_i = vec[i].set;
			if (set_i == set_s)
				updateCmp10Cnt(vec[i], ls);
			else
				break;
		}
	}
	pair<int, int> listScore(vector<node> &vec) {
		int sum = 0;
		int cnt = 0;
		for (int i=0; i<vec.size(); /* i++ */) {
			lookAheadState ls;
			lookAhead(vec, i, ls);
			//cout << "look i " << i << ", cmp10Cnt ";
			//printVector(ls.cmp10Cnt);
			//cout << "lt10Max " << ls.lt10Max << endl;
			//cout << "gt10Sum " << ls.gt10Sum << endl;
			
			if (ls.cmp10Cnt[2]) {  // discard all <=10 nodes if > 10 exists
				sum += ls.gt10Sum;
				sum -= 10*(ls.cmp10Cnt[2]-1);
				cnt += ls.cmp10Cnt[2];
			} else if (ls.cmp10Cnt[1]) {  // discard all < 10 nodes if = 10 exists
				sum += 10;
				cnt += 1;
			} else {  // select the max < 10 node
				sum += ls.lt10Max;
				cnt += 1;
			}
			i += sumCmp10Cnt(ls.cmp10Cnt);
		}
		return {sum, cnt};
	}
};

int main() {
	int cnt;
	while (cin >> cnt) {
		vector<node> vec;
		vec.resize(cnt);
		for (auto &n : vec) {
			cin >> n.set >> n.val;
		}
		//printNodeList(vec);
		Solution sln;
		auto score = sln.listScore(vec);
		cout << score.first << " " << score.second << endl;
	};
}

#if 0
n
1 10
1 5
2 4
3 9
4 8

5 6
5 7
5 8
5 9
5 10
5 11
5 12
5 13

6 7
6 10


7 13
7 14

8 6
8 7

9 3
9 4
9 5
9 6

5 10
5 10
5 10

## aka ##

26
1 10
1 5
2 4
3 9
4 8
5 6
5 7
5 8
5 9
5 10
5 11
5 12
5 13
6 7
6 10
7 13
7 14
8 6
8 7
9 3
9 4
9 5
9 6
5 10
5 10
5 10

127 13

## aka ##

26
1 10
2 4
3 9
4 8
5 11
5 12
5 13
6 10
7 13
7 14
8 7
9 6
5 10

127 13

###
10
1 2
7 14
7 20
3 20
9 1
6 12
7 5
10 15
10 15
2 6

90 10

#endif