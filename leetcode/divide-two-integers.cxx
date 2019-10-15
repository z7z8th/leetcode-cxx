/* 29. Divide Two Integers
Medium

Given two integers dividend and divisor, divide two integers without using multiplication, division and mod operator.

Return the quotient after dividing dividend by divisor.

The integer division should truncate toward zero.

Example 1:

Input: dividend = 10, divisor = 3
Output: 3

Example 2:

Input: dividend = 7, divisor = -3
Output: -2

Note:

    Both dividend and divisor will be 32-bit signed integers.
    The divisor will never be 0.
    Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−2^31,  2^31 − 1]. For the purpose of this problem, assume that your function returns 2^31 − 1 when the division result overflows.

Accepted
221,807
Submissions
1,372,738
*/

#include <bits/stdc++.h>

using namespace std;

template<typename It>
void printRange(It first, It last) {
	cout << "[ ";
	while (first != last) {
		cout << *first;
		if (++first != last)
			cout << ", ";
	}
	cout << " ]" << endl;
}

class Solution {
public:
    void fillDivs(unsigned divend, unsigned div, deque<unsigned> &divs)
    {
        while (div <= divend) {
            divs.push_front(div);
			if (div == divend)
				break;
            div <<= 1;
        }
		//printRange(divs.begin(), divs.end());
    }
    unsigned doDiv(unsigned divend, deque<unsigned> &divs)
    {
        int quot = 0;
        for (size_t i=0; i<divs.size(); i++) {
            quot <<= 1;
            auto div = divs[i];
            while (divend >= div) {
                divend -= div;
                quot++;
            }
        }
        return quot;
    }
    int divide(int dividend, int divisor) {
		int sign = (dividend & (1U << 31)) ^ (divisor & (1U << 31));
		unsigned udivend = dividend;
		unsigned udiv = divisor;
		if (dividend < 0 && dividend != INT_MIN)
			udivend = -dividend;
		if (divisor < 0 && divisor != INT_MIN)
			udiv = -divisor;
        deque<unsigned> divs;
        fillDivs(udivend, udiv, divs);
        unsigned quot = doDiv(udivend, divs);
		//cout << "divid " << dividend << " / " << divisor << " = " << quot << endl;
		if (quot & (1U<<31) && !sign)
			quot = INT_MAX;
        return  sign ? -quot : quot;
    }
};

int main()
{
	tuple <int, int, int> tcs[] {
		{ 1, 1,  1 },
		{ 2, 2,  1 },
		{ -2, -2,  1 },
		{ 1, 2,  0 },
		{ 10, 3,  3 },
		{ 7, -3, -2 },
		{ INT_MIN/* −2^31 */, -1, INT_MAX },
		{ INT_MIN/* −2^31 */, 1, INT_MIN },
		{ INT_MIN/* −2^31 */, -2, 1073741824 },
		{ INT_MIN/* −2^31 */, 2, -1073741824 },
		{ -1010369383, -2147483648, 0 },
		{ INT_MIN, INT_MIN, 1 },
	};
	for (auto &tc : tcs) {
		Solution sln;
		auto quot = sln.divide(get<0>(tc), get<1>(tc));
		cout << "case " << get<0>(tc) << " / " << get<1>(tc) << " = " << quot << endl;
	}
}