/*
365. Water and Jug Problem
Medium

You are given two jugs with capacities x and y litres. There is an infinite amount of water supply available. You need to determine whether it is possible to measure exactly z litres using these two jugs.

If z liters of water is measurable, you must have z liters of water contained within one or both buckets by the end.

Operations allowed:

    Fill any of the jugs completely with water.
    Empty any of the jugs.
    Pour water from one jug into another till the other jug is completely full or the first jug itself is empty.

Example 1: (From the famous "Die Hard" example)

Input: x = 3, y = 5, z = 4
Output: True

Example 2:

Input: x = 2, y = 6, z = 5
Output: False

Accepted
28,694
Submissions
98,563
 */

void swap(int *a, int *b) {
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

bool canMeasureWater(int x, int y, int z) {
    int m1 = x;
    int m2 = y;
    int m3;

    if(z>x+y)
        return false;

    while(true) {
        if(m2 > m1)
            swap(&m1, &m2);
        if(m1)
            z %= m1;
        if(m2)
            z %= m2;
        m3 = m1 - m2;
        if(m3)
            z %= m3;
        if(m3 > m2)
            swap(&m2, &m3);
        if(!m3)
            break;
        m1 = m2;
        m2 = m3;
    }

    return !z;
}
