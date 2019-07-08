/*
128. Longest Consecutive Sequence
Hard

Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

Your algorithm should run in O(n) complexity.

Example:

Input: [100, 4, 200, 1, 3, 2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.

Accepted
214,902
Submissions
511,081
 */

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.size() == 0)
            return 0;
        std::set<int> nset(nums.begin(), nums.end());
        int count_max = 1;
        int count = 1;
        auto it = nset.begin();
        int prev = *it;
        for (++it; it != nset.end(); it++) {
            if (*it == prev+1) {
                prev++;
                count++;
                if (count > count_max)
                    count_max = count;
            } else {
                prev = *it;
                count = 1;
            }
        }
        return count_max;
    }
};