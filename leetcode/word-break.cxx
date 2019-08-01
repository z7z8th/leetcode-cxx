/* 139. Word Break
Medium

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

Note:

    The same word in the dictionary may be reused multiple times in the segmentation.
    You may assume the dictionary does not contain duplicate words.

Example 1:

Input: s = "leetcode", wordDict = ["leet", "code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".

Example 2:

Input: s = "applepenapple", wordDict = ["apple", "pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
             Note that you are allowed to reuse a dictionary word.

Example 3:

Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
Output: false

Accepted
361,633
Submissions
1,004,747 */


#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
	int wordBreakEx(string& s, size_t si) {
		if (dp[si] >= 0)
			return dp[si];
		if (si >= s.size())
			return true;
		size_t i=si;
		char ch = s[i];
		for (auto ts : map_[ch]) {
			if (s.compare(i, ts.size(), ts) == 0) {
				int ret = wordBreakEx(s, i+ts.size());
				//dp[i+ts.size()] = ret;
				if (ret)
					return dp[i] = ret;
			}
		}
		return dp[si] = 0;
	}

	bool fastValidate(string& s, vector<string>& wordDict) {
		bitset<128>	bsStr;
		bitset<128> bsWD;
		for (auto ch : s) {
			bsStr.set(ch, true);
		}
		for (auto w : wordDict) {
			for (auto ch : w) {
				bsWD.set(ch, true);
			}
		}
		return ((bsStr & bsWD) == bsStr);
	}

    bool wordBreak(string s, vector<string>& wordDict) {
		if (!fastValidate(s, wordDict))
			return false;
		dp.clear();
		dp.resize(s.size()+1, -1);
		map_.clear();
        for (auto& w : wordDict) {
			map_[w[0]].emplace_back(w);
		}
		
		return wordBreakEx(s, 0);
    }
	unordered_map<char, vector<string>> map_;
	vector<int> dp;
};

int main() {
	tuple<string, vector<string>, bool> tcs[] {
		{"leetcode", {"leet", "code"}, true},
		{"applepenapple", {"apple", "pen"}, true},
		{"catsandog", {"cats", "dog", "sand", "and", "cat"}, false},
		{
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab",
			{
				"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"
			},
			false
		},
		{
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
			{
				"aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa","ba"
			},
			false
		}
	};
	int tcIdx = 0;
	for (auto tc : tcs) {
		cout << "case " << tcIdx++ << " : ";
		Solution sln;
		int ret = sln.wordBreak(get<0>(tc), get<1>(tc));
		cout << "ret " << ret << " " << (ret != get<2>(tc) ? "** WRONG **" : "OK") << endl;
		cout << endl;
	}
}