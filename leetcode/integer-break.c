/* 
343. Integer Break
Medium

Given a positive integer n, break it into the sum of at least two positive integers and maximize the product of those integers. Return the maximum product you can get.

Example 1:

Input: 2
Output: 1
Explanation: 2 = 1 + 1, 1 × 1 = 1.

Example 2:

Input: 10
Output: 36
Explanation: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.

Note: You may assume that n is not less than 2 and not larger than 58.
Accepted
81,799
Submissions
170,242 
*/

int integerBreak(int n) {
    int sqr = n>=5 ? 3 : sqrt(n);
    int sum = 0;
    int prod = 1;
    while(sum < n) {
        if(sqr+sum < n && (n == 2 || sqr+1+sum < n)) {
            prod *= sqr;
            sum += sqr;
        } else {
            prod *= (n-sum);
            break;
        }
    }
    return prod;
}