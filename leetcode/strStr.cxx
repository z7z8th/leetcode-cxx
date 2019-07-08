class Solution {
public:
    int strStr(string str, string sub) {
        if (sub.length() == 0)
            return 0;
        for (int i=0; i<str.length(); i++) {
            bool match = str.length() - i >= sub.length();
            for (int j=0; match && j<sub.length() && i+j<str.length(); j++) {
                if (str[i+j] != sub[j]) {
                    match = false;
                    break;
                }
            }
            if (match)
                return i;
        }
        return -1;
    }
};

// passed on leetcode