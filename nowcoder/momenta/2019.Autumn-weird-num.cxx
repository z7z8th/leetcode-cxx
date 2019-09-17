
#include <bits/stdc++.h>
#include <math.h>

using namespace std;

#define MY_DRAFT 0
#define SINGLE_N_TEST 0
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
#endif
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
		{ 0, 10000000, 4999298 },  // 1000w, sqrt: 1m27s, half 7m25s
		//{ 0, 100000000, 0 }, // 1y
		//{ 0, 1<<31, 0 },     // 20y, overflow
	};
	for (auto &tc : tcs2) {
		unsigned a = get<0>(tc);
		unsigned b = get<1>(tc);
		//auto ans = get<2>(tc);
		unsigned cnt = 0;
		for (unsigned i=a; i<=b; i++) {
			auto ret = weird_num_sqrt(i);
			//auto ret = weird_num_half(i);
			if (!(ret & 0x1)) {
				++cnt;
			}
		}
		cout << "case " << a << ", " << b << ": cnt " << cnt << endl;
	}
#else
	unsigned a, b;
	while(cin >> a >> b) {
		unsigned cnt = 0;
		for (unsigned i=a; i<=b; i++) {
			auto ret = weird_num_sqrt(i);
			if (!(ret & 0x1)) {
				++cnt;
			}
		}
		cout << cnt << endl;
	}
#endif
}