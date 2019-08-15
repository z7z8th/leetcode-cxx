/* 1154. Day of the Year

    User Accepted: 2684
    User Tried: 2764
    Total Accepted: 2820
    Total Submissions: 5405
    Difficulty: Easy

Given a string date representing a Gregorian calendar date formatted as YYYY-MM-DD, return the day number of the year.

 

Example 1:

Input: date = "2019-01-09"
Output: 9
Explanation: Given date is the 9th day of the year in 2019.

Example 2:

Input: date = "2019-02-10"
Output: 41

Example 3:

Input: date = "2003-03-01"
Output: 60

Example 4:

Input: date = "2004-03-01"
Output: 61

 

Constraints:

    date.length == 10
    date[4] == date[7] == '-', and all other date[i]'s are digits
    date represents a calendar date between Jan 1st, 1900 and Dec 31, 2019.
 */


#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    int dayOfYear(string date) {
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));
        monthDays[1] = 28;
        if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
            monthDays[1] = 29;
        int dayOfYear = 0;
        for (int i=0; i<month-1; i++)
            dayOfYear += monthDays[i];
        dayOfYear += day;
        return dayOfYear;
    }
    int monthDays[12] { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
};

/*
"2019-01-09"  9
"2019-02-10"  41
"2003-03-01"  60
"2004-03-01"  61
"2000-03-01"  61
"1900-03-25"  84
 */