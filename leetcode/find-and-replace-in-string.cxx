/* 
833. Find And Replace in String
Medium

To some string S, we will perform some replacement operations that replace groups of letters with new ones (not necessarily the same size).

Each replacement operation has 3 parameters: a starting index i, a source word x and a target word y.  The rule is that if x starts at position i in the original string S, then we will replace that occurrence of x with y.  If not, we do nothing.

For example, if we have S = "abcd" and we have some replacement operation i = 2, x = "cd", y = "ffff", then because "cd" starts at position 2 in the original string S, we will replace it with "ffff".

Using another example on S = "abcd", if we have both the replacement operation i = 0, x = "ab", y = "eee", as well as another replacement operation i = 2, x = "ec", y = "ffff", this second operation does nothing because in the original string S[2] = 'c', which doesn't match x[0] = 'e'.

All these operations occur simultaneously.  It's guaranteed that there won't be any overlap in replacement: for example, S = "abc", indexes = [0, 1], sources = ["ab","bc"] is not a valid test case.

Example 1:

Input: S = "abcd", indexes = [0,2], sources = ["a","cd"], targets = ["eee","ffff"]
Output: "eeebffff"
Explanation: "a" starts at index 0 in S, so it's replaced by "eee".
"cd" starts at index 2 in S, so it's replaced by "ffff".

Example 2:

Input: S = "abcd", indexes = [0,2], sources = ["ab","ec"], targets = ["eee","ffff"]
Output: "eeecd"
Explanation: "ab" starts at index 0 in S, so it's replaced by "eee". 
"ec" doesn't starts at index 2 in the original S, so we do nothing.

Notes:

    0 <= indexes.length = sources.length = targets.length <= 100
    0 < indexes[i] < S.length <= 1000
    All characters in given inputs are lowercase letters.

 
Accepted
19,601
Submissions
42,000
*/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string findReplaceString(string str, vector<int>& indexes, 
								vector<string>& sources, vector<string>& targets) {
		if (indexes.size() == 0)
			return str;
		string sret(str);
		map<int, tuple<bool, int>> map_;
        for (int i=0; i<indexes.size(); i++) {
			int offset = indexes[i];
			string& src = sources[i];
			//cout << "[" << i << "] " << " offset " << offset 
			//	 << " replace size " << src.size() << endl;
			string stmp(str.substr(offset, src.size()));
			bool match = stmp == src;
			map_.emplace(offset, tuple<bool, int>{ match, i});
		}
		int offset_diff = 0;
		for (auto it=map_.begin(); it!=map_.end(); it++) {
			int offset = it->first;
			bool match = get<0>(it->second);
			if (!match)
				continue;
			int idx = get<1>(it->second);
			string& src = sources[idx];
			string& tgt = targets[idx];
			sret.replace(offset + offset_diff, src.size(), tgt);
			offset_diff += tgt.size() - src.size();
		}

		return sret;
    }
};

/* 
"vmokgggqzp"
[3,5,1]
["kg","ggq","mo"]
["s","so","bfr"]


 */
int main() {
	tuple<string, vector<int>, vector<string>, vector<string>, string> tcs[] {
		{ "abcd", {0,2}, {"a","cd"}, {"eee","ffff"}, "eeebffff" },
		{ "abcd", {0,2}, {"ab","ec"}, {"eee","ffff"}, "eeecd" },
		{ "abcdefghijklmn", {0,2,5}, {"ab","ec", "fg" }, {"eee","ffff", "--"}, "eeecde--hijklmn" },
		{ "vmokgggqzp", {3,5,1}, {"kg","ggq","mo"}, {"s","so","bfr"}, "vbfrssozp" },
		{ "", {}, {}, {}, "" },
	};

	int tcIdx = 0;
	for (auto tc : tcs) {
		Solution sln;
		string sret = sln.findReplaceString(get<0>(tc), get<1>(tc), get<2>(tc), get<3>(tc));
		cout << "case " << tcIdx++ << endl;
		cout << "input " << get<0>(tc) << " return " << sret << endl;
		cout << (sret == get<4>(tc) ? "PASS" : "*** FAIL ***") << endl;
		cout << endl;
	}
}