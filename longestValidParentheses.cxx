#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

using namespace std;

class Solution
{
public:
	unsigned *dp = nullptr;
	unsigned max_dp = 0;
	unsigned max_idx = 0;
	int len = 0;
	const unsigned INIT_MASK = 1UL << 31;
	const unsigned INVALID_MASK = 1UL << 30;

	inline bool isCalced(unsigned x)
	{
		return !(x & INIT_MASK);
	}
	inline bool isValid(unsigned x)
	{
		return !(x & INVALID_MASK);
	}

	int maxValid(unsigned a, unsigned b)
	{
		if (isValid(a) && isValid(b))
			return a > b ? a : b;
		if (isValid(a))
			return a;
		if (isValid(b))
			return b;
		return INVALID_MASK;
	}

	unsigned subPar(const string &s, unsigned l, unsigned r, int depth = 0)
	{
		int depth_next = depth + 2;
		// cout << setw(depth) << "" << "l " << l << " r " << r << endl;
		int idx = l * len + r;
		if (isCalced(dp[idx]))
		{
			//cout << "ret dp " << dp[idx] << endl;
			return dp[idx];
		}
		if (l + 1 == r && !(s[l] == '(' && s[r] == ')'))
		{
			//cout << "dp["<<idx<<"]=1" << endl;
			return dp[idx] = INVALID_MASK;
		}
		if (l == r)
		{
			//cout << setw(depth) << "" << "l == r  ret INVALID" << endl;
			return dp[idx] = INVALID_MASK;
		}
		if (l > r)
		{
			//cout << setw(depth) << "" << "l > r ret 0" << endl;
			return dp[idx] = 0;
		}
		unsigned p3 = INVALID_MASK;
		if (s[l] == '(' && s[r] == ')')
		{
			//cout << setw(depth) << "" << "before p3 " << hex << p3 << dec << endl;
			p3 = subPar(s, l + 1, r - 1, depth_next) + 1;
			//cout << setw(depth) << "" << "l " << l << " r " << r << " p3 " << hex << p3 << dec 
			//	 << (isValid(p3) ? " valid" : "") << endl;
		}
		if (isValid(p3)) {
			dp[idx] = p3;
			// cout << setw(depth) << "" << "assign dp[" << idx << "] to p3 " << hex << p3 << dec << endl;
		} else {
			dp[idx] = INVALID_MASK;
			for (unsigned i = l+1; i < r; i++)
			{
				// cout << setw(depth) << "" << "l " << l << " r " << r << " iiii " << i << endl;
				unsigned p1 = 0;
				unsigned p2 = 0;

				unsigned tmp = 0;
				p1 = subPar(s, l, i, depth_next);
				// cout << setw(depth) << "" << "l " << l << " r " << r << " iiii " << i
				// 	 << " p1 " << hex << p1 << dec << endl;
				if (isValid(p1))
					p2 = subPar(s, i+1, r, depth_next);
				else
					p2 = subPar(s, i, r, depth_next);
				// cout << setw(depth) << "" << "l " << l << " r " << r << " iiii " << i
				// 	 << " p2 " << hex << p2 << dec << endl;
				if (isValid(p1) && isValid(p2))
				{
					tmp = p1 + p2;
					if (!isValid(dp[idx]) || tmp > dp[idx]) {
						// cout << setw(depth) << "" << "l " << l << " r " << r
						// 	 << " assign dp[" << idx << "] " << hex << dp[idx] << dec <<" to tmp " << tmp << endl;
						dp[idx] = tmp;
					}
				}
			}
		}
#if 0
		unsigned tmp_l_eq_r = INVALID_MASK;
		if (s[l] == '(' && s[r] == ')') {
			tmp_l_eq_r = subPar(s, l+1, r-1, depth);
			//if (isValid(tmp_l_eq_r))
			 	tmp_l_eq_r += 1;
		}
		unsigned tmp_l_eq_l1 = INVALID_MASK;
		if (s[l] == '(' && s[l+1] == ')'){
			tmp_l_eq_l1 = subPar(s, l+2, r, depth);
			//if (isValid(tmp_l_eq_l1))
				tmp_l_eq_l1 += 1;
		}
		unsigned tmp_r1_eq_r = INVALID_MASK;
		if (s[r-1] == '(' && s[r] == ')'){
			tmp_r1_eq_r = subPar(s, l, r-2, depth);
			//if (isValid(tmp_r1_eq_r))
				tmp_r1_eq_r += 1;
		}
		if (!isValid(tmp_l_eq_l1))
			unsigned tmp_l1_r = subPar(s, l+1, r, depth) | INVALID_MASK;
		if (!isValid(tmp_r1_eq_r))
			unsigned tmp_l_r1 = subPar(s, l, r-1, depth) | INVALID_MASK;
		unsigned tmp_eq = maxValid(tmp_l_eq_l1, tmp_r1_eq_r);
		tmp_eq = maxValid(tmp_eq, tmp_l_eq_r);
		//unsigned tmp_invalid = max(tmp_l1_r, tmp_l_r1);
		dp[idx] = tmp_eq; //maxValid(tmp_eq, tmp_invalid);
		//cout << setw(depth) << "" << "l " << l << " r " << r << " ret dp " << dp[idx] << endl;
			 //<< " tmp_l_eq_l1 " << tmp_l_eq_l1 << " tmp_r1_eq_r " << tmp_r1_eq_r  << endl;
#endif
		if (isValid(dp[idx]) && dp[idx] > max_dp)
			max_dp = dp[idx];
		// cout << setw(depth) << "" << "l " << l << " r " << r << " ret dp " << hex << dp[idx] << dec <<endl;
		return dp[idx];
	}
	void *memset32(void *__s, int __c, size_t __n)
	{
		for (size_t i = 0; i < __n; i++)
			*((reinterpret_cast<int *>(__s)) + i) = __c;
		return __s;
	}
	unsigned find_max_dp() {
		unsigned max_dp = 0;
		for (int i=0; i<len*len; i++) {
			if (isValid(dp[i]) && isCalced(dp[i])) {
				if (dp[i] > max_dp) {
					max_dp = dp[i];
					max_idx = i;
				}
			}
		}
		return max_dp;
	}
	int longestValidParentheses(string s)
	{
		len = s.length();
		if (!len)
			return 0;
		//cout << "len " << len << endl;
		dp = new unsigned[(len + 1) * (len + 1)];
		//int dp[len+1][len+1];
		memset32(dp, INIT_MASK, (len + 1) * (len + 1));
		subPar(s, 0, len - 1);
		//unsigned dp_ret = isValid(dp[len - 1]) ? dp[len - 1] : 0;
		unsigned max_dp = find_max_dp();
		delete[] dp;
		//return max_dp * 2;
		//cout << "result " << dp_ret * 2 << endl;
		//cout << "max dp idx " << max_idx/len << ", " << max_idx % len << endl;
		return max_dp * 2;
	}
};

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		Solution sln;
		string s(argv[1]);
		cout << endl
			 << "try argv[1]: " << s << endl;
		int ret = sln.longestValidParentheses(s);
		cout << "ret " << ret << endl;
		return 0;
	}
	string sArray[] = {
		// "",
		// "()",
		// "(",
		// ")",
		// "((",
		// "))",
		// "(()",
		// "(())",
		// "((()",  //2
		// ")()()",
		// "()(()",  //2
		// "(()(()",
		// "(()())",
		// ")()())",
		// "(()))))",
		// "(())()",
		// "(())(())",
		// "(())(())(())",
		// "(()()()()((())",
		// ")()()()()()()()",
		// ")()())((((()))(())))))))",
		//")()()) (( ((())) (()) )) ))))" //14
		"((())())(()))(()()(()(()))(()((((()))))))((()())()))()()(()(((((()()()())))()())(()()))((((((())))((()))()()))))(()))())))()))()())((()()))))(()(((((())))))()((()(()(())((((())(())((()()(()())))())(()(())()()))())(()()()))()(((()())(((()()())))(((()()()))(()()))()))()))))))())()()((()(())(()))()((()()()((())))()(((()())(()))())())))(((()))))())))()(())))()())))())()((()))((()))()))(((())((()()()(()((()((())))((()()))())(()()(()))))())((())))(()))()))))))()(()))())(()())))))(()))((())(()((())(((((()()()(()()())))(()())()((()(()()))(()(())((()((()))))))))(()(())()())()(()(()(()))()()()(()()())))(())(()((((()()))())))(())((()(())())))))())()()))(((())))())((()(()))(()()))((())(())))))(()(()((()((()()))))))(()()()(()()()(()(())()))()))(((()(())()())(()))())))(((()))())(()((()))(()((()()()(())()(()())()(())(()(()((((())()))(((()()(((()())(()()()(())()())())(()(()()((()))))()(()))))(((())))()()))(()))((()))))()()))))((((()(())()()()((()))((()))())())(()((()()())))))))()))(((()))))))(()())))(((()))((()))())))(((()(((())))())(()))))(((()(((((((((((((())(((()))((((())())()))())((((())(((())))())(((()))))()())()(())())(()))))()))()()()))(((((())()()((()))())(()))()()(()()))(())(()()))()))))(((())))))((()()(()()()()((())((((())())))))((((((()((()((())())(()((()))(()())())())(()(())(())(()((())((())))(())())))(()()())((((()))))((()(())(()(()())))))))))((()())()()))((()(((()((()))(((((()()()()()(()(()((()(()))(()(()((()()))))()(()()((((((()((()())()))((())()()(((((()(()))))()()((()())((()())()(())((()))()()(()))"
	};
	for (auto s : sArray)
	{
		Solution sln;
		cout << endl
			 << "try " << s << endl;
		int ret = sln.longestValidParentheses(s);
		cout << "ret " << ret << endl;
	}
	return 0;
}