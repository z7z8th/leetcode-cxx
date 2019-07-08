/*
2. Add Two Numbers
Medium

You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example:

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.


*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *p1 = l1;
        ListNode *p2 = l2;
        ListNode *result = nullptr;
        ListNode *head = nullptr;
        int incr = 0;
        
        while (p1 && p2) {
            int sum = p1->val + p2->val + incr;
            ListNode *tmp = new ListNode(sum >= 10 ? sum - 10 : sum);
            incr = sum >= 10 ? 1 : 0;
            if (!result) {
                result = tmp;
                head = tmp;
            } else {
                result->next = tmp;
                result = result->next;
            }
            p1 = p1->next;
            p2 = p2->next;            
        }
        ListNode *p = p1 ? p1 : p2;
        while (p) {
            int sum = p->val + incr;
            result->next = new ListNode(sum >= 10 ? sum - 10 : sum);
            result = result->next;
            incr = sum >= 10 ? 1 : 0;
            p = p->next;
        }
        if (incr)
            result->next = new ListNode(incr);
        return head;
    }
};