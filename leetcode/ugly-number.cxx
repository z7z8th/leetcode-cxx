/*
263. Ugly Number
Easy

Write a program to check whether a given number is an ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5.

Example 1:

Input: 6
Output: true
Explanation: 6 = 2 × 3

Example 2:

Input: 8
Output: true
Explanation: 8 = 2 × 2 × 2

Example 3:

Input: 14
Output: false 
Explanation: 14 is not ugly since it includes another prime factor 7.

Note:

    1 is typically treated as an ugly number.
    Input is within the 32-bit signed integer range: [−231,  231 − 1].

Accepted
161,826
Submissions
397,292
 */


class Solution {
public:
    bool isUgly(int num) {
        int fact[] = { 2, 3, 5 };
        for (int i=0; i<3; i++) {
            while (num > 1) {
                int tmp = num / fact[i];
                if (tmp * fact[i] != num)
                    break;
                num  = tmp;
            }
        }
        return num == 1;
    }
};