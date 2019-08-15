/* 347. Top K Frequent Elements
Medium

Given a non-empty array of integers, return the k most frequent elements.

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Example 2:

Input: nums = [1], k = 1
Output: [1]

Note:

    You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
    Your algorithm's time complexity must be better than O(n log n), where n is the array's size.

Accepted
230,406
Submissions
410,962 */

#include <bits/stdc++.h>

using namespace std;

template<typename Type>
void printVector(vector<Type> vec) {
	cout << "[ ";
	for (size_t si=0; si<vec.size(); si++) {
		auto& val = vec[si];
		cout << val;
		if (si != vec.size()-1)
			cout << ", ";
	}
	cout << " ]" << endl;
}

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
		std::ios::sync_with_stdio(NULL);

        unordered_map<int, int> freq;
        for (auto n : nums) {
            ++freq[n];
        }
		using CompareFunction = function<bool(const pair<int, int>&, const pair<int, int>&)>;
        CompareFunction cmpLesserFunc = [](const pair<int, int>& e1, const pair<int, int>& e2) -> bool {
            return e1.second < e2.second;
        };
		/* priority queue: use < cmp function, result in large ... small */
        priority_queue<pair<int, int>, vector<pair<int, int>>, CompareFunction> freqQueue(
				freq.begin(), freq.end(), cmpLesserFunc
			);
        vector<int> vec;
        while(k-- > 0 && !freqQueue.empty()) {
            vec.push_back(freqQueue.top().first);
            freqQueue.pop();;
        }
        return vec;
    }
};

int main() {
	tuple<vector<int>, int> tcs[]{
		{{1,1,1,2,2,3}, 2},
		{{1,2}, 2},
		{{1}, 1},
		{{}, 1},
	};
	int tcIdx = 0;
	for (auto& tc : tcs) {
		cout << "case " << tcIdx++ << endl;
		printVector(get<0>(tc));
		Solution sln;
		auto ret = sln.topKFrequent(get<0>(tc), get<1>(tc));
		cout << "return ";
		printVector(ret);
		cout << endl;
	}
}