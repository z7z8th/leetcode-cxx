/*
49. Group Anagrams
Medium

Given an array of strings, group anagrams together.

Example:

Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
Output:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]

Note:

    All inputs will be in lowercase.
    The order of your output does not matter.


*/

class Solution {
public:
    void processStr(const string &str) {
        string strsorted(str);
        sort(strsorted.begin(), strsorted.end());
        map_[strsorted].push_back(str);
            
    }
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> retVec;
        for (auto str : strs) {
            processStr(str);
        }
        for (auto it = map_.begin(); it != map_.end(); it++) {
            retVec.emplace_back(std::move(it->second));
        }
        return retVec;
    }
    unordered_map<string, vector<string>> map_;
};