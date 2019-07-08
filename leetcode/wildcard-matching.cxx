#include <iostream>
#include <string>

using namespace std;

class Solution {
	#define DEBUG 0
public:
	int& dp(int i, int j) {
		return dp_[(i+1)*COL_CNT + (j+1)];
	}
    bool isMatch(string str, string ptn) {
#if DEBUG
		cout << "try " << str << endl
			 << " <> " << ptn << endl << endl;

		cout << " str len " << str.size() << endl;
		cout << " ptn len " << ptn.size() << endl;
#endif
		ROW_CNT  = str.size() + 1;
		COL_CNT = ptn.size() + 1;
		dp_ = new int[ROW_CNT * COL_CNT]();
		dp(-1, -1) = true;
		if (ptn[0] == '*') {
			for (int i=-1; i<str.size(); i++)
				dp(i, -1) = true;
		}
		for (int j = 0; j<ptn.size(); j++) {
			if (ptn[j] == '*')
				dp(-1, j) = true;
			else
				break;
		}

		//for (int j=0; j<COL_CNT; j++)
		//	dp(0, j) = true;
		for (int i=0; i<str.size(); i++) {
#if DEBUG
			cout << endl "> " << str.substr(0, i+1) << endl;
#endif
			for (int j=0; j<ptn.size(); j++) {
#if DEBUG
				cout << "["<< i << ", " <<j<<"] " << str[i] << ", " << ptn[j] << " ; "
					 //<< " dp(" << i << "," << j-1 <<") " << dp(i, j-1)
					 << " dp(" << i-1 << "," << j-1 <<") " << dp(i-1, j-1)
					 << " ,  ";
#endif
				if (ptn[j] == '*' && (dp(i-1, j-1) || dp(i-1, j) || dp(i, j-1))) {
					dp(i, j) = true;
				} else if (ptn[j] == '?' && dp(i-1, j-1)) {
					dp(i, j) = true;
				} else if (ptn[j] == str[i] && (dp(i-1, j-1)) ) {
					dp(i, j) = true;
				} else {
					//dp(i, j) = false;
				}
#if DEBUG
				cout << "new dp(" << i << "," << j <<") " << dp(i, j) << endl;
#endif
			}
		}
		return dp(str.size()-1, ptn.size()-1);
    }

	int *dp_ = nullptr;
	int COL_CNT = 0;
	int ROW_CNT = 0;
};


int main() {
	string tcs[][2] {
		{ "aa", "a" },  // false
		{ "aa", "*"},  // true
		{ "cb", "?a"},  // false
 		{ "adceb", "*a*b"},  // true
		{ "acdcb", "a*c?b"}, // false
		{ "baaabab", "*****ba*****ab"},  // true
		{ "baaabab", "baaa?ab"},  // true
		{ "baaabab", "ba*a?"},  // true
		{ "baaabab", "a*ab"},  // false
		{ "asdf", ""},  // false
		{ "a", ""},  // false
		{ "", ""},  // false

	};

	for (auto tc : tcs) {
		Solution sln;
		cout << "try '" << tc[0] << "'" << endl
			 << " <> '" << tc[1] << "'" << endl;
		bool ret = sln.isMatch(tc[0], tc[1]);
		cout << (ret ? "#YES#" : "[NO]") << " match" << endl << endl;
		cout << endl;
	}
}