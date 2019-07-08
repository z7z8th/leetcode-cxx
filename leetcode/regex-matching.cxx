#include <iostream>
#include <string>

using namespace std;

class Solution {
	#define DEBUG 0
public:
	int& dp(int i, int j) {
		if (i < -1) {
			cout << "i < -1"<<endl;
		}
		if (j < -1) {
			cout << "j < -1"<<endl;
		}
		return dp_[(i+1)*COL_CNT + (j+1)];
	}
    bool isMatch(string str, string ptn) {
#if DEBUG
		//cout << "try " << str << endl
		//	 << " <> " << ptn << endl << endl;
		//
		cout << " str len " << str.size() << endl;
		cout << " ptn len " << ptn.size() << endl;
#endif
		ROW_CNT  = str.size() + 1;
		COL_CNT = ptn.size() + 1;
		dp_ = new int[ROW_CNT * COL_CNT]();
		dp(-1, -1) = true;
		if (ptn.size() > 1 && ptn[0] == '.' && ptn[1] == '*') {
			for (int i=-1; i<str.size(); i++)
				dp(i, -1) = true;
		}
 		for (int j = 1; j<ptn.size(); j+=2) {
			if (ptn[j] == '*')
				dp(-1, j) = true;
			else
				break;
		}

		//for (int j=0; j<COL_CNT; j++)
		//	dp(0, j) = true;
		for (int i=0; i<str.size(); i++) {
#if DEBUG
			cout << endl << "> " << str.substr(0, i+1) << endl;
#endif
			for (int j=0; j<ptn.size(); j++) {
#if DEBUG
				cout << "["<< i << ", " <<j<<"] " << str[i] << ", " << ptn[j] << " ; ";
				cout << " dp(" << i-1 << "," << j-1 <<") " << dp(i-1, j-1);
				if (ptn[j] == '*') {
					cout << ", dp(" << i-1 << "," << j-2 <<") " << dp(i-1, j-2);
					cout << ", dp(" << i-1 << "," << j <<") " << dp(i-1, j);
					cout << ", dp(" << i << "," << j-2 <<") " << dp(i, j-2);
				}
				cout << " ,  ";
#endif
				if (ptn[j] == '*' && j > 0){
					if (ptn[j-1] == '.' && (dp(i-1, j-2) || dp(i-1, j) || dp(i, j-2)))
						dp(i, j) = true;
					else if (ptn[j-1] == str[i] && (dp(i-1, j-2) || dp(i-1, j) || dp(i, j-2)))
						dp(i, j) = true;
					else if (ptn[j-1] != str[i] && (dp(i, j-2)))
						dp(i, j) = true;
				} else if (ptn[j] == '.' && dp(i-1, j-1)) {
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
		{ "aa", "a*"},  // true
		{ "ab", ".*"},  // true
 		{ "aab", "c*a*b"},  // true
		{ "acdcb", "c*a*b"}, // true
		{ "abc" ,  ".." },
		{ "abc" ,  "..." },
		{ "leetcode", "le*..z*d*." }, // false
		{ "leetcode", "le*..z*d*.." },  // false
		{ "helloworld", ".*hh"}, 
		{ "helloworld", ".*l*...rld"}, // true
		{ "helloworld", ".*l*..rld"}, // true, to fix
		{ "helloworld", ".*h.*"},  // true
		{ "helloworld", ".*h.*...."}, // true
		{ "mississippi", "mis*is*p*."},  // false
		{ "asdf", ""},  // false
		{ "a", ""},  // false
		{ "", "a"},  // false
		{ "", "aa"},  // false
		{ "aa", "aa"},  // true
		{ "", ""},  // true

		{ "helloworld", "*"},  // no
		{ "helloworld", "**"},  // no  // test with echo helloworld |grep --color '**', no highlight in result
		{ "helloworld", "***"},  // no
		{ "helloworld", "******"},  // no
		{ "helloworld", "hello**ld"}, // no
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