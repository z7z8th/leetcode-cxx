/* Momenta2019秋招技术岗笔试题
企业提供原题
00:08:36
33/37
[编程题]交换查询

时间限制：1秒
空间限制：131072K

小M有一个N*M的方格，行列下标均从0开始。其中有K个方格中有数字，表示为(X, Y)方格中有数字C。对方格有2种操作，交换方格的两行或者交换方格的两列。

小M希望随时能够知道在经过一系列交换之后某一方格中是否含有数字，并且如果有的话，数字是多少。

输入描述:
输入数据第一行包含3个整数N, M, K。表示N行M列的方格，并且其中K个方格有数字。
(1 <= N, M <= 10^5, 0 <= K <= 10^5)
接下来K行，每行有3个整数，X, Y, C,表示（X，Y）方格中有数字C。
(0 <= X <= N - 1, 0 <= Y <= M - 1, 1 <= C <= 1000)
接下来有一个整数T，表示有T次操作或询问。(0 <= T <= 10^5)
接下来T行，买行有三个整数Q, A, B。
当Q == 0时，交换行A和行B所有方格。
当Q == 1时，交换列A和列B所有方格。
当Q == 2时，询问(A, B)是否有数字，如果有则输出该数字，如果没有输出－1。
数据保证Q，A，B均在合法的范围之内。

输出描述:
对于每个询问，输出一个整数表示其答案。

输入例子1:
3 3 2
1 1 1
2 2 2
5
2 1 1
0 0 1
1 0 1
2 1 1
2 2 2

输出例子1:
1
-1
2

例子说明1:
首先有3x3的方格，其中（1，1）有数字1，（2，2）有数字2，即：
-1 -1 -1
-1  1 -1
-1 -1  2
5次操作，
第一次查询（1，1）得到1；
第二次交换行1和行2，即：
-1  1 -1
-1 -1 -1
-1 -1  2
第三次交换列1和列2，即：
 1 -1 -1
-1 -1 -1
-1 -1  2
第四次查询（1，1）得到-1；
第五次查询（2，2）得到2；
*/

#include <bits/stdc++.h>

using namespace std;

void swap(int &a, int &b) {
	int c = a;
	a = b;
	b = c;
}

class SparseMatrix_Tune_for_Swap_Row_Col
{
public:
	SparseMatrix_Tune_for_Swap_Row_Col(int rows, int cols) {
		for (int i=0; i<rows; i++) {
			rowMap.push_back(i);
		}
		for (int j=0; j<cols; j++) {
			colMap.push_back(j);
		}
	}
	void insert(int i, int j, int val) {
		m[make_pair(i, j)] = val;
	}
	void swapRow(int ia, int ib) {
		swap(rowMap[ia], rowMap[ib]);
	}
	void swapColum(int ja, int jb) {
		swap(colMap[ja], colMap[jb]);
	}

	int query(int i, int j) {
		auto it = m.find(make_pair(rowMap[i], colMap[j]));
		return (it != m.end()) ? it->second : -1;
	}
	map<pair<int, int>, int> m;
	vector<int> rowMap;
	vector<int> colMap;
};


#warning SparseMatrix_LM is tested, too much search when swap colums.
class SparseMatrix_LM
{
public:
	void insert(int i, int j, int val) {
		if (i >= static_cast<int>(m.size()))
			m.resize(i+1);
		m[i][j] = val;
	}
	void swapRow(int ia, int ib) {
		m[ia].swap(m[ib]);
	}
	void swapColum(int ja, int jb) {
		//ensureOrder(ja, jb);
		for (auto &row : m) {
			auto ita = row.find(ja);
			auto itb = row.find(jb);
			if (ita != row.end() && itb != row.end()) {
				swap(ita->second, itb->second);
			} else if (ita != row.end()) {
				row[jb] = ita->second;
				row.erase(ita);
			} else if (itb != row.end()) {
				row[ja] = itb->second;
				row.erase(itb);
			}
		}
	}

	int query(int i, int j) {
		auto &row = m[i];
		auto it = row.find(j);
		int val = (it != row.end()) ? it->second : -1;
		return val;
	}

	// vector<unordered_map<int, int>> m; // 3m29s for n = m = k = t = 10^5
	vector<map<int, int>> m;  // 1m42s for n = m = k = t = 10^5
};

#warning SparseMatrix_LIL is tested, but two slow when swap colums, since too much binary search.

void ensureOrder(int &a, int &b) {
	if (a > b)
		swap(a, b);
}

struct lil_elem {
	int col;
	int val;
	bool operator<(const lil_elem &b) {
		return col < b.col;
	}
};

class SparseMatrix_LIL
{
public:
	void insert(int i, int j, int val) {
		if (i >= static_cast<int>(m.size()))
			m.resize(i+1);
		lil_elem ne { j, val };
		auto& row = m[i];
		auto comp = [](const lil_elem &a, const lil_elem &b) {
				return a.col < b.col;
		};
		auto itj = lower_bound(row.begin(), row.end(), ne, comp);
		//cout << "insert [ " << i << ", " << j << " ] = " << val
		//	 << ", itj " << &*itj << " end " << &*row.end() << endl;
		row.insert(itj, ne);
	}
	void swapRow(int ia, int ib) {
		m[ia].swap(m[ib]);
	}
	void swapColumInRow(vector<lil_elem> &row, int ja, int jb) {
		auto ita = lower_bound(row.begin(), row.end(), lil_elem{ja, 0});
		auto itb = lower_bound(ita, row.end(), lil_elem{jb, 0});
		auto afound = ita != row.end() && ita->col == ja;
		auto bfound = itb != row.end() && itb->col == jb;

		if (afound && bfound) {
			swap(ita->val, itb->val);
		} else if (!afound && bfound) {
			itb->col = ja;
			auto tmp = *itb;
			while (itb > ita) {
				*itb = *(itb-1);
				--itb;
			}
			*ita = tmp;
		} else if (afound && !bfound) {
			ita->col = jb;
			auto tmp = *ita;
			while (ita + 1 < itb) {
				*ita = *(ita+1);
				++ita;
			}
			*ita = tmp;
		} else {
			/* do nothing */
		}
	}
	void swapColum(int ja, int jb) {
		ensureOrder(ja, jb);
		for (auto &row : m) {
			swapColumInRow(row, ja, jb);
		}
	}

	int query(int i, int j) {
		auto &row = m[i];
		auto it = lower_bound(row.begin(), row.end(), lil_elem{j, 0});
		int val = (it != row.end() && it->col == j) ? it->val : -1;
		return val;
	}

	vector<vector<lil_elem>> m;  // 1m12s for n = m = k = t = 10^5
};

#if 0
#warning SparseMatrix_CSR is not tested
/* Compressed Sparse Row, Yale format */
class SparseMatrix_CSR
{
public:
	SparseMatrix_CSR(SparseMatrix_LIL &m)
	{
		int prevRowIdx = 0;
		for (auto &row : m.getLIL()) {
			IA.emplace_back(prevRowIdx);
			for (auto &elem : row) {
				A.emplace_back(elem.val);
				JA.emplace_back(elem.col);
			}
			prevRowIdx += row.size();
		}
		IA.emplace_back(prevRowIdx);
	}

	vector<int> A;
	vector<int> IA;
	vector<int> JA;
};
#endif


int main() {
	int n;
	int m;
	int k;
	while (cin >> n >> m >> k) {
		//cout << "n " << n << " m " << m << " k " << k << endl;
		//SparseMatrix_LM mtrx;
		SparseMatrix_Tune_for_Swap_Row_Col mtrx(n, m);
		for (int ki=0; ki<k; ki++) {
			int x;
			int y;
			int c;
			cin >> x >> y >> c;
			/* if (x < 0 || x >= n) {
				cout << "x " << x << " out of range " << endl;
			}
			if (y < 0 || y >= m) {
				cout << "y " << y << " out of range " << endl;
			} */
			mtrx.insert(x, y, c);
		}
		//return 0;
		int t;
		cin >> t;
		//cout << "t " << t << endl;
		for (int ti=0; ti<t; ti++) {
			int q;
			int a;
			int b;
			cin >> q >> a >> b;
			/* if (a < 0 || a >= n) {
				cout << "a " << a << " out of range " << endl;
			}
			if (b < 0 || b >= m) {
				cout << "b " << b << " out of range " << endl;
			} */
			switch (q) {
			case 0:
				mtrx.swapRow(a, b);
				break;
			case 1:
				mtrx.swapColum(a, b);
				break;
			case 2:
				cout << mtrx.query(a, b) << endl;
				break;
			default:
				cout << "unknown query" << endl;
			}
		}
	};
}

#if 0
use `swap-query-gen-case.py 100000 100000 100000 100000` to generate the largest case.

Fail at case 10%: 
### orignal nowcoder case
sed -r -e 's/([0-9]+\s+){3}/&\n/g' sq-t1.txt | sed -r -e 's/\s+$//g'  | ./swap-query | wc -l
用例:
10 10 20
3 2 908 6 9 849 8 5 654 5 0 318 8 8 709 5 9 400 7 3 641 4 8 855 0 4 383 9 7 61 1 7 716 2 9 290 5 7 256 8 0 161 3 7 181 0 8 447 9 9 372 0 9 131 7 2 516 2 5 939
1000
0 2 1 1 2 3 0 1 0 0 5 6 1 3 6 0 8 8 0 1 4 2 5 6 1 2 9 0 6 9 1 2 2 0 2 9 1 3 4 0 7 0 0 1 0 2 5 7 1 6 2 2 5 8 2 2 9 1 2 0 2 9 6 0 2 9 0 2 6 1 4 1 1 5 8 2 9 0 1 7 4 1 0 2 2 6 9 2 0 8 1 8 6 0 4 0 1 0 5 2 6 4 0 2 3 0 5 9 0 1 0 1 4 2 0 8 5 2 3 7 1 8 8 0 1 8 2 2 5 1 4 0 2 0 5 2 8 6 2 9 2 0 9 6 0 4 4 2 2 9 1 8 7 1 5 3 2 1 3 2 8 8 2 1 1 1 1 0 2 7 6 2 2 5 2 0 2 1 1 5 2 8 7 1 7 0 2 7 0 0 0 2 2 5 3 2 4 7 1 8 2 1 0 2 2 6 9 2 9 2 1 6 9 1 3 3 0 0 4 2 9 5 0 7 1 1 7 8 1 0 9 2 5 4 0 9 7 0 5 3 0 9 4 1 1 9 1 6 2 2 3 4 2 2 8 1 4 5 2 4 2 2 6 5 0 9 7 2 8 5 2 7 3 1 4 1 2 8 3 0 7 8 1 6 3 0 1 6 0 5 7 1 2 2 2 1 5 0 4 0 2 2 1 2 7 9 2 0 6 2 0 1 1 0 5 2 2 1 2 8 2 2 7 5 0 3 5 0 1 0 0 0 7 2 7 0 0 7 8 2 9 3 1 2 0 1 9 7 2 1 3 1 5 9 2 2 5 0 5 6 1 9 0 2 8 1 0 4 4 1 8 0 2 8 5 2 9 8 1 1 8 0 7 5 0 4 6 0 6 8 1 7 7 2 6 9 1 1 4 2 0 3 2 7 2 0 7 8 2 0 9 2 3 9 1 9 5 0 4 3 0 0 1 0 9 5 1 6 9 2 8 1 1 4 5 1 9 5 0 9 8 2 1 5 2 6 6 1 7 4 2 0 6 0 1 9 1 8 2 1 7 1 0 7 5 2 4 0 0 3 1 1 6 3 1 8 6 1 6 3 1 1 5 2 4 5 0 8 3 0 7 1 0 3 1 2 1 5 1 3 3 1 1 1 1 0 4 1 7 1 1 2 9 1 1 0 0 2 1 2 4 9 2 9 7 2 0 1 0 5 6 2 0 8 1 9 6 2 2 4 0 9 5 2 5 1 1 3 3 0 0 6 0 0 4 1 0 4 0 4 7 0 7 1 0 2 6 2 3 7 1 1 3 1 6 7 1 4 3 1 1 3 1 7 9 2 7 9 1 5 8 2 7 8 0 1 9 0 9 7 1 6 4 2 5 5 1 1 2 2 5 0 1 3 2 1 6 0 0 4 4 0 9 6 0 5 1 2 3 6 1 6 4 1 5 8 0 6 5 2 0 6 2 8 5 2 7 3 1 4 0 2 4 7 2 6 4 1 3 5 2 2 3 0 0 7 1 3 8 2 7 4 2 8 3 1 8 5 0 7 4 2 2 5 0 4 8 0 7 2 0 3 3 2 3 7 2 7 7 1 7 7 0 9 5 0 1 1 0 4 5 2 9 4 1 4 2 2 0 4 0 4 1 2 3 6 2 8 8 0 9 5 2 4 7 1 7 1 2 4 4 1 7 7 2 0 0 1 5 7 2 6 8 1 6 8 2 7 1 2 4 8 0 5 9 2 8 3 1 7 5 2 6 4 2 7 7 0 8 5 0 6 0 0 3 6 1 4 2 0 0 9 2 4 2 2 3 0 1 8 0 0 2 8 1 1 1 1 0 9 1 4 2 1 2 3 0 5 1 1 4 1 1 5 9 0 6 8 0 1 1 0 0 8 1 6 7 2 0 3 2 1 6 2 8 5 0 4 5 2 8 5 0 9 0 1 2 0 2 3 1 2 3 8 0 0 0 1 0 5 2 6 0 1 6 2 2 0 7 0 2 1 2 3 7 1 6 5 1 6 0 1 4 8 0 9 6 0 9 9 2 0 3 0 3 1 2 2 0 2 3 3 1 7 3 0 0 9 1 5 6 1 8 8 1 1 3 1 6 2 2 5 3 0 2 6 2 8 0 2 9 7 1 8 4 0 7 8 2 7 6 0 3 2 0 7 3 1 4 2 1 4 7 2 4 6 1 7 5 2 2 3 1 5 6 0 6 3 1 8 4 0 9 8 2 8 7 2 0 7 1 1 1 2 3 1 1 9 5 2 8 8 1 6 6 2 0 6 2 2 7 0 7 4 1 9 9 2 3 0 2 4 7 1 5 7 0 9 3 1 6 6 2 0 7 1 4 3 0 9 9 1 2 9 2 5 6 0 6 4 0 3 5 1 0 9 1 2 7 2 5 2 0 0 1 1 7 0 1 1 8 1 6 8 2 6 7 0 4 3 2 6 0 2 1 8 2 2 0 0 2 0 0 4 4 2 5 1 2 8 2 0 5 0 2 3 7 2 9 1 1 6 4 1 3 7 0 8 5 1 4 3 2 5 1 0 6 0 1 1 3 0 7 1 2 6 6 2 9 1 1 0 7 2 3 8 1 6 8 0 3 6 1 0 5 0 3 8 2 1 8 2 0 9 2 5 3 2 5 5 0 3 4 1 6 4 2 5 6 0 5 9 1 4 7 0 9 4 0 8 6 0 7 9 1 4 1 0 2 6 1 7 9 2 2 1 0 6 1 2 2 0 1 3 4 1 9 5 2 4 0 2 9 3 1 0 3 2 3 5 1 7 3 1 0 2 0 0 4 2 2 2 0 9 2 1 9 6 2 4 4 0 5 2 0 0 0 0 1 1 0 7 1 1 4 4 2 0 4 2 1 5 0 0 6 0 2 4 1 3 6 1 9 1 2 7 6 2 4 6 2 1 9 2 6 7 0 2 0 2 4 7 1 9 2 1 3 3 1 2 8 0 7 1 1 4 0 1 6 7 2 7 0 2 0 0 2 1 5 0 8 1 0 2 3 0 4 8 2 4 6 1 9 5 2 9 5 0 1 7 0 1 1 1 7 5 0 8 0 1 1 3 1 8 1 2 5 2 1 2 9 2 2 2 1 0 9 0 3 2 0 4 3 1 1 6 1 0 0 2 1 1 1 4 8 2 6 8 0 8 9 2 0 5 0 6 2 0 3 2 2 2 8 0 9 0 1 9 0 1 3 4 0 1 1 1 1 2 2 0 4 0 2 7 1 8 5 2 6 4 0 6 7 1 3 9 0 2 4 1 6 6 2 8 3 2 3 7 1 9 2 0 2 4 0 8 5 2 9 6 2 6 9 1 2 1 1 5 8 2 1 6 2 6 2 1 6 5 1 4 5 0 5 8 2 4 6 2 9 7 2 5 5 1 8 6 2 7 7 1 2 4 0 1 6 1 4 3 2 2 2 2 3 6 0 5 8 2 6 9 0 8 2 1 5 3 0 1 3 0 0 7 0 7 6 2 6 1 0 0 6 2 5 4 1 0 3 0 7 9 2 4 2 1 8 0 1 3 7 1 1 0 1 2 7 0 6 7 1 1 6 2 7 6 1 4 9 1 0 8 2 0 3 1 7 6 1 2 7 1 8 2 2 1 8 2 0 6 0 7 3 0 6 4 0 4 2 1 0 8 2 7 9 0 7 6 0 9 9 1 1 4 1 6 7 2 4 6 0 7 5 0 4 1 0 4 9 0 1 9 0 3 0 2 8 6 1 5 0 0 2 0 1 8 9 1 7 2 2 9 2 0 3 2 2 2 4 2 9 6 2 6 8 1 2 8 0 5 3 0 3 9 2 7 6 2 1 5 2 0 4 1 9 2 2 4 1 2 1 9 0 8 1 0 3 6 2 2 7 1 1 7 0 7 4 2 0 9 2 8 0 2 0 7 0 3 3 1 8 4 2 7 9 2 3 3 1 6 1 0 2 9 1 8 6 2 4 5 2 7 9 2 5 4 0 2 6 1 2 6 2 6 0 0 6 9 1 7 1 2 0 6 2 1 1 0 8 6 0 9 3 2 7 2 1 0 5 1 0 1 2 8 9 0 9 9 0 8 6 1 1 6 0 7 6 2 8 9 0 0 5 0 8 6 0 8 8 1 3 5 0 2 5 0 4 2 2 4 1 0 7 7 0 4 3 2 8 1 0 0 2 1 2 3 1 5 5 1 0 9 2 2 5 0 2 4 1 1 7 2 0 2 0 3 2 1 0 4 0 4 9 2 5 0 1 5 6 1 0 9 2 7 1 0 9 4 0 7 0 2 2 0 1 0 6 2 7 9 2 4 1 0 9 7 0 3 6 1 5 7 0 1 7 2 4 8 0 6 4 0 7 9 0 4 8 2 7 6 1 9 0 1 3 4 2 7 4 1 3 3 2 1 1 1 4 1 2 5 1 0 6 3 0 6 0 0 3 3 1 3 2 0 5 1 0 3 9 1 1 6 2 6 0 2 3 8 0 9 2 1 3 8 0 9 7 1 1 8 0 8 4 1 2 8 1 9 7 0 3 8 0 4 2 2 2 3 0 4 2 2 7 2 1 7 7 0 1 3 1 1 7 2 0 8 2 5 9 1 3 5 2 1 3 1 5 2 2 6 3 1 8 6 1 4 5 0 2 8 1 0 3 2 6 1 2 4 3 2 4 2 0 8 7 1 4 4 1 7 2 1 1 0 0 4 0 1 4 3 2 6 2 0 0 6 0 2 3 0 3 5 2 7 4 0 6 0 1 7 7 1 7 5 1 5 9 2 5 9 2 9 1 2 0 9 2 6 7 2 9 3 2 6 0 2 1 4 2 8 9 0 4 0 0 5 8 2 2 7 1 5 7 0 1 9 1 9 8 2 5 3 0 1 7 0 4 4 2 8 0 2 8 9 2 0 5 2 1 6 2 6 4 1 8 1 2 9 6 0 6 7 2 8 7 0 3 4 2 5 6 1 4 8 0 2 9 1 7 9 0 8 9 2 5 5 0 8 2 2 7 3 0 9 3 0 1 1 2 1 0 2 6 8 1 9 1 1 4 8 1 6 7 1 2 5 1 4 9 1 8 8 1 7 1 0 9 3 0 8 4 1 2 0 2 2 6 2 9 0 0 6 8 1 7 9 2 3 2 1 2 3 1 7 9 1 2 0 0 4 2 0 7 4 0 1 6 1 0 0 1 9 6 2 7 7 1 0 2 2 1 3 0 6 6 0 0 6 2 2 3 0 2 1 1 6 1 0 2 3 1 6 8 0 1 0 0 8 2 1 3 8 2 1 4 1 2 2 2 8 0 1 7 6 1 5 8 1 5 0 2 4 0 0 6 1 2 3 5 2 6 1 2 9 3 0 5 4 1 2 0 2 5 6 0 0 3 0 9 5 1 4 1 1 0 8 0 3 4 1 7 9 0 4 0 1 4 6 1 4 1 0 7 2 2 0 7 2 2 0 1 9 1 1 3 2 0 0 0 1 1 1 0 6 7 0 7 2 0 8 0 2 3 6 1 4 3 0 0 3 1 4 7 2 1 0 1 2 0 2 5 6 0 7 7 1 6 2 0 2 5 2 9 8 1 6 2 2 7 9 2 0 9 0 2 4 2 1 4 1 6 2 2 5 2 0 9 4 1 8 5 2 2 2 0 2 7 0 8 9 1 1 8 2 9 7 0 1 1 0 5 3 1 1 8 0 2 9 1 8 5 0 2 3 1 1 1 0 1 5 1 0 9 1 0 4 2 1 4 0 7 7 1 4 1 2 5 9 0 8 4 2 3 0 0 6 4 2 0 5 1 3 3 1 2 1 0 6 9 0 9 4 0 3 1 1 1 9 0 8 5 1 4 5 1 8 2 2 5 8 0 9 3 2 4 1 1 3 7 2 3 8 1 3 7 2 0 0 2 1 1 0 3 5 2 6 4 0 8 3 0 6 0 0 2 7 1 8 8 0 4 8 1 2 5 1 3 7 1 4 0 0 6 5 0 8 3 2 1 7 1 2 1 0 3 1 0 4 6 1 9 1 2 0 9 1 0 0 1 8 9 1 3 8 1 6 5 2 9 1 1 5 9 1 7 3 0 1 3 0 4 5 1 0 9 0 0 2 1 7 8 1 0 7 2 7 9 2 5 9 2 6 8 0 3 7 0 9 9 0 0 7 0 2 5 1 6 4 2 3 9 0 7 2 0 8 9 0 0 8 2 6 7 0 3 2 1 7 3 2 8 8 0 8 5 0 6 6 1 7 5 2 4 6 0 0 4 1 5 5 1 0 4 0 7 3 2 8 4 1 4 6 0 8 2 1 7 0 1 7 4 0 8 7 0 1 7 1 7 7 0 7 0 1 1 1 1 8 5 1 6 4 0 0 1 2 9 9 1 1 9 2 3 8 1 0 1 1 8 1 1 1 5 2 8 8 2 5 0 2 0 6 1 6 9 2 3 5 1 2 5 1 7 0 0 9 9 2 2 4 2 6 8 0 6 4 0 5 8 1 3 1 2 5 1 0 8 8 1 7 4 0 9 5 1 3 3 1 0 2 2 7 1 1 1 9 0 1 6 2 7 9 2 5 8 1 2 9 0 1 0 2 4 1 0 5 3 2 0 7 0 8 0 1 3 5 1 1 8 1 4 6 1 1 3 2 6 5 2 0 8 2 4 6 0 9 6 2 7 8 2 1 9 1 3 0 2 5 3 0 7 3 0 2 9 1 7 2 2 7 1 1 5 9 1 3 6 2 1 9 2 3 9 2 4 8 0 9 6 1 3 6
对应输出应该为:
echo 'x x x' | tr ' ' "\n"
-1 -1 -1 -1 -1 -1 -1 -1 716 -1 -1 -1 -1 -1 -1 318 -1 -1 939 -1 -1 131 290 161 -1 -1 -1 -1 709 709 -1 -1 -1 447 -1 -1 -1 516 -1 318 -1 516 -1 -1 -1 -1 400 -1 -1 -1 -1 -1 372 -1 -1 -1 -1 -1 -1 256 -1 -1 -1 -1 -1 -1 400 -1 -1 -1 516 641 372 -1 -1 -1 -1 -1 -1 -1 -1 383 290 -1 716 256 -1 855 -1 -1 61 -1 -1 -1 256 -1 131 -1 -1 -1 -1 -1 -1 -1 -1 855 -1 161 -1 -1 -1 131 -1 -1 -1 -1 -1 -1 -1 -1 161 -1 -1 -1 -1 131 -1 -1 -1 -1 716 -1 -1 939 -1 -1 -1 383 -1 -1 -1 516 -1 -1 -1 -1 -1 -1 318 -1 -1 -1 -1 -1 -1 -1 -1 131 939 -1 -1 -1 -1 -1 -1 -1 709 -1 -1 -1 131 -1 716 181 -1 -1 -1 -1 939 -1 372 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 849 -1 855 -1 -1 654 -1 -1 855 -1 849 -1 -1 -1 -1 447 -1 -1 -1 -1 400 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 654 -1 -1 -1 -1 -1 318 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 716 -1 -1 -1 -1 -1 -1 256 -1 -1 318 -1 939 -1 -1 -1 -1 641 -1 -1 -1 -1 -1 447 383 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 131 -1 -1 -1 -1 372 -1 -1 383 -1 -1 400 -1 -1 -1 -1 -1


用例:
100 90 100 5 7 582 20 81 852 96 14 585 76 21 248 25 44 319 72 15 611 11 46 991 57 35 956 97 74 277 48 31 206 62 71 467 34 76 604 18 51 462 62 83 77 6 31 556 50 19 308 2 17 531 23 62 642 69 20 28 47 82 306 58 85 264 44 73 487 88 66 737 26 68 306 41 28 257 60 42 496 98 10 107 66 8 700 78 81 712 63 80 353 56 66 966 12 20 220 68 62 539 76 88 701 27 17 507 5 77 864 2 15 613 37 71 221 72 7 899 44 13 764 0 28 549 26 9 876 81 0 220 53 11 534 88 22 262 90 42 614 85 81 370 76 68 752 77 64 967 21 17 533 63 51 145 56 26 133 66 89 451 64 6 539 82 55 150 93 35 320 22 68 816 84 42 325 10 34 886 17 50 494 88 39 604 67 70 604 44 22 816 83 76 190 45 82 270 16 33 511 53 4 411 85 40 792 36 77 515 50 67 442 12 17 511 7 7 413 57 21 513 47 86 831 60 46 801 49 17 42 98 46 921 9 18 390 24 30 293 80 65 443 61 44 443 49 77 9 6 84 7 52 8 166 54 65 740 15 79 358 82 25 241 97 38 425 20 41 750 76 74 344 85 49 591 13 12 721 93 14 312 57 44 423 10 22 993 61 30 352 12 26 506 33 71 178 93 87 384 24 78 582 10 1 85 24 2 97 60 0 16 55 1 82 61 1 39 82 0 8 12 0 74 62 0 24 91 2 67 9 0 50 10
对应输出应该为:
-1 -1
你的输出为:
-1 b 91 out of range -1
#endif
