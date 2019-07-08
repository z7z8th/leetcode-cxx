/* 342. Power of Four
Easy

Given an integer (signed 32 bits), write a function to check whether it is a power of 4.

Example 1:

Input: 16
Output: true

Example 2:

Input: 5
Output: false

Follow up: Could you solve it without loops/recursion?
Accepted
116,949
Submissions
289,073 */

bool isPowerOfFour(int num) {
    if((num & (1UL<<31)))
        return false;
    for(int i = 0; i<32; i++) {
        if (num & 1)
            if (num>>1 != 0)
                return false;
            else if ((i & 1) == 0)
                return true;
            else return false;
        else
            num >>= 1;
    }
    return false;
}

