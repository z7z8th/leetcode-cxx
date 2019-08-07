/* 12. Integer to Roman
Medium

Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000

For example, two is written as II in Roman numeral, just two one's added together. Twelve is written as, XII, which is simply X + II. The number twenty seven is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

    I can be placed before V (5) and X (10) to make 4 and 9. 
    X can be placed before L (50) and C (100) to make 40 and 90. 
    C can be placed before D (500) and M (1000) to make 400 and 900.

Given an integer, convert it to a roman numeral. Input is guaranteed to be within the range from 1 to 3999.

Example 1:

Input: 3
Output: "III"

Example 2:

Input: 4
Output: "IV"

Example 3:

Input: 9
Output: "IX"

Example 4:

Input: 58
Output: "LVIII"
Explanation: L = 50, V = 5, III = 3.

Example 5:

Input: 1994
Output: "MCMXCIV"
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.

Accepted
250,441
Submissions
484,516 */

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
	Solution() {
	}
	inline void singToRoman(int sing, const char ten, const char five, const char one) {
		tmpStr.resize(4);
		tmpStr.clear();
		if (sing == 9) {
			tmpStr.push_back(one);
			tmpStr.push_back(ten);
			return ;
		}
		if (sing >= 5) {
			tmpStr.push_back(five);
			sing -= 5;
		}
		if (sing == 4) {
			tmpStr.push_back(one);
			tmpStr.push_back(five);
			return ;
		}
		for (int i=0; i<sing; i++)
			tmpStr.push_back(one);
		//return tmpStr;
	}
	/* 	
		I             1
		V             5
		X             10
		L             50
		C             100
		D             500
		M             1000
	*/
    string intToRoman(int num) {
		string roman;
		for (auto valBase : valBaseMap) {
			if (num >= valBase[0]) {
				int part = num/valBase[0];
				singToRoman(part, valBase[1], valBase[2], valBase[3]);
				roman.append(std::move(tmpStr));
				num -= part * valBase[0];
			}
		}
		return roman;
    }
	const static int valBaseMap[4][4];
	string tmpStr;
};

const int Solution::valBaseMap[][4] = {
	{1000, '\0', '\0', 'M'},
	{100, 'M', 'D', 'C'},
	{10, 'C', 'L', 'X'},
	{1, 'X', 'V', 'I'},
};

int main() {
	pair<int, string> tcs[] {
		{ 1994, "MCMXCIV" },
		{ 400, "CD" },
		{ 58, "LVIII" },
		{ 0, "" },
		{ 1, "I" },
		{ 3, "III" },
		{ 4, "IV" },
		{ 9, "IX" },
	};
	int tcIdx = 0;
	for (auto tc : tcs) {
		cout << "case " << tcIdx++ << " : " << endl;
		cout << tc.first << " = " << tc.second << endl;
		Solution sln;
		auto ret = sln.intToRoman(tc.first);
		cout << "ret " << ret << " " << (ret != tc.second ? "** WRONG **" : "OK") << endl;
		cout << endl;
	}
}