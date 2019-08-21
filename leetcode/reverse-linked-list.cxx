/* 206. Reverse Linked List
Easy

Reverse a singly linked list.

Example:

Input: 1->2->3->4->5->NULL
Output: 5->4->3->2->1->NULL

Follow up:

A linked list can be reversed either iteratively or recursively. Could you implement both?
Accepted
655,683
Submissions
1,165,006 */

#include <bits/stdc++.h>

using namespace std;

/* Definition for singly-linked list. */
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
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
    void insertNodeAfter(ListNode* prev, ListNode* toInsert) {
        toInsert->next = prev->next;
        prev->next = toInsert;
    }
    ListNode* reverseList(ListNode* head) {
        if (!head)
            return head;
        ListNode tmpNode(-1);
        ListNode *dummyHead = &tmpNode;
        ListNode *ps = head;
        dummyHead->next = head;
        ListNode* tmp = nullptr;
        while (ps->next) {
            tmp = ps->next;
            ps->next = ps->next->next;
            insertNodeAfter(dummyHead, tmp);
            //ps = ps->next;
        }
        head = dummyHead->next;
        return head;
    }
};