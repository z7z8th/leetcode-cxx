/* 264. Ugly Number II
Medium

Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. 

Example:

Input: n = 10
Output: 12
Explanation: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.

Note:  

    1 is typically treated as an ugly number.
    n does not exceed 1690.

Accepted
108,425
Submissions
294,578
 */


#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int nthUglyNumber(int n) {
        if (vec_.size() > n)
            return vec_[n];
        set<int> set_;
        int fact[] = { 5, 3, 2 };
        int fact_cnt[] = {0, 0, 0};
        int fact_cnt_max[] = {
            static_cast<int>(ceil(log(INT_MAX)/log(5)))+1,
            static_cast<int>(ceil(log(INT_MAX)/log(3)))+1,
            static_cast<int>(ceil(log(INT_MAX)/log(2)))+1
        };
        /* for (int m=0; m<3; m++) {
            cout << "fact_cnt_max [" << m << "] " << fact_cnt_max[m] << endl;
        } */
        int ugn_idx = 0;
        for (int i=0; i<fact_cnt_max[0]; i++) {
            fact_cnt[1] = 0;
            for (int j=0; j<fact_cnt_max[1]; j++) {
                fact_cnt[2] = 0;
                for (int k=0; k<fact_cnt_max[2]; k++) {
                    int tmp = 1;
                    for (int m=0; m<3; m++) {
                        tmp *= pow(fact[m], fact_cnt[m]);
                    }
                    /* if (tmp == 2123366400) {
                        cout << "factor cnt for 1690th: " << endl;
                        for (int m=0; m<3; m++) {
                            cout << fact[m] << "^" << fact_cnt[m];
                            if (m != 2)
                                cout << " * ";
                        }
                        cout << endl;
                    } */
                    ugn_idx++;
                    set_.emplace(tmp);
                    fact_cnt[2]++;
                }
                fact_cnt[1]++;
            }
            fact_cnt[0]++;
        }
        //cout << "set size " << set_.size() << endl;
        vec_.resize(set_.size());
        int idx = 0;
        for (auto it : set_) {
            vec_[idx++] = (it);
        }
        return vec_[n];
    }
    static vector<int> vec_;
};
vector<int> Solution::vec_;

int main() {
    Solution sln;
    int ret = sln.nthUglyNumber(1690);
    cout << 1690 << "th ugly number " << ret << endl;
    return 0;
}
