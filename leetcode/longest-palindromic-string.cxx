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
    string longestPalindrome(string s) {
        //return "a";
		// dp[i] means index of left most of palindromic string to i
        vector<int> dp(max(s.size(), 2UL),-1);
        int maxLen = 1;
        int maxLenEndIdx = 0;
        int maxLenStartIdx = 0;
		dp[0] = 0;
        for (size_t i=1; i<s.size(); i++) {
            int si = dp[i-1];
            if (si > 0) {
                if (s[si-1] == s[i]) {
                    dp[i] = si-1;
                    if (maxLen < static_cast<int>(i-si+2)) {
						maxLen = i-si+2;
						maxLenEndIdx = i;
						maxLenStartIdx = dp[i];
					}
					continue;
                }
            }
			if (s[i-1] == s[i]) {
				dp[i] = i-1;
				/* search for continous same char, e.g. ccccc */
				int j;
				for (j=i-1; j>=0; j--) {
					if (s[j] != s[i-1])
						break;
				}
				dp[i] = min(dp[i], dp[j+1]);
			} else {
				dp[i] = i;
			}
			if (maxLen < static_cast<int>(i-dp[i]+1)) {
				maxLen = i-dp[i]+1;
				maxLenEndIdx = i;
				maxLenStartIdx = dp[i];
			}
        }
		printVector(dp);
		return s.substr(dp[maxLenEndIdx], maxLen);
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
		{
			"aaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffgggggggggghhhhhhhhhhiiiiiiiiiijjjjjjjjjjkkkkkkkkkkllllllllllmmmmmmmmmmnnnnnnnnnnooooooooooppppppppppqqqqqqqqqqrrrrrrrrrrssssssssssttttttttttuuuuuuuuuuvvvvvvvvvvwwwwwwwwwwxxxxxxxxxxyyyyyyyyyyzzzzzzzzzzyyyyyyyyyyxxxxxxxxxxwwwwwwwwwwvvvvvvvvvvuuuuuuuuuuttttttttttssssssssssrrrrrrrrrrqqqqqqqqqqppppppppppoooooooooonnnnnnnnnnmmmmmmmmmmllllllllllkkkkkkkkkkjjjjjjjjjjiiiiiiiiiihhhhhhhhhhggggggggggffffffffffeeeeeeeeeeddddddddddccccccccccbbbbbbbbbbaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffgggggggggghhhhhhhhhhiiiiiiiiiijjjjjjjjjjkkkkkkkkkkllllllllllmmmmmmmmmmnnnnnnnnnnooooooooooppppppppppqqqqqqqqqqrrrrrrrrrrssssssssssttttttttttuuuuuuuuuuvvvvvvvvvvwwwwwwwwwwxxxxxxxxxxyyyyyyyyyyzzzzzzzzzzyyyyyyyyyyxxxxxxxxxxwwwwwwwwwwvvvvvvvvvvuuuuuuuuuuttttttttttssssssssssrrrrrrrrrrqqqqqqqqqqppppppppppoooooooooonnnnnnnnnnmmmmmmmmmmllllllllllkkkkkkkkkkjjjjjjjjjjiiiiiiiiiihhhhhhhhhhggggggggggffffffffffeeeeeeeeeeddddddddddccccccccccbbbbbbbbbbaaaa",
			"aaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffgggggggggghhhhhhhhhhiiiiiiiiiijjjjjjjjjjkkkkkkkkkkllllllllllmmmmmmmmmmnnnnnnnnnnooooooooooppppppppppqqqqqqqqqqrrrrrrrrrrssssssssssttttttttttuuuuuuuuuuvvvvvvvvvvwwwwwwwwwwxxxxxxxxxxyyyyyyyyyyzzzzzzzzzzyyyyyyyyyyxxxxxxxxxxwwwwwwwwwwvvvvvvvvvvuuuuuuuuuuttttttttttssssssssssrrrrrrrrrrqqqqqqqqqqppppppppppoooooooooonnnnnnnnnnmmmmmmmmmmllllllllllkkkkkkkkkkjjjjjjjjjjiiiiiiiiiihhhhhhhhhhggggggggggffffffffffeeeeeeeeeeddddddddddccccccccccbbbbbbbbbbaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffgggggggggghhhhhhhhhhiiiiiiiiiijjjjjjjjjjkkkkkkkkkkllllllllllmmmmmmmmmmnnnnnnnnnnooooooooooppppppppppqqqqqqqqqqrrrrrrrrrrssssssssssttttttttttuuuuuuuuuuvvvvvvvvvvwwwwwwwwwwxxxxxxxxxxyyyyyyyyyyzzzzzzzzzzyyyyyyyyyyxxxxxxxxxxwwwwwwwwwwvvvvvvvvvvuuuuuuuuuuttttttttttssssssssssrrrrrrrrrrqqqqqqqqqqppppppppppoooooooooonnnnnnnnnnmmmmmmmmmmllllllllllkkkkkkkkkkjjjjjjjjjjiiiiiiiiiihhhhhhhhhhggggggggggffffffffffeeeeeeeeeeddddddddddccccccccccbbbbbbbbbbaaaa"
		},
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