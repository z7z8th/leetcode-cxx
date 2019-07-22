/*
Hash table solution + RB tree.
20ms, fast > 23%
 */

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        unordered_set<ListNode *> set_;
        while(head) {
            if (set_.find(head) != set_.end())
                return head;
            else
                set_.emplace(head);
            head = head->next;
        }
        return nullptr;

    }
};
