#include <bits/stdc++.h>
using namespace std;


#define SUPPORT_OCT 0
class Solution {
public:
	int skipLeadingSpace(const string &str) {
		int i;
		for (i=0; i<str.size(); i++)
			if (str[i] != ' ')
				return i;
		return i;
	}
    int myAtoi(string str) {
		int si = skipLeadingSpace(str);
		int sign = 0;
		int radix = 10;
		int ch = str[si];
		if (ch == '-') {
			sign = -1;
			si++;
		} else if (ch == '+') {
			sign = 1;
			si++;
		} else 
			sign = 1;

		ch = str[si];

		if (ch == '0' && si+1<str.size() && (str[si+1] == 'x' || str[si+1] == 'X')) {
			radix = 16;
			si += 2;
		}
#if SUPPORT_OCT
		else if (ch == '0') {
			radix = 8;
			si++;
		}
#endif

		cout << "sign " << sign << " radix " << radix << endl;
		bool overflow = false;
		int val = 0;
		for (int i=si; i<str.size(); i++) {
			int ch = str[i];
			if (radix == 8) {
				if(ch >= '0' && ch <= '7')
					ch -= '0';
				else
					break;
			} else if (radix == 16) {
				if (ch >= '0' && ch <= '9')
					ch -= '0';
				else if (ch >= 'a' && ch <= 'f')
					ch -= 'a';
				else if (ch >= 'A' && ch <= 'F')
					ch -= 'A';
				else break;
			} else {
				if (ch >= '0' && ch <= '9')
					ch -= '0';
				else
					break;
			}
			/* can not catch overflow on leetcode, so test before multiply */
			if ((INT_MAX - ch) / radix < val) {
				overflow = true;
				cout << "overflow" << endl;
				break;
			}

			int new_val = val * radix + ch;
			if (val > new_val) {
				overflow = true;
				break;
			}
			val = new_val;
		}
		if (overflow) {
			return sign < 0 ? INT_MIN : INT_MAX;
		}
        return val * sign;
    }
};

int main() {
	tuple<string, int> tcs[] {
		{ "42", 42 },
		{ "-", 0 },
		{ "+", 0 },
		{ "-a", 0 },
		{ "+a", 0 },
		{ "-42", -42 },
		{ "   ", 0 },
		{ "   -42", -42 },
		{ "+42", 42 },
#if !SUPPORT_OCT
		{ "  0000000000012345678",  12345678 }, // leetcode does not support oct radix
#else
		{ "042", 042 }, 
#endif
		{ "0x42", 0x42 },
		{ "4193 with words", 4193 },
		{ "words and 987", 0 },
		{ "-91283472332", -2147483648 },
		{ "91283472332", 2147483647 },
	};

	for (auto tc : tcs) {
		cout << "try atoi(\"" << get<0>(tc) << "\")"<< endl;
		Solution sln;
		int ret = sln.myAtoi(get<0>(tc));
		cout << "return " << ret << ", " 
			 << (ret != get<1>(tc) ? "[--WRONG--]" : "CORRECT")
			 << endl << endl;
	}

	return 0;
}
