/* 746. Min Cost Climbing Stairs
Easy

On a staircase, the i-th step has some non-negative cost cost[i] assigned (0 indexed).

Once you pay the cost, you can either climb one or two steps. You need to find minimum cost to reach the top of the floor, and you can either start from the step with index 0, or the step with index 1.

Example 1:

Input: cost = [10, 15, 20]
Output: 15
Explanation: Cheapest is start on cost[1], pay that cost and go to the top.

Example 2:

Input: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
Output: 6
Explanation: Cheapest is start on cost[0], and only step on 1s, skipping cost[3].

Note:

    cost will have a length in the range [2, 1000].
    Every cost[i] will be an integer in the range [0, 999].

Accepted
91,262
Submissions
190,687 */

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        vector<int> dp(max(static_cast<size_t>(2), cost.size()), 0);
        dp[0] = cost[0];
        dp[1] = cost[1];
        for (size_t i=2; i<cost.size(); i++) {
            dp[i] = min(dp[i-1], dp[i-2]) + cost[i];
        }
        return min(dp.back(), dp[dp.size()-2]);
    }
};

/*
Input:
[1,2]
[0,0,0,0]
[10, 15, 20]
[1, 100, 1, 1, 1, 100, 1, 1, 100, 1]

Output:
1
0
15
6

 */