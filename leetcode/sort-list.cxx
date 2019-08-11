/* 148. Sort List
Medium

Sort a linked list in O(n log n) time using constant space complexity.

Example 1:

Input: 4->2->1->3
Output: 1->2->3->4

Example 2:

Input: -1->5->3->4->0
Output: -1->0->3->4->5

Accepted
198,111
Submissions
541,745 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <bits/stdc++.h>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

/* Insertion sort list
 * 760ms, slow
 */
class Solution {
public:
    void insertNode(ListNode *pprev, ListNode *node) {
        ListNode *pnext = pprev->next;
        pprev->next = node;
        node->next = pnext;
    }
    ListNode* insertNodeToSortedList(ListNode *node, ListNode *head) {
        //if (!head)
        //    return node;
        ListNode *p = head;
        ListNode *pprev = nullptr;
        while(p && node->val > p->val) {
            pprev = p;
            p = p->next;
        }
        if (!pprev) {
            node->next = head;
            return node;
        }
        insertNode(pprev, node);
        return head;
    }
    ListNode* sortList(ListNode* head) {
        ListNode *p1 = head;
        ListNode *pnew = nullptr;
        while(p1) {
            ListNode *pnext = p1->next;
            //removeNode(p1);
            p1->next = nullptr;
            pnew = insertNodeToSortedList(p1, pnew);
            p1 = pnext;
        }
        return pnew;
    }
};

/* Tune clue:
 * 1. convert to vector, qsort, convert back
 * 2. merge sort
 */