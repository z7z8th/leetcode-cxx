/*
50. Pow(x, n)
Medium

Implement pow(x, n), which calculates x raised to the power n (xn).

Example 1:

Input: 2.00000, 10
Output: 1024.00000

Example 2:

Input: 2.10000, 3
Output: 9.26100

Example 3:

Input: 2.00000, -2
Output: 0.25000
Explanation: 2-2 = 1/22 = 1/4 = 0.25

Note:

    -100.0 < x < 100.0
    n is a 32-bit signed integer, within the range [−231, 231 − 1]

Accepted
333,452
Submissions
1,182,984
 */


class Solution {
public:
    double myPow(double x, long long n) {
		//cout << "n " << n << endl;
        if (abs(n) < 1)
            return 1;
        int sign = n < 0 ? -1 : 1;
        n = abs(n);
        bool isodd = n & 0x1;
        double ret = myPow(x, n>>1);
        ret *= ret;
        if (isodd)
            ret *= x;
        return (sign<0) ? 1.0/ret : ret;
    }
};