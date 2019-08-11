/* 147. Insertion Sort List
Medium

Sort a linked list using insertion sort.


A graphical example of insertion sort. The partial sorted list (black) initially contains only the first element in the list.
With each iteration one element (red) is removed from the input data and inserted in-place into the sorted list
 

Algorithm of Insertion Sort:

    Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list.
    At each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list, and inserts it there.
    It repeats until no input elements remain.


Example 1:

Input: 4->2->1->3
Output: 1->2->3->4

Example 2:

Input: -1->5->3->4->0
Output: -1->0->3->4->5

Accepted
155,882
Submissions
410,262

 */

#include <bits/stdc++.h>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};


#include <bits/stdc++.h>

using namespace std;

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
    ListNode* insertionSortList(ListNode* head) {
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