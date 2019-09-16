
#include <bits/stdc++.h>

using namespace std;

//#define MY_DRAFT

unsigned weird_num_v3(unsigned n) {
	unsigned sum = 0;
	for (unsigned i=1; i<=n/2;/*  i++ */) {
		unsigned x = n/i;
		//cout << x << " ";
		sum += x;
		if (x < 3000) {
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
#ifdef MY_DRAFT
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
#ifdef MY_DRAFT
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
#ifdef MY_DRAFT
	cout << "sum bf " << sum << endl;
#endif
	return sum;
}

int main() {
#ifdef MY_DRAFT
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
		auto ret_bf = weird_num_brute_force(n);
		auto ret = weird_num(n);
		cout << "case " << n << " " << ((ret_bf != ans || ret != ans) ? "** WRONG **" : "OK") << endl;
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