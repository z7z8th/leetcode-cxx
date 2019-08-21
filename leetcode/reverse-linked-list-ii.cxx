/* 92. Reverse Linked List II
Medium

Reverse a linked list from position m to n. Do it in one-pass.

Note: 1 ≤ m ≤ n ≤ length of list.

Example:

Input: 1->2->3->4->5->NULL, m = 2, n = 4
Output: 1->4->3->2->5->NULL

Accepted
209,177
Submissions
584,743 */

#include <bits/stdc++.h>

using namespace std;

/* Definition for singly-linked list. */
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    void insertNodeAfter(ListNode* prev, ListNode* toInsert) {
        toInsert->next = prev->next;
        prev->next = toInsert;
    }
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode tmpNode(-1);
        ListNode *dummyHead = &tmpNode;
        ListNode *ps = head;
        ListNode *pprev = nullptr;
        dummyHead->next = head;
        pprev = dummyHead;
        int i=1;
        while(i < m) {
            pprev = ps;
            ps = ps->next;
            i++;
        }
        ListNode* tmp = nullptr;
        while (i < n) {
            tmp = ps->next;
            ps->next = ps->next->next;
            insertNodeAfter(pprev, tmp);
            //ps = ps->next;
            i++;
        }
        head = dummyHead->next;
        return head;
    }
};