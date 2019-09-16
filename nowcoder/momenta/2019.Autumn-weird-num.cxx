
#include <bits/stdc++.h>
#include <math.h>

using namespace std;

#define MY_DRAFT 1
#define SINGLE_N_TEST 1
#define PRINT_RESULT 1

double weird_num_float(unsigned n) {
	double y = 0.57721566490153286060651209;
	double ret = log(n) + y;
	ret = ret * n;
#if PRINT_RESULT
	cout << "sum fl " << ret << endl;
#endif
	return ret;
}

unsigned weird_num_v3(unsigned n) {
	unsigned sum = 0;
	unsigned sqrtn = sqrt(n);
	for (unsigned i=1; i<=n/2;/*  i++ */) {
		unsigned x = n/i;
		//cout << x << " ";
		sum += x;
		if (x < sqrtn) {
			unsigned ni = n/x;
			if (ni != i) {
				sum += x*(ni-i);
				//cout << x << "*" << ni << " ";
				i = ni+1;
			} else {
				i++;
			}
		} else {
			i++;
		}
		//if (x < 2000)
		//	break;
	}
	//cout << endl;
	sum += (n+1)/2;
#if PRINT_RESULT
	cout << "sum op " << sum << endl;
#endif
	return sum;
}

unsigned weird_num(unsigned n) {
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
	cout << "sum op " << sum << endl;
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
	cout << "sum bf " << sum << endl;
#endif
	return sum;
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
		auto ans = get<1>(tc);
		auto ret_f = weird_num_float(n);
		auto ret = weird_num(n);
		cout << "diff " << ret_f - ret << endl;
		cout << "case " << n << " " << (ret != ans ? "** WRONG **" : "OK") << endl << endl;
	}
	return 0;
#endif
	tuple<unsigned, unsigned, unsigned> tcs2[] {
		{ 0, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 2, 0 },
		{ 0, 3, 0 },
		{ 0, 4, 0 },
		{ 0, 5, 0 },
		{ 0, 6, 0 },
		{ 0, 7, 0 },
		{ 0, 8, 0 },
		{ 0, 9, 0 },
		{ 0, 10, 0 },
		{ 0, 11, 0 },
		{ 0, 12, 0 },
		{ 0, 100, 0 },
		{ 0, 1000, 0 },
		{ 0, 10000, 0 },
		{ 0, 100000, 0 },
		{ 0, 1000000, 0 },
		//{ 0, 1<<31, 0 },  // overflow
	};
	for (auto &tc : tcs2) {
		unsigned a = get<0>(tc);
		unsigned b = get<1>(tc);
		auto ans = get<2>(tc);
		unsigned cnt = 0;
		for (unsigned i=a; i<=b; i++) {
			auto ret = weird_num_v3(i);
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
			auto ret = weird_num_v3(i);
			if (!(ret & 0x1)) {
				++cnt;
			}
		}
		cout << cnt << endl;
	}
#endif
}