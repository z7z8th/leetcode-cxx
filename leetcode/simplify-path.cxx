/* 71. Simplify Path
Medium

Given an absolute path for a file (Unix-style), simplify it. Or in other words, convert it to the canonical path.

In a UNIX-style file system, a period . refers to the current directory. Furthermore, a double period .. moves the directory up a level. For more information, see: Absolute path vs relative path in Linux/Unix

Note that the returned canonical path must always begin with a slash /, and there must be only a single slash / between two directory names. The last directory name (if it exists) must not end with a trailing /. Also, the canonical path must be the shortest string representing the absolute path.

 

Example 1:

Input: "/home/"
Output: "/home"
Explanation: Note that there is no trailing slash after the last directory name.

Example 2:

Input: "/../"
Output: "/"
Explanation: Going one level up from the root directory is a no-op, as the root level is the highest level you can go.

Example 3:

Input: "/home//foo/"
Output: "/home/foo"
Explanation: In the canonical path, multiple consecutive slashes are replaced by a single one.

Example 4:

Input: "/a/./b/../../c/"
Output: "/c"

Example 5:

Input: "/a/../../b/../c//.//"
Output: "/c"

Example 6:

Input: "/a//b////c/d//././/.."
Output: "/a/b/c"

Accepted
158,657
Submissions
541,339 */

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string getNextDir(string& path, size_t& si) {
        size_t i=si;
       /*  while(i < path.size() && path[i] == '/') {
            i++;
        }
        si = i; */
        while(i < path.size() && path[i] != '/') {
            i++;
        }
        size_t n = i - si;
        string dir(path.substr(si, n));
        while(i < path.size() && path[i] == '/') {
            i++;
        }
        si = i;
        return dir;
    }
    void splitPathToStack(string& path, vector<string>& stk) {
        for (size_t i=0; i<path.size();) {
            string dir(std::move(getNextDir(path, i)));
            if (dir == "." || dir.empty()) {
                ;
            } else if (dir == "..") {
                if (!stk.empty())
                    stk.pop_back();
            } else {
                stk.push_back(dir);
            }            
        }
    }
    string simplifyPath(string path) {
        vector<string> stk;
        splitPathToStack(path, stk);
        string newpath;
        for (size_t i=0; i<stk.size(); i++) {
            newpath.push_back('/');
            newpath.append(std::move(stk[i]));
        }
        if (newpath.empty())
            return "/";
        return newpath;        
    }
};

int main() {
    pair<string, string> tcs[] {
        { "/home/", "/home" },
        { "/../", "/" },
        { "/home//foo/", "/home/foo" },
        { "/a/./b/../../c/", "/c" },
        { "/a/../../b/../c//.//", "/c" },
        { "/a//b////c/d//././/..", "/a/b/c" },
    };
    for (auto tc : tcs) {
        cout << "case : \"" << tc.first << "\"" << endl;
        cout << "expect \"" << tc.second << "\"" << endl;
        Solution sln;
        auto ret = sln.simplifyPath(tc.first);
        cout << "return \"" << ret << "\" " << (ret != tc.second ? "** WRONG **" : "OK") << endl;
        cout << endl;
    }
}