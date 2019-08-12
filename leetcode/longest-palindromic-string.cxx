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
	for (size_t si=0; si<vec.size(); si++) {
		auto& val = vec[si];
		cout << val;
		if (si != vec.size()-1)
			cout << ", ";
	}
	cout << " ]" << endl;
}

class Solution {
public:
/* 	bool checkPalindrome(string& s, int l, int r) {
		while (l < r) {
			if (s[l++] != s[r--])
				return false;
		}
		return true;
	} */
    string longestPalindrome(string s) {
 		size_t dp_size = max(s.size(), 2UL);
        vector<vector<int>> dp(dp_size);
		for (auto& vec : dp) {
			vec.resize(dp_size, 0);
		}
        int maxLen = 1;
		int maxLenIdxL = 0;
		//int maxLenIdxR = 0;
        for (size_t ei=0; ei<s.size(); ei++) {
            for (int si=ei; si>=0; si--) {
				if (si==ei) {
					dp[si][ei] = true;
					continue;
				}
				if (si+1 == ei && s[si] == s[ei]) {
					dp[si][ei] = true;
				} else if (ei >= 1 && dp[si+1][ei-1] && s[si] == s[ei])
					dp[si][ei] = true;

				if (dp[si][ei] && maxLen < ei-si+1) {
					maxLen = ei-si+1;
					maxLenIdxL = si;
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

/*
5. Longest Palindromic Substring

Average Rating: 4.54 (310 votes)
April 8, 2016  |  496.4K views

Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example 1:

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.

Example 2:

Input: "cbbd"
Output: "bb"

Summary

This article is for intermediate readers. It introduces the following ideas: Palindrome, Dynamic Programming and String Manipulation. Make sure you understand what a palindrome means. A palindrome is a string which reads the same in both directions. For example, SSS = "aba" is a palindrome, SSS = "abc" is not.
Solution
Approach 1: Longest Common Substring

Common mistake

Some people will be tempted to come up with a quick solution, which is unfortunately flawed (however can be corrected easily):

    Reverse SSS and become S′S'S′. Find the longest common substring between SSS and S′S'S′, which must also be the longest palindromic substring.

This seemed to work, let’s see some examples below.

For example, SSS = "caba", S′S'S′ = "abac".

The longest common substring between SSS and S′S'S′ is "aba", which is the answer.

Let’s try another example: SSS = "abacdfgdcaba", S′S'S′ = "abacdgfdcaba".

The longest common substring between SSS and S′S'S′ is "abacd". Clearly, this is not a valid palindrome.

Algorithm

We could see that the longest common substring method fails when there exists a reversed copy of a non-palindromic substring in some other part of SSS. To rectify this, each time we find a longest common substring candidate, we check if the substring’s indices are the same as the reversed substring’s original indices. If it is, then we attempt to update the longest palindrome found so far; if not, we skip this and find the next candidate.

This gives us an O(n2)O(n^2)O(n2) Dynamic Programming solution which uses O(n2)O(n^2)O(n2) space (could be improved to use O(n)O(n)O(n) space). Please read more about Longest Common Substring here.

Approach 2: Brute Force

The obvious brute force solution is to pick all possible starting and ending positions for a substring, and verify if it is a palindrome.

Complexity Analysis

    Time complexity : O(n3)O(n^3)O(n3). Assume that nnn is the length of the input string, there are a total of (n2)=n(n−1)2\binom{n}{2} = \frac{n(n-1)}{2}(2n​)=2n(n−1)​ such substrings (excluding the trivial solution where a character itself is a palindrome). Since verifying each substring takes O(n)O(n)O(n) time, the run time complexity is O(n3)O(n^3)O(n3).

    Space complexity : O(1)O(1)O(1).

Approach 3: Dynamic Programming

To improve over the brute force solution, we first observe how we can avoid unnecessary re-computation while validating palindromes. Consider the case "ababa". If we already knew that "bab" is a palindrome, it is obvious that "ababa" must be a palindrome since the two left and right end letters are the same.

We define P(i,j)P(i,j)P(i,j) as following:

P(i,j)={true,false,if the substring Si…Sj is a palindromeotherwise. 

Therefore,

P(i,j)=(P(i+1,j−1) and Si==Sj) P(i, j) = ( P(i+1, j-1) \text{ and } S_i == S_j ) P(i,j)=(P(i+1,j−1) and Si​==Sj​)

The base cases are:

P(i,i)=true P(i, i) = true P(i,i)=true

P(i,i+1)=(Si==Si+1) P(i, i+1) = ( S_i == S_{i+1} ) P(i,i+1)=(Si​==Si+1​)

This yields a straight forward DP solution, which we first initialize the one and two letters palindromes, and work our way up finding all three letters palindromes, and so on...

Complexity Analysis

    Time complexity : O(n2)O(n^2)O(n2). This gives us a runtime complexity of O(n2)O(n^2)O(n2).

    Space complexity : O(n2)O(n^2)O(n2). It uses O(n2)O(n^2)O(n2) space to store the table.

Additional Exercise

Could you improve the above space complexity further and how?

Approach 4: Expand Around Center

In fact, we could solve it in O(n2)O(n^2)O(n2) time using only constant space.

We observe that a palindrome mirrors around its center. Therefore, a palindrome can be expanded from its center, and there are only 2n−12n - 12n−1 such centers.

You might be asking why there are 2n−12n - 12n−1 but not nnn centers? The reason is the center of a palindrome can be in between two letters. Such palindromes have even number of letters (such as "abba") and its center are between the two 'b's.

Complexity Analysis

    Time complexity : O(n2)O(n^2)O(n2). Since expanding a palindrome around its center could take O(n)O(n)O(n) time, the overall complexity is O(n2)O(n^2)O(n2).

    Space complexity : O(1)O(1)O(1).

Approach 5: Manacher's Algorithm

There is even an O(n)O(n)O(n) algorithm called Manacher's algorithm, explained here in detail. However, it is a non-trivial algorithm, and no one expects you to come up with this algorithm in a 45 minutes coding session. But, please go ahead and understand it, I promise it will be a lot of fun.
 */