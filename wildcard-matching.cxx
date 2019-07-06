#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int abc;
		return true;
    }
};


int main() {
	string tcs[][2] {
		{ "aa", "a" },  // false
		{ "aa", "*"},  // true
		{ "cb", "?a"},  // false
		{ "adceb", "*a*b"},  // true
		{ "acdcb", "a*c?b"}, // false
		{ "baaabab", "*****ba*****ab"},  // true
		{ "", "baaa?ab"},  // true
		{ "", "ba*a?"},  // true
		{ "", "a*ab"},  // false

	};

	for (auto tc : tcs) {
		Solution sln;
		bool ret = sln.isMatch(tc[0], tc[1]);
		cout << (ret ? "" : "[NOT]") << " match" << endl;
	}
}