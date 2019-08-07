/* 13. Roman to Integer
Easy

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

Given a roman numeral, convert it to an integer. Input is guaranteed to be within the range from 1 to 3999.

Example 1:

Input: "III"
Output: 3

Example 2:

Input: "IV"
Output: 4

Example 3:

Input: "IX"
Output: 9

Example 4:

Input: "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.

Example 5:

Input: "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.

Accepted
455,480
Submissions
861,080 */


#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
	Solution() {
		if (valMap[0])
			return;
		pair<char, int> tmpMap[]{
			{ 'I', 1 },
			{ 'V', 5 },
			{ 'X', 10 },
			{ 'L', 50 },
			{ 'C', 100 },
			{ 'D', 500 },
			{ 'M', 1000 }
		};
		for (auto kv : tmpMap) {
			setMapVal(kv.first, kv.second);
		}
		valMap[0] = -1;
	}
	void setMapVal(char sym, int val) {
		valMap[sym - 'A'] = val;
	}
    int romanToInt(string s) {
        int sum = 0;
		int tmp = 0;
		for (size_t i=0; i<s.size(); i++) {
			int val = valMap[s[i]-'A'];
			if (tmp < val) {
				tmp = val - tmp;
			} else {
				sum += tmp;
				tmp = val;
			}
		}
		if (tmp)
			sum += tmp;
		return sum;
    }
/* 	map<char, int> valMap {
		{ 'I', 1 },
		{ 'V', 5 },
		{ 'X', 10 },
		{ 'L', 50 },
		{ 'C', 100 },
		{ 'D', 500 },
		{ 'M', 1000 },
	}; */
	static int valMap[26];
};
int Solution::valMap[26];

int main() {
	pair<string, int> tcs[] {
		{"", 0},
		{"I", 1},
		{"III", 3},
		{"IV", 4},
		{"IX", 9},
		{"LVIII", 58},
		{"MCMXCIV", 1994},
	};
	int tcIdx = 0;
	for (auto tc : tcs) {
		cout << "case " << tcIdx++ << " : " << endl;
		cout << tc.first << " = " << tc.second << endl;
		Solution sln;
		int ret = sln.romanToInt(tc.first);
		cout << "ret " << ret << " " << (ret != tc.second ? "** WRONG **" : "OK") << endl;
		cout << endl;
	}
}