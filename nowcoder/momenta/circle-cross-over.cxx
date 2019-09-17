/* Momenta2019秋招技术岗笔试题
企业提供原题
01:39:22
26/37
[编程题]交叉线
时间限制：1秒
空间限制：65536K

大M布置给小M一个题目：首先给出n个在横坐标上的点，然后连续的用半圆连接他们：首先连接第一个点与第二点(以第一个点和第二点作为半圆的直径)。然后连接第二个第三个点，直到第n个点。现在需要判定这些半圆是否相交了，在端点处相交不算半圆相交。如下图所示。

输入描述:
输入的第一行包含一个整数T (1 ≤ T ≤ 10)表示有T组样例。
每组样例的第一行是一个整数n (1≤n≤1000)。
接下来的一行输入有n个用空格隔开的不同的整数a1,a2,...,an (-1000000 ≤ ai ≤ 1000000)，(ai,0)表示第i个点在横坐标的位置。

输出描述:
对于每个输入文件，输出T行。
每行输出"y"表示这些半圆有相交或者"n"。

输入例子1:
2
4
0 10 5 15
4
0 15 5 10

输出例子1:
y
n
*/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
	void swap(int &a, int &b) {
		int c = a;
		a = b;
		b = c;
	}
	void ensureAscOrder(int &a, int &b) {
		if (a > b)
			swap(a, b);
	}
/* 	bool inRangeExclude(int cl, int cr, int i) {
		if (cl < i && i < cr)
			return true;
		if (cl > i && i > cr)
			return true;
		return false;
	} */
	bool twoCrossOver(int c1l, int c1r, int c2l, int c2r) {
		ensureAscOrder(c1l, c1r);
		ensureAscOrder(c2l, c2r);
		if (c1l < c2l) {
			return c2l < c1r && c1r < c2r;
		} else if (c1l == c2l) {
			return false;
		} else {
			return c1l < c2r && c2r < c1r;
		}
	}
	bool circlesCrossOver(vector<int> &cv) {
		for (int i=1; i<cv.size(); i++) {
			for (int si=1; si<i; si++) {
				if (twoCrossOver(cv[si-1], cv[si], cv[i-1], cv[i])) {
					//cout << "overlap! c1 " << cv[si-1] << ", " << cv[si] << " c2 " << cv[i-1] << ", " << cv[i] << endl;
					return true;
				}
			}
		}
		return false;
	}
};

void printVector(vector<int> &vec) {
	cout << "len " << vec.size() << endl;
	for (auto &val : vec) {
		cout << val << " ";
	}
	cout << endl;
}

int main() {
	int case_cnt;
	while (cin >> case_cnt) {
		vector<char> result;
		//result.resize(case_cnt);
		for (int i=0; i<case_cnt; i++) {
			int cv_cnt;
			cin >> cv_cnt;
			vector<int> cv;
			cv.resize(cv_cnt);
			for (auto &p : cv)
				cin >> p;
			//printVector(cv);
			Solution sln;
			bool ret = sln.circlesCrossOver(cv);
			result.push_back(ret ? 'y' : 'n');
		}
		for (auto &r : result) {
			cout << r << endl;
		}
	}
}