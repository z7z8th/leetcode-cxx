/* Momenta2019秋招技术岗笔试题
企业提供原题
00:40:48
29/37
[编程题]大家来扫雷
时间限制：1秒
空间限制：131072K

小M最近爱上了扫雷游戏，就是在一个n*m的区域中，有地雷，每一个方格上都有一个数字s，表示在这个方格周围有s颗雷，现在给你一张表明地雷的图，并且指定一个位置点开，请输出点开后的数字情况，若点开的地方的数字为0，则向该方格周围扩展，直到遇到数字或者地图边界为止，若点开的地方为地雷,那么直接输出"GG"。
周围指的是上，左上，左，左下，下，右下，右，右上八个方向。

输入描述:
第一行有两个数字n和m(2<=n,m<=1000)，表示地图的大小，第二行有两个整数x和y(1<=x<=n,1<=y<=m)，表示点击第x行y列的方格，接下来的是一个n行m列的一个矩阵，表示地图，其中.表示空地，*表示地雷。

输出描述:
如果点开的地方为地雷直接输出"GG"。否则输出点击指定位置后的地图，"."表示未点开的空地，"*"表示地雷，数字表示在该方格周围的地雷数目。


输入例子1:
3 4
1 1
....
..*.
....

输出例子1:
01..
01*.
01..
*/

#include <bits/stdc++.h>

using namespace std;

void printMatrix(vector<vector<char>> &m) {
	for (auto &row : m) {
		for (auto &n : row) {
			cout << n;
		}
		cout << endl;
	}
	//cout << endl;
}

//template <typename T>
class Solution {
public:
	bool isIndexValid(vector<vector<char>> &m, int ridx, int cidx) {
		if (ridx < 0 || ridx >= m.size())
			return false;
		if (cidx < 0 || cidx >= m[0].size())
			return false;
		return true;
	}
	bool isMine(vector<vector<char>> &m, int ridx, int cidx) {
		if (!isIndexValid(m, ridx, cidx))
			return false;
		return m[ridx][cidx] == '*';
	}
	bool visited(vector<vector<char>> &m, int ridx, int cidx) {
		auto &p = m[ridx][cidx];
		return '0' <= p && p <='8';
	}
	int countMines(vector<vector<char>> &m, int ridx, int cidx) {
		int cnt = 0;
		for (auto &dir : dirs) {
			if (isMine(m, ridx+dir[0], cidx+dir[1]))
				cnt++;
		}
		return cnt;
	}
	void expandMap(vector<vector<char>> &m, int ridx, int cidx) {
		if (!isIndexValid(m, ridx, cidx))
			return;
		if (visited(m, ridx, cidx))
			return;
		int cnt = countMines(m, ridx, cidx);
		//cout << ridx << ", " << "cidx " << cnt << endl;
		m[ridx][cidx] = '0' + cnt;
		if (cnt)
			return;
		for (auto &dir : dirs) {
			expandMap(m, ridx+dir[0], cidx+dir[1]);
		}
	}

	void mineSweeping(vector<vector<char>> &m, int ridx, int cidx) {
		if (isMine(m, ridx, cidx)) {
			cout << "GG" << endl;
			return;
		}
		expandMap(m, ridx, cidx);
		printMatrix(m);
	}
	static int dirs[8][2];
};

int Solution::dirs[8][2] = {
	{-1, -1 },
	{ 0, -1 },
	{ 1, -1 },
	{ 1,  0 },
	{ 1,  1 },
	{ 0,  1 },
	{-1,  1 },
	{-1,  0 },
};

int main() {
	int rows;
	int cols;
	int x;
	int y;
	while (cin >> rows >> cols) {
		cin >> x >> y;
		--x;
		--y;
#warning change char to int to improve perf if mem enough
		vector<vector<char>> m;
		m.resize(rows);
		for (auto &row : m) {
			row.resize(cols);
			for (auto &n : row) {
				cin >> n;
			}
		}
		Solution sln;
		sln.mineSweeping(m, x, y);
	}

}