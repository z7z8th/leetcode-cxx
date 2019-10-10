/* 142. Linked List Cycle II
Medium

Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

To represent a cycle in the given linked list, we use an integer pos which represents the position (0-indexed) in the linked list where tail connects to. If pos is -1, then there is no cycle in the linked list.

Note: Do not modify the linked list.

 

Example 1:

Input: head = [3,2,0,-4], pos = 1
Output: tail connects to node index 1
Explanation: There is a cycle in the linked list, where tail connects to the second node.

Example 2:

Input: head = [1,2], pos = 0
Output: tail connects to node index 0
Explanation: There is a cycle in the linked list, where tail connects to the first node.

Example 3:

Input: head = [1], pos = -1
Output: no cycle
Explanation: There is no cycle in the linked list.

 

Follow-up:
Can you solve it without using extra space?
Accepted
226,208
Submissions
690,965 */


#include <bits/stdc++.h>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
		if (!head)
			return nullptr;
        ListNode *p1 = head; // slow
		ListNode *p2 = head; // fast
		do {
            p1 = p1->next;
			if (p2->next)
				p2 = p2->next->next;
            else
                p2 = nullptr;
		} while (p2 && p1 != p2);

        if(!p2)
            return nullptr;

        /* fast_walk_len - slow_walk_len = n * circle_len;
           fast_walk_len = 2 * slow_walk_len;
           slow_walk_len = n * circle_len;
           
           straight_len = total_len - circle_len;
           slow_to_junction = total_len - slow_walk_len = total_len - circle_len - (n-1) * circle_len;
           straight_len = slow_to_junction + (n-1) * circle_len;
           another walk from head will meet slow at junction, slow may walk multiple around circle.
        */

        p2 = head;
        while(p1 != p2) {
            p1 = p1->next;
            p2 = p2->next;
        }
        return p2;
    }
};

void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}
ListNode* tail = nullptr;
ListNode* stringToListNode(string input) {
    // Generate list from the input
    vector<int> list = stringToIntegerVector(input);

    // Now convert that list into linked list
    ListNode* dummyRoot = new ListNode(0);
    ListNode* ptr = dummyRoot;
    for(int item : list) {
        ptr->next = new ListNode(item);
        ptr = ptr->next;
		tail = ptr;
    }
    ptr = dummyRoot->next;
    delete dummyRoot;
    return ptr;
}

int stringToInteger(string input) {
    return stoi(input);
}

string listNodeToString(ListNode* node) {
    if (node == nullptr) {
        return "[]";
    }

    string result;
    while (node) {
        result += to_string(node->val) + ", ";
        node = node->next;
    }
    return "[" + result.substr(0, result.length() - 2) + "]";
}

void makeCycle(ListNode *head, ListNode *tail, int pos) {
	if (pos < 0)
		return;
	for (int i=0; i<pos; i++) {
		if (!head) {
			cout << "List not long enough for " << pos << endl;
			return;
		}
		head = head->next;
	}
    if (tail)
	    tail->next = head;
}

/* 
./objs/linked-list-cycle-ii <<EOF
[1,2,3,4,5]
1
EOF
 */
int main() {
    string line;
    tuple<string, string> tcs[] {
        { "[1,2,3,4,5]", "2"},
        { "[1,2,3,4,5]", "5"},
        { "[1,2,3,4,5]", "0"},
        { "[1,2]", "-1"},
        { "[2]", "0"},
        { "[3,2,0,-4]", "1"},
    };
    //while (getline(cin, line)) {
    for (auto tc : tcs) {
		line = get<0>(tc);
        ListNode* head = stringToListNode(line);
        //getline(cin, line);
		line = get<1>(tc);
        int pos = stringToInteger(line);
		makeCycle(head, tail, pos);
        
        ListNode* ret = Solution().detectCycle(head);

        //string out = listNodeToString(ret);
        cout << (ret ? ret->val : -1) << endl;
    }
    return 0;
}