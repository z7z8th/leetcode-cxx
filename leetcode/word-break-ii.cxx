/* 140. Word Break II
Hard

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences.

Note:

    The same word in the dictionary may be reused multiple times in the segmentation.
    You may assume the dictionary does not contain duplicate words.

Example 1:

Input:
s = "catsanddog"
wordDict = ["cat", "cats", "and", "sand", "dog"]
Output:
[
  "cats and dog",
  "cat sand dog"
]

Example 2:

Input:
s = "pineapplepenapple"
wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]
Output:
[
  "pine apple pen apple",
  "pineapple pen apple",
  "pine applepen apple"
]
Explanation: Note that you are allowed to reuse a dictionary word.

Example 3:

Input:
s = "catsandog"
wordDict = ["cats", "dog", "sand", "and", "cat"]
Output:
[]

Accepted
167,048
Submissions
600,827 */

/* Dynamic Programing, Backtracking */


#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
	void genSepStr(string& s) {
		int prevISep = 0;
		string str;
		for (size_t i=1; i<sepQue.size(); i++) {
			auto iSep = sepQue[i];
			str.append(s.substr(prevISep, iSep-prevISep));
			str.push_back(' ');
			prevISep = iSep;		
		}
		str.append(s.substr(prevISep, s.size()-prevISep));
		comb.emplace_back(std::move(str));
	}
	int wordBreakEx(string& s, size_t si) {
		if (si >= s.size()) {
			genSepStr(s);
			return 1;
		}
		//cout << si << " recur " << s[si] << " dp[]" << dp[si] << endl;

		if (dp[si] == 0)
			return dp[si];
		sepQue.emplace_back(si);
		char ch = s[si];
		for (auto ts : map_[ch]) {
			if (s.compare(si, ts.size(), ts) == 0) {
				//cout << si << " try " << ts << endl;
				auto ret = wordBreakEx(s, si + ts.size());
				if (ret)
					dp[si] = ret;
			}
		}
		sepQue.pop_back();
		//return dp[si] = 0;
		if (dp[si] < 0) {
			//cout << "dp [" << si << "] = 0" << endl;
			dp[si] = 0;
		}
		return comb.size() > 0;
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

    vector<string> wordBreak(string s, vector<string>& wordDict) {
		//if (!fastValidate(s, wordDict))
		//	return {};
		dp.clear();
		dp.resize(s.size()+1, -1);
		map_.clear();
		comb.clear();
        for (auto& w : wordDict) {
			map_[w[0]].emplace_back(w);
		}
		
		wordBreakEx(s, 0);
		return std::move(comb);
    }
	unordered_map<char, vector<string>> map_;
	vector<int> dp;
	vector<string> comb;
	deque<int> sepQue;
};

template<typename Type>
void printVector(vector<Type> vec) {
	cout << "[ ";
	for (auto val : vec) {
		cout << val << ", ";
	}
	cout << " ]" << endl;
}

int main() {
	tuple<string, vector<string>> tcs[] {
		{"leetcode", {"leet", "code"}},
		{"applepenapple", {"apple", "pen"}},
		{"catsandog",
			{"cats", "dog", "sand", "and", "cat"}
		},
		{"catsanddog", {"cat", "cats", "and", "sand", "dog"}},
		{"pineapplepenapple",
			{"apple", "pen", "applepen", "pine", "pineapple"}
		},
		{
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab",
			{
				"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"
			}
		},
		{
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
			{
				"aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa","ba"
			}
		}
	};

	int tcIdx = 0;
	for (auto tc : tcs) {
		cout << "case " << tcIdx++ << " : ";
		cout << "str: " << get<0>(tc) << endl;
		cout << "word dict: " << endl;
		printVector(get<1>(tc));
		Solution sln;
		auto ret = sln.wordBreak(get<0>(tc), get<1>(tc));
		cout << "sep result: " << endl;
		printVector(ret);
		cout << endl;
	}
}