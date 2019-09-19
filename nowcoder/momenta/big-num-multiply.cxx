/* Momenta2019秋招技术岗笔试题
企业提供原题
00:00:22
34/37
[编程题]大数乘法

时间限制：1秒
空间限制：65536K

实现大数乘法，输入是两个字符串如
n1 = '340282366920938463463374607431768211456'
n2 = '340282366920938463463374607431768211456'
输出
'115792089237316195423570985008687907853269984665640564039457584007913129639936'
要求：不能使用对大数相乘有内建支持的语言；需要包含对输入字符串的合法性校验

输入描述:
一行，两个非负整数n1,n2，保证|n1|+|n2|<10000，其中|n|是n作为字符串的长度

输出描述:
输出n1*n2的结果

输入例子1:
340282366920938463463374607431768211456 340282366920938463463374607431768211456

输出例子1:
115792089237316195423570985008687907853269984665640564039457584007913129639936
*/

#include <bits/stdc++.h>

using namespace std;

#define MY_DRAFT 0
#define PRINT_LOG 0

#define BITCNT(x) (sizeof(x)*8U)
#define BITSET(x, i)  ((x) & (1<<(i)))
#define DIV_UP(a, b)  (((a)+(b-1)) / (b))
#define MASK(n) ((1<<(n))-1)

/* count leading zeros */
inline int clz(unsigned i) {
	if (i == 0)
		return BITCNT(i);
	return __builtin_clz(i);
}
/* find first most significant bit set to 1 */
inline int ffms(unsigned i) {
	assert(i != 0);
	return BITCNT(i) - __builtin_clz(i) - 1;
}

template <typename T>
void printVectorR(/* deque<unsigned> */ T &vec, bool fmthex = true, bool sep = true, const string &title = "") {
#if PRINT_LOG
	cout << title;
	cout << (fmthex ? "hex " : "dec ");
#endif
	int width;
	if (fmthex) {
		cout << setfill('0');
		cout << hex;
		width = sizeof(typename T::value_type) * 2;
	} else {
		width = 0;
	}
	for (ssize_t i=vec.size()-1; i>=0; i--) {
		auto val = vec[i];
		cout << setw(width) << (unsigned) val << (sep ? " " : "");
	}
	if (fmthex)
		cout << dec;
	cout << endl;
#if PRINT_LOG
	cout << endl;
#endif
}

struct bignum {
	bignum() = default;
	bignum(unsigned rhs) : num{rhs} {}
	bignum(const bignum &rhs) = default;
	bignum(bignum &&rhs): num(std::move(rhs.num)) {
	}
	bignum(const string &strn) : num{0} {
#if PRINT_LOG
		cout << "parsing dec " << strn << endl;
#endif
		for (size_t i=0; i<strn.length(); i++) {
			char ch = strn[i];
			if (ch < '0' || ch > '9') {
				bad = true;
				return;
			}
			unsigned n = ch - '0';
			*this = std::move(muli(10));
			(*this) += n;
		}
#if PRINT_LOG
		printhex();
		printdec();
#endif
	}
	bignum& operator=(const unsigned rhs) {
		num.resize(1);
		num[0] = rhs;
		return *this;
	}
	bignum& operator=(const bignum &rhs) = default;

	bignum& operator=(bignum &&rhs) {
		if (this == &rhs)
			return *this;
		num = std::move(rhs.num);
		return *this;
	}
	void printhex(const string &prefix = "") {
		cout << prefix;
		printVectorR(num, true);
	}
	void printdec(const string &prefix = "") {
		//cout << prefix;
		vector<unsigned short> bn8 = std::move(toshortbn());
		//printVectorR(bn8, true, true, "bn8 ");
		vector<unsigned char> bndec = std::move(bin2dec(bn8));
		//printVectorR(bndec, false, false, "bndec ");
		printVectorR(bndec, false, false);
	}
	vector<unsigned short> toshortbn() {
		vector<unsigned short> bn8;
		for (auto &n : num) {
			bn8.emplace_back(n & 0xFFU);
			bn8.emplace_back((n >> 8) & 0xFFU);
			bn8.emplace_back((n >> 16) & 0xFFU);
			bn8.emplace_back((n >> 24) & 0xFFU);
		}
		return bn8;
	}
	vector<unsigned char> bin2dec(vector<unsigned short> binary)
	{
		/* 
		 From: https://stackoverflow.com/a/39002548
		 */
		vector<unsigned char> decimal;
		bool all_zero = false;

		// binary[i]: stores 8-bit of the nubmer.
		// Ex. 258 = 0x102 => binary[0] = 0x2, binary[1] = 0x1.
		while (!all_zero) {
			all_zero = true;
			for (int i = binary.size() - 1; i >= 0; i--) {
				int q = binary[i] / 10;
				int r = binary[i] % 10;

				binary[i] = q;
				if (i > 0) {
					binary[i - 1] += (r << 8);
				} else {
					//decimal.insert(decimal.begin(), r);
					decimal.emplace_back(r);
				}
				if (q != 0) {
					all_zero = false;
				}
			}
		}
		// each element stands for one digit of the decimal number.
		// Ex. 258 => decimal[0] = 2, decimal[1] = 5, decimal[2] = 8.
		return decimal;
	}

	bignum& operator+=(unsigned &rhs) {
		unsigned carry = rhs;
		for (size_t i=0; i<num.size(); i++) {
			unsigned l = num[i];
			unsigned l2 = l + carry;
			num[i] = l2;
			if (l2 < l) {
				carry = 1;
			} else {
				carry = 0;
				break;
			}
		}
		if (carry)
			num.push_back(1);
		return *this;
	}
	bignum& operator+=(bignum &rhs) {
		auto &rnum  = rhs.num;
		auto maxSize = max(num.size(), rnum.size());
		unsigned carry = 0;
		for (size_t i=0; i<maxSize; i++) {
			unsigned l;
			unsigned r;
			if (i < num.size()) {
				l = num[i];
			} else {
				l = 0;
			}
			if (i < rnum.size()) {
				r = rnum[i];
			} else {
				r = 0;
			}
			unsigned l2 = l+r+carry;
			if (l2 < l)
				carry = 1;
			else
				carry = 0;
			if (i < num.size())
				num[i] = l2;
			else
				num.push_back(l2);
		}
		if (carry)
			num.push_back(1);
		return *this;
	}
	bool iszero() {
		for (int i=num.size()-1; i>=0; i--) {
			if (num[i] != 0)
				return false;
		}
		return true;
	}
	/* remove leading zeros */
	void rmlz() {
		for (auto i=num.size()-1; i>0; i++) {
			if (num[i] == 0)
				num.pop_back();
			else
				return;
		}
	}
	deque<unsigned>& lshift_num_(deque<unsigned> &tmpnum, unsigned shift) {
		int nclz = ::clz(tmpnum.back());

		if (shift > nclz) {
			tmpnum.resize(tmpnum.size() + DIV_UP(shift - nclz, BITCNT(unsigned)), 0);
		}
		for (unsigned i=0; i<shift/BITCNT(unsigned); i++)
			tmpnum.push_front(0);
		unsigned leftshift = shift & (32-1);
		unsigned rightalign = BITCNT(unsigned) - leftshift;
		unsigned ov = 0;
		//cout << "leftshift " << leftshift << " rightalign " << rightalign << endl;
		for (int i=tmpnum.size()-1; i>=0; i--) {
			ov = tmpnum[i] >> rightalign;
			tmpnum[i] <<= leftshift;
			if (ov) {
				/* cout << "i " << i <<" ov " << ov 
					 << " MASK(rightalign) "  << hex << MASK(leftshift)
					 << " tmpnum[i+1] " << tmpnum[i+1] << dec << endl; */
				assert(!(MASK(leftshift) & tmpnum[i+1]));
				tmpnum[i+1] |= ov;
			}
		}
		return tmpnum;
	}

	bignum lshift(unsigned shift) {
		if (iszero())
			return 0;

		bignum bn(*this);
		auto &tmpnum = bn.num;
		lshift_num_(tmpnum, shift);

		return bn;
	}
	bignum& lshift_inplace(unsigned shift) {
		if (iszero())
			return *this;

		lshift_num_(num, shift);
		
		return *this;
	}
	bignum rshift(unsigned shift) {
	}
	bignum muli(unsigned rhs) {
		if (!rhs)
			return 0;

		bignum ret(0);

		for (int i = ::ffms(rhs); i>=0; i--) {
			ret.lshift_inplace(1);
			if (BITSET(rhs, i)) {
				ret += *this;
			}
		}
#if 0
		cout << "this ";
		printVector(num, true);
		cout << "muli ret ";
		printVector(ret.num, true);
#endif
		return ret;
	}
	
	int ffms() {
		ssize_t i;
		for (i = num.size()-1; i>=0; i--) {
			if (num[i] != 0)
				break;
		}
		if (i < 0)
			return -1;
		return ::ffms(num[i]) + i * BITCNT(unsigned);
	}
	bool bitset(int off) {
		auto ioff = off / BITCNT(unsigned);
		auto boff = off % BITCNT(unsigned);
		if (ioff >= num.size())
			return false;
		return num[ioff] & (1 << boff);
	}
	bignum mul(bignum &rhs) {
		if (rhs.iszero() || iszero())
			return 0;

		bignum ret(0);

		for (int i = rhs.ffms(); i>=0; i--) {
			ret.lshift_inplace(1);
			if (rhs.bitset(i)) {
				ret += *this;
			}
		}
#if PRINT_LOG
		cout << "this ";
		printVectorR(num, true);
		cout << "mul ret ";
		printVectorR(ret.num, true);
#endif
		return ret;
	}

	bignum operator*(bignum &rhs) {
		return mul(rhs);
	}

	deque<unsigned> num {0U};
	bool bad = false;
};


int main() {
	assert(sizeof(unsigned) == sizeof(uint32_t));
	assert(clz(0U) == BITCNT(unsigned));
#if MY_DRAFT
	cout << "clz(0) " << clz(0) << endl;
	bignum bn1(12);
	//bn1.muli(4);
	bn1 = 1 << 31;
	cout << "1 << 31 " << (1U<<31) << endl;
	bn1.printhex("bn1 ");
	bn1.printdec("bn1 \n");
	auto bn2 = bn1.muli(1<<31);
	auto bn3 = bn2.muli(1<<31);
	bn2.printhex("bn2 ");
	bn3.printhex("bn3 ");

	tuple<string, string, string> tcs[] {
		{
			"2147483648",
			"2147483648",
			"4611686018427387904"
		},
		{ 
			"340282366920938463463374607431768211456",
			"340282366920938463463374607431768211456", "115792089237316195423570985008687907853269984665640564039457584007913129639936"
		},
	};
	for (auto &tc : tcs) {
		auto& sbn1 = get<0>(tc);
		auto& sbn2 = get<1>(tc);
		auto& sans = get<2>(tc);
		bignum bn1(sbn1);
		bignum bn2(sbn2);
		auto bn3 = std::move(bn1.mul(bn2));
		bn3.printdec("bn3 ");
	}
#else
	string sbn1, sbn2;
	while (cin >> sbn1 >> sbn2) {
		bignum bn1(sbn1);
		bignum bn2(sbn2);
		if (bn1.bad || bn2.bad) {
			cout << "" << endl;
			continue;
		}
		auto bn3 = std::move(bn1.mul(bn2));
		bn3.printdec();
	}
#endif
}
