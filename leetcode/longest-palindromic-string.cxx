/* 5. Longest Palindromic Substring
Medium

Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example 1:

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.

Example 2:

Input: "cbbd"
Output: "bb"

Accepted
619,434
Submissions
2,235,448

How can we reuse a previously computed palindrome to compute a larger palindrome?

If “aba” is a palindrome, is “xabax” and palindrome? Similarly is “xabay” a palindrome?

Complexity based hint:
If we use brute-force and check whether for every start and end position a substring is a palindrome we have O(n^2) start - end pairs and O(n) palindromic checks. Can we reduce the time for palindromic checks to O(1) by reusing some previous computation.

 */
/* 
   0 1 2 3
   a b b a
*/

#include <bits/stdc++.h>

using namespace std;

template<typename Type>
void printVector(vector<Type> vec) {
	cout << "[ ";
	for (size_t i=0; i<vec.size(); i++) {
		auto& val = vec[i];
		cout << val;
		if (i != vec.size()-1)
			cout << ", ";
	}
	cout << " ]" << endl;
}

class Solution {
public:
	bool checkPalindrome(string& s, int l, int r) {
		while (l < r) {
			if (s[l++] != s[r--])
				return false;
		}
		return true;
	}
    string longestPalindrome(string s) {
        //return "a";
		// dp[i] means index of left most of palindromic string to i
/* 		size_t dp_size = max(s.size(), 2UL);
        vector<vector<int>> dp(dp_size);
		for (auto& vec : dp) {
			vec.resize(dp_size, -1);
		} */
        int maxLen = 1;
		int maxLenIdxL = 0;
		//int maxLenIdxR = 0;
        for (size_t i=0; i<s.size(); i++) {
            for (int j=i; j<s.size(); j++) {
				//dp[i][j] = checkPalindrome(s, i, j);
				//if (dp[i][j] && maxLen < j-i+1) {
				if (checkPalindrome(s, i, j) && maxLen < j-i+1) {
					maxLen = j-i+1;
					maxLenIdxL = i;
					//maxLenIdxR = j;
				}
			}
        }
		return s.substr(maxLenIdxL, maxLen);
    }
};

int main() {
	pair<string, string> tcs[] {
		{"babad", "bab"},
		{"cbbd", "bb"},
		{"ab", "a"},
		{"a", "a"},
		{"", ""},
		{ "ababcbabdef", "babcbab"},
		{ "ccc", "ccc"},
		{ "cccc", "cccc"},
		{ "ccccc", "ccccc"},
		{ "ccbcc", "ccbcc"},
		{ "ccbccc", "ccbcc"},
		{ "cccbcc", "ccbcc"},
		{ "cccbccc", "cccbccc"},
		{ "abbaabba", "abbaabba"},
		/* {
			"aaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffgggggggggghhhhhhhhhhiiiiiiiiiijjjjjjjjjjkkkkkkkkkkllllllllllmmmmmmmmmmnnnnnnnnnnooooooooooppppppppppqqqqqqqqqqrrrrrrrrrrssssssssssttttttttttuuuuuuuuuuvvvvvvvvvvwwwwwwwwwwxxxxxxxxxxyyyyyyyyyyzzzzzzzzzzyyyyyyyyyyxxxxxxxxxxwwwwwwwwwwvvvvvvvvvvuuuuuuuuuuttttttttttssssssssssrrrrrrrrrrqqqqqqqqqqppppppppppoooooooooonnnnnnnnnnmmmmmmmmmmllllllllllkkkkkkkkkkjjjjjjjjjjiiiiiiiiiihhhhhhhhhhggggggggggffffffffffeeeeeeeeeeddddddddddccccccccccbbbbbbbbbbaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffgggggggggghhhhhhhhhhiiiiiiiiiijjjjjjjjjjkkkkkkkkkkllllllllllmmmmmmmmmmnnnnnnnnnnooooooooooppppppppppqqqqqqqqqqrrrrrrrrrrssssssssssttttttttttuuuuuuuuuuvvvvvvvvvvwwwwwwwwwwxxxxxxxxxxyyyyyyyyyyzzzzzzzzzzyyyyyyyyyyxxxxxxxxxxwwwwwwwwwwvvvvvvvvvvuuuuuuuuuuttttttttttssssssssssrrrrrrrrrrqqqqqqqqqqppppppppppoooooooooonnnnnnnnnnmmmmmmmmmmllllllllllkkkkkkkkkkjjjjjjjjjjiiiiiiiiiihhhhhhhhhhggggggggggffffffffffeeeeeeeeeeddddddddddccccccccccbbbbbbbbbbaaaa",
			"aaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffgggggggggghhhhhhhhhhiiiiiiiiiijjjjjjjjjjkkkkkkkkkkllllllllllmmmmmmmmmmnnnnnnnnnnooooooooooppppppppppqqqqqqqqqqrrrrrrrrrrssssssssssttttttttttuuuuuuuuuuvvvvvvvvvvwwwwwwwwwwxxxxxxxxxxyyyyyyyyyyzzzzzzzzzzyyyyyyyyyyxxxxxxxxxxwwwwwwwwwwvvvvvvvvvvuuuuuuuuuuttttttttttssssssssssrrrrrrrrrrqqqqqqqqqqppppppppppoooooooooonnnnnnnnnnmmmmmmmmmmllllllllllkkkkkkkkkkjjjjjjjjjjiiiiiiiiiihhhhhhhhhhggggggggggffffffffffeeeeeeeeeeddddddddddccccccccccbbbbbbbbbbaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffgggggggggghhhhhhhhhhiiiiiiiiiijjjjjjjjjjkkkkkkkkkkllllllllllmmmmmmmmmmnnnnnnnnnnooooooooooppppppppppqqqqqqqqqqrrrrrrrrrrssssssssssttttttttttuuuuuuuuuuvvvvvvvvvvwwwwwwwwwwxxxxxxxxxxyyyyyyyyyyzzzzzzzzzzyyyyyyyyyyxxxxxxxxxxwwwwwwwwwwvvvvvvvvvvuuuuuuuuuuttttttttttssssssssssrrrrrrrrrrqqqqqqqqqqppppppppppoooooooooonnnnnnnnnnmmmmmmmmmmllllllllllkkkkkkkkkkjjjjjjjjjjiiiiiiiiiihhhhhhhhhhggggggggggffffffffffeeeeeeeeeeddddddddddccccccccccbbbbbbbbbbaaaa"
		}, */
		{
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabcaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		}
	};

	for (auto tc : tcs) {
		cout << "case " << tc.first << endl;
		cout << "expect " << tc.second << endl;
		Solution sln;
		auto ret = sln.longestPalindrome(tc.first);
		cout << "return " << ret << " " << (ret != tc.second ? "** WRONG **" : "OK") << endl;
		cout << endl;
	}
}