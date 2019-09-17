/* Momenta2019秋招技术岗笔试题
企业提供原题
00:00:24
28/37
[编程题]怪数

时间限制：1秒

空间限制：65536K

小M突然对怪数产生了兴趣。假设一个数n，如果[n/1]+[n/2]+...+[n/k](k为趋近于正无穷的正整数)为一个偶数，那么这个数是一个怪数，现在给定一个区间[a,b]，求[a,b]之间有多少怪数。

[x]表示不大于x的最大整数。

输入描述:

输入只包含一行，有两个非负整数a,b(0<=a,b<=2^31,a<=b)。


输出描述:

输出区间[a,b]中的怪数的个数。


输入例子1:

0 10


输出例子1:

6

 */
#include <bits/stdc++.h>
#include <math.h>

using namespace std;

#define MY_DRAFT 0
#define SINGLE_N_TEST 0
#define EVEN_ONLY_TEST 0
#define PRINT_RESULT 0

#if MY_DRAFT
double weird_num_float(unsigned n) {
	double y = 0.57721566490153286060651209;
	double ret = 0;
	if (n)
		ret = log(n) + y;
	ret = ret * n;
#if PRINT_RESULT
	cout << "sum float " << ret << endl;
#endif
	return ret;
}
#endif

inline bool isOdd(unsigned n) {
	return (n & 0x1);
}

inline bool isEven(unsigned n) {
	return !(n & 0x1);
}

/* return even 0 or odd 1 as result */
unsigned weird_num_trick(unsigned n) {
	unsigned sqrtn = sqrt(n);
	return sqrtn & 0x1U;
}
/* NOTE: this ncalc function isn't faster than weird_num_sqrt
   hardware multiply is very fast!!!
*/
unsigned weird_num_ncalc(unsigned n) {
	if (n == 0)
		return 0;
	unsigned sum = 0;
	unsigned sqrtn = sqrt(n);

	unsigned prev_x = n;
	//sum += n;
	
	for (unsigned i=1; i<=sqrtn; i++) {
		unsigned x = n/i;
		cout << (isOdd(x) ? 1 : 0) << " ";
		if (isOdd(x))
			sum += 1;
		if (isOdd(i - 1) && isOdd(prev_x - x)) {
			sum += 1;
		}
		prev_x = x;
	}
	cout << "sqrtn " << (isOdd(sqrtn) ? 1 : 0) << " ";
	unsigned sqrt_remain = n / sqrtn;
	for (unsigned i = sqrtn+1; i<=sqrt_remain; i++) {
		unsigned x = n/i;
		if (isOdd(x))
			sum += 1;
	}
	//cout << endl;
#if PRINT_RESULT
	cout << "sqrt_remain - sqrtn = " << sqrt_remain - sqrtn << endl;
	cout << "sum sqrt " << sum << endl;
#endif
	return sum;
}

unsigned weird_num_sqrt(unsigned n) {
	if (n == 0)
		return 0;
	unsigned sum = 0;
	unsigned sqrtn = sqrt(n);

	unsigned prev_x = n;
	//sum += n;
	
	for (unsigned i=1; i<=sqrtn; i++) {
		unsigned x = n/i;
		//cout << x << " ";
		sum += x;
		sum += (i - 1) * (prev_x - x);
		prev_x = x;
	}
	unsigned sqrt_remain = n / sqrtn;
	for (unsigned i = sqrtn+1; i<=sqrt_remain; i++) {
		unsigned x = n/i;
		sum += x;
	}
	//cout << endl;
#if PRINT_RESULT
	cout << "sqrt_remain - sqrtn = " << sqrt_remain - sqrtn << endl;
	cout << "sum sqrt " << sum << endl;
#endif
	return sum;
}

#if MY_DRAFT
unsigned weird_num_half(unsigned n) {
	unsigned sum = 0;
	for (unsigned i=1; i<=n/2;/*  i++ */) {
		unsigned x = n/i;
		//cout << x << " ";
		sum += x;
		unsigned ni = n/x;
		if (ni != i) {
			sum += x*(ni-i);
			//cout << x << "*" << ni << " ";
			i = ni+1;
		} else {
			i++;
		}
		//if (x < 2000)
		//	break;
	}
	//cout << endl;
	sum += (n+1)/2;
#if PRINT_RESULT
	cout << "sum half " << sum << endl;
#endif
	return sum;
}

unsigned weird_num_brute_force(unsigned n) {
	unsigned sum = 0;
	for (unsigned i=1; i<=n/2; i++) {
		unsigned x = n/i;
		//cout << x << " ";
		sum += x;
	}
	//cout << endl;
	sum += (n+1)/2;
#if PRINT_RESULT
	cout << "sum brtf " << sum << endl;
#endif
	return sum;
}
#endif

unsigned weird_num_cnt_sqrt(unsigned a, unsigned b) {
			unsigned cnt = 0;
		for (unsigned i=a; i<=b; i++) {
			auto ret = weird_num_sqrt(i);
			if (!(ret & 0x1)) {
				++cnt;
			}
			//cout << "i " << i << " cnt " << cnt << endl;
		}
		//cout << cnt << endl;
		return cnt;
}

unsigned weird_num_cnt_trick(unsigned a, unsigned b) {
		unsigned cnt = 0;
		for (unsigned i=a; i<=b; i++) {
			auto ret = weird_num_trick(i);
			if (isEven(ret)) {
				++cnt;
			}
			//cout << "i " << i << " cnt " << cnt << endl;
		}
		//cout << cnt << endl;
		return cnt;
}

unsigned weird_num_cnt_trick_v2(unsigned a, unsigned b) {
		unsigned cnt = 0;
		unsigned sqrta = sqrt(a);
		unsigned sqrtb = sqrt(b);

		unsigned prev2 = a;
		for (unsigned i=sqrta+1; i<=sqrtb; i++) {
			unsigned w = weird_num_trick(prev2);
			unsigned i2 = i*i;
			if (isEven(w)) {
				cnt += (i2 - prev2);
			}
			prev2 = i2;
		}
		unsigned w = weird_num_trick(prev2);
		if (isEven(w)) {
			cnt += (b-prev2+1);
		}
		//cout << cnt << endl;
		return cnt;
}


int main() {
#if MY_DRAFT
#if SINGLE_N_TEST
	unsigned n;
	//cin >> n;
	tuple<unsigned, unsigned> tcs[] {
		{ 0, 0},
		{ 1, 1},
		{ 2, 3},
		{ 3, 5},
		{ 4, 8},
		{ 5, 10},
		{ 6, 14},
		{ 7, 16},
		{ 8, 20},
		{ 9, 23},
		{ 10, 27},
		{ 11, 29},
		{ 12, 35},
		{ 100, 482},
		{ 1000, 7069},
		{ 10000, 93668},
		{ 100000, 1166750},
		{ 1000000, 13970034},
		{ 1<<31, 3526155458},  // overflow
	};
	for (auto &tc : tcs) {
		n = get<0>(tc);
		cout << "case " << n << " : " << endl;
		auto ans = get<1>(tc);
		//auto ret_float = weird_num_float(n);
		auto ret_half = weird_num_half(n);
		auto ret_sqrt = weird_num_sqrt(n);
		//cout << "diff " << ret_float - ret_half << endl;
		cout << "return " << (ret_half != ret_sqrt ? "** WRONG **" : "OK") << endl << endl;
	}
	return 0;
#elif EVEN_ONLY_TEST
	unsigned n;
	//cin >> n;
	tuple<unsigned, unsigned> tcs[] {
		{ 0, 0},
		{ 1, 1},
		{ 2, 3},
		{ 3, 5},
		{ 4, 8},
		{ 5, 10},
		{ 6, 14},
		{ 7, 16},
		{ 8, 20},
		{ 9, 23},
		{ 10, 27},
		{ 11, 29},
		{ 12, 35},
		{ 100, 482},
		{ 1000, 7069},
		{ 10000, 93668},
		{ 100000, 1166750},
		{ 1000000, 13970034},
		{ 1<<31, 3526155458},  // overflow
	};
	for (auto &tc : tcs) {
		n = get<0>(tc);
		cout << "case " << n << " : " << endl;
		//auto ans = get<1>(tc);
		auto ret_sqrt = weird_num_sqrt(n);
		auto ret_ncalc = weird_num_ncalc(n);
		cout << "return " << (isEven(ret_ncalc) != isEven(ret_sqrt) ? "** WRONG **" : "OK") << endl << endl;
	}
	cout << "scan test:" << endl;
	unsigned prev_i = 0;
	for (unsigned i=10000; i < 1U<<31; i++) {
		n = i;
		if ((n>>20) != prev_i) {
			cout << "case " << n << " : " << endl;
			prev_i = n>>20;
		}
		//auto ans = get<1>(tc);
		auto ret_sqrt = weird_num_sqrt(n);
		auto ret_ncalc = weird_num_ncalc(n);
		if (isEven(ret_ncalc) != isEven(ret_sqrt)) {
			cout << "ncalc for " << i << "** WRONG **" << endl;
		}
	}
	return 0;
#else
	tuple<unsigned, unsigned, unsigned> tcs2[] {
		{ 0, 0, 1 },
		{ 0, 1, 1 },
		{ 0, 2, 1 },
		{ 0, 3, 1 },
		{ 0, 4, 2 },
		{ 0, 5, 3 },
		{ 0, 6, 4 },
		{ 0, 7, 5 },
		{ 0, 8, 6 },
		{ 0, 9, 6 },
		{ 0, 10, 6 },
		{ 0, 11, 6 },
		{ 0, 12, 6 },
		{ 0, 100, 46 },
		{ 0, 1000, 496 },
		{ 0, 10000, 4951 },
		{ 0, 100000, 49915 },
		{ 0, 1000000, 499501 },
		{ 100, 1048576, 523732 },
		{ 55,  1048600, 523773 },
		{ 0, 10000000, 4999298 },  // 1000w, trick: 0.08s sqrt: 1m27s, half: 7m25s
		{ 0, 100000000, 49995001 }, // 1y, trick: 0.7s
		{ 0, 1<<31, 1073762679 },     // 20y, overflow, trick: 14s, trick v2: 0.007s
	};
	for (auto &tc : tcs2) {
		unsigned a = get<0>(tc);
		unsigned b = get<1>(tc);
		//auto ans = get<2>(tc);
		//auto cnt = weird_num_cnt_trick(a, b);
		auto cnt = weird_num_cnt_trick_v2(a, b);
		cout << "case " << a << ", " << b << ": cnt " << cnt << endl;
	}
#endif
#else
	unsigned a, b;
	while(cin >> a >> b) {
		auto cnt = weird_num_cnt_trick_v2(a, b);
		cout << cnt << endl;
	}
#endif
}

#if 0
!! repeat pattern !!

~/src/cxx ⑂master* $ ./objs/2019.Autumn-weird-num 
1 100
1 sqrtn 1 i 1 cnt 0
0 sqrtn 1 i 2 cnt 0
1 sqrtn 1 i 3 cnt 0
0 0 sqrtn 0 i 4 cnt 1
1 0 sqrtn 0 i 5 cnt 2
0 1 sqrtn 0 i 6 cnt 3
1 1 sqrtn 0 i 7 cnt 4
0 0 sqrtn 0 i 8 cnt 5
1 0 1 sqrtn 1 i 9 cnt 5
0 1 1 sqrtn 1 i 10 cnt 5
1 1 1 sqrtn 1 i 11 cnt 5
0 0 0 sqrtn 1 i 12 cnt 5
1 0 0 sqrtn 1 i 13 cnt 5
0 1 0 sqrtn 1 i 14 cnt 5
1 1 1 sqrtn 1 i 15 cnt 5
0 0 1 0 sqrtn 0 i 16 cnt 6
1 0 1 0 sqrtn 0 i 17 cnt 7
0 1 0 0 sqrtn 0 i 18 cnt 8
1 1 0 0 sqrtn 0 i 19 cnt 9
0 0 0 1 sqrtn 0 i 20 cnt 10
1 0 1 1 sqrtn 0 i 21 cnt 11
0 1 1 1 sqrtn 0 i 22 cnt 12
1 1 1 1 sqrtn 0 i 23 cnt 13
0 0 0 0 sqrtn 0 i 24 cnt 14
1 0 0 0 1 sqrtn 1 i 25 cnt 14
0 1 0 0 1 sqrtn 1 i 26 cnt 14
1 1 1 0 1 sqrtn 1 i 27 cnt 14
0 0 1 1 1 sqrtn 1 i 28 cnt 14
1 0 1 1 1 sqrtn 1 i 29 cnt 14
0 1 0 1 0 sqrtn 1 i 30 cnt 14
1 1 0 1 0 sqrtn 1 i 31 cnt 14
0 0 0 0 0 sqrtn 1 i 32 cnt 14
1 0 1 0 0 sqrtn 1 i 33 cnt 14
0 1 1 0 0 sqrtn 1 i 34 cnt 14
1 1 1 0 1 sqrtn 1 i 35 cnt 14
0 0 0 1 1 0 sqrtn 0 i 36 cnt 15
1 0 0 1 1 0 sqrtn 0 i 37 cnt 16
0 1 0 1 1 0 sqrtn 0 i 38 cnt 17
1 1 1 1 1 0 sqrtn 0 i 39 cnt 18
0 0 1 0 0 0 sqrtn 0 i 40 cnt 19
1 0 1 0 0 0 sqrtn 0 i 41 cnt 20
0 1 0 0 0 1 sqrtn 0 i 42 cnt 21
1 1 0 0 0 1 sqrtn 0 i 43 cnt 22
0 0 0 1 0 1 sqrtn 0 i 44 cnt 23
1 0 1 1 1 1 sqrtn 0 i 45 cnt 24
0 1 1 1 1 1 sqrtn 0 i 46 cnt 25
1 1 1 1 1 1 sqrtn 0 i 47 cnt 26
0 0 0 0 1 0 sqrtn 0 i 48 cnt 27
1 0 0 0 1 0 1 sqrtn 1 i 49 cnt 27
0 1 0 0 0 0 1 sqrtn 1 i 50 cnt 27
1 1 1 0 0 0 1 sqrtn 1 i 51 cnt 27
0 0 1 1 0 0 1 sqrtn 1 i 52 cnt 27
1 0 1 1 0 0 1 sqrtn 1 i 53 cnt 27
0 1 0 1 0 1 1 sqrtn 1 i 54 cnt 27
1 1 0 1 1 1 1 sqrtn 1 i 55 cnt 27
0 0 0 0 1 1 0 sqrtn 1 i 56 cnt 27
1 0 1 0 1 1 0 sqrtn 1 i 57 cnt 27
0 1 1 0 1 1 0 sqrtn 1 i 58 cnt 27
1 1 1 0 1 1 0 sqrtn 1 i 59 cnt 27
0 0 0 1 0 0 0 sqrtn 1 i 60 cnt 27
1 0 0 1 0 0 0 sqrtn 1 i 61 cnt 27
0 1 0 1 0 0 0 sqrtn 1 i 62 cnt 27
1 1 1 1 0 0 1 sqrtn 1 i 63 cnt 27
0 0 1 0 0 0 1 0 sqrtn 0 i 64 cnt 28
1 0 1 0 1 0 1 0 sqrtn 0 i 65 cnt 29
0 1 0 0 1 1 1 0 sqrtn 0 i 66 cnt 30
1 1 0 0 1 1 1 0 sqrtn 0 i 67 cnt 31
0 0 0 1 1 1 1 0 sqrtn 0 i 68 cnt 32
1 0 1 1 1 1 1 0 sqrtn 0 i 69 cnt 33
0 1 1 1 0 1 0 0 sqrtn 0 i 70 cnt 34
1 1 1 1 0 1 0 0 sqrtn 0 i 71 cnt 35
0 0 0 0 0 0 0 1 sqrtn 0 i 72 cnt 36
1 0 0 0 0 0 0 1 sqrtn 0 i 73 cnt 37
0 1 0 0 0 0 0 1 sqrtn 0 i 74 cnt 38
1 1 1 0 1 0 0 1 sqrtn 0 i 75 cnt 39
0 0 1 1 1 0 0 1 sqrtn 0 i 76 cnt 40
1 0 1 1 1 0 1 1 sqrtn 0 i 77 cnt 41
0 1 0 1 1 1 1 1 sqrtn 0 i 78 cnt 42
1 1 0 1 1 1 1 1 sqrtn 0 i 79 cnt 43
0 0 0 0 0 1 1 0 sqrtn 0 i 80 cnt 44
1 0 1 0 0 1 1 0 1 sqrtn 1 i 81 cnt 44
0 1 1 0 0 1 1 0 1 sqrtn 1 i 82 cnt 44
1 1 1 0 0 1 1 0 1 sqrtn 1 i 83 cnt 44
0 0 0 1 0 0 0 0 1 sqrtn 1 i 84 cnt 44
1 0 0 1 1 0 0 0 1 sqrtn 1 i 85 cnt 44
0 1 0 1 1 0 0 0 1 sqrtn 1 i 86 cnt 44
1 1 1 1 1 0 0 0 1 sqrtn 1 i 87 cnt 44
0 0 1 0 1 0 0 1 1 sqrtn 1 i 88 cnt 44
1 0 1 0 1 0 0 1 1 sqrtn 1 i 89 cnt 44
0 1 0 0 0 1 0 1 0 sqrtn 1 i 90 cnt 44
1 1 0 0 0 1 1 1 0 sqrtn 1 i 91 cnt 44
0 0 0 1 0 1 1 1 0 sqrtn 1 i 92 cnt 44
1 0 1 1 0 1 1 1 0 sqrtn 1 i 93 cnt 44
0 1 1 1 0 1 1 1 0 sqrtn 1 i 94 cnt 44
1 1 1 1 1 1 1 1 0 sqrtn 1 i 95 cnt 44
0 0 0 0 1 0 1 0 0 sqrtn 1 i 96 cnt 44
1 0 0 0 1 0 1 0 0 sqrtn 1 i 97 cnt 44
0 1 0 0 1 0 0 0 0 sqrtn 1 i 98 cnt 44
1 1 1 0 1 0 0 0 1 sqrtn 1 i 99 cnt 44
0 0 1 1 0 0 0 0 1 0 sqrtn 0 i 100 cnt 45
45

#endif