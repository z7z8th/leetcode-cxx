/* 123. Best Time to Buy and Sell Stock III
Hard

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note: You may not engage in multiple transactions at the same time (i.e., you must sell the stock before you buy again).

Example 1:

Input: [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
             Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.

Example 2:

Input: [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
             Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are
             engaging multiple transactions at the same time. You must sell before buying again.

Example 3:

Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.

Accepted
157,556
Submissions
459,866 */


#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prs) {
        int buy_1 = INT_MAX;
        int profit_1 = INT_MIN;
        int buy_2 = INT_MAX;
        int profit_2 = 0;
        
        for (int i=0; i<prs.size(); i++) {
            /* same as maxprofit only one transcation allowed */
            if (prs[i] < buy_1)
                buy_1 = prs[i];
            if (prs[i] - buy_1 > profit_1)
                profit_1 = prs[i] - buy_1;
            
            if (prs[i] - profit_1 < buy_2)
                buy_2 = prs[i] - profit_1; // preserve profit_1
            if (prs[i] - buy_2 > profit_2)
                profit_2 = prs[i] - buy_2;
        }
        return profit_2;
    }
};

void printArray(vector<int>& vec) {
    for (auto val :  vec) {
        cout << val << ", ";
    }
    cout << endl;
}

int main() {
    tuple<vector<int>, int> tcs[] {
        {{1,2,4,2,5,7,2,4,9,0}, 13},
        {{3,3,5,0,0,3,1,4}, 6},
        {{1,2,3,4,5}, 4},
        {{7,6,4,3,1}, 0},
        {{}, 0}
    };

    int tcIdx = 0;
    for (auto tc : tcs) {
        Solution sln;
        cout << "case " << tcIdx << " :" << endl;
        printArray(get<0>(tc));
        cout << "max profit : " << get<1>(tc) << endl;
        int ret = sln.maxProfit(get<0>(tc));
        cout << "ret " << ret << endl << endl;
    }
    return 0;
}