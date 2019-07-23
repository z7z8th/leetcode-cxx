/* 146. LRU Cache
Medium

Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

The cache is initialized with a positive capacity.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LRUCache cache = new LRUCache( 2); // capacity

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4

 
Accepted
320,354
Submissions
1,217,909 */

#include <bits/stdc++.h>

using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) {
        cap = capacity;
		//cout << "capacity " << cap << endl;
    }

	void updateKeyAge(int key) {
		int age = ageMap_[key];
		ageMap_[key] = ++age_;
		prioMap_.erase(age);
		prioMap_[age_] = key;
	}

    int get(int key) {
        auto it = valMap_.find(key);
        if (it == valMap_.end()) {
			//cout << "get " << key << " = -1" << endl;
            return -1;
		}
		updateKeyAge(key);
		//cout << "get " << key << " = " << it->second << endl;

        return it->second;
    }
	void dumpPrioMap() {
		cout << endl << "dumpPrioMap" << endl;
		for (auto it=prioMap_.begin(); it!=prioMap_.end(); it++) {
			cout << "age " << it->first << " key " << it->second << endl;
		}
		cout << endl;
	}
    
    void put(int key, int value) {
		//cout << "put " << key << " = " << value << endl;
        auto it = valMap_.find(key);

        if (valMap_.size() == cap && it == valMap_.end()) {
			//dumpPrioMap();
			int delAge = prioMap_.begin()->first;
			int delKey = prioMap_[delAge];
			//cout << "evicts age " << delAge << " key " << delKey << endl;
			prioMap_.erase(delAge);
			valMap_.erase(delKey);
			ageMap_.erase(delKey);
        }
		valMap_[key] = value;

        updateKeyAge(key);
    }
    map<int, int> valMap_;
    map<int, int> ageMap_;
    map<int, int> prioMap_;
    int cap;
	int age_ = 0;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {
	#if 0
	LRUCache cache( 2 /* capacity */ );

	cache.put(1, 1);
	cache.put(2, 2);
	cache.get(1);       // returns 1
	cache.put(3, 3);    // evicts key 2
	cache.get(2);       // returns -1 (not found)
	cache.put(4, 4);    // evicts key 1
	cache.get(1);       // returns -1 (not found)
	cache.get(3);       // returns 3
	cache.get(4);       // returns 4
	#endif
	#if 0
	Input:
	["LRUCache","put","put","put","put","put","get","put","get","get","put","get","put","put","put","get","put","get","get","get","get","put","put","get","get","get","put","put","get","put","get","put","get","get","get","put","put","put","get","put","get","get","put","put","get","put","put","put","put","get","put","put","get","put","put","get","put","put","put","put","put","get","put","put","get","put","get","get","get","put","get","get","put","put","put","put","get","put","put","put","put","get","get","get","put","put","put","get","put","put","put","get","put","put","put","get","get","get","put","put","put","put","get","put","put","put","put","put","put","put"]
	[[10],[10,13],[3,17],[6,11],[10,5],[9,10],[13],[2,19],[2],[3],[5,25],[8],[9,22],[5,5],[1,30],[11],[9,12],[7],[5],[8],[9],[4,30],[9,3],[9],[10],[10],[6,14],[3,1],[3],[10,11],[8],[2,14],[1],[5],[4],[11,4],[12,24],[5,18],[13],[7,23],[8],[12],[3,27],[2,12],[5],[2,9],[13,4],[8,18],[1,7],[6],[9,29],[8,21],[5],[6,30],[1,12],[10],[4,15],[7,22],[11,26],[8,17],[9,29],[5],[3,4],[11,30],[12],[4,29],[3],[9],[6],[3,4],[1],[10],[3,29],[10,28],[1,20],[11,13],[3],[3,12],[3,8],[10,9],[3,26],[8],[7],[5],[13,17],[2,27],[11,15],[12],[9,19],[2,15],[3,16],[1],[12,17],[9,1],[6,19],[4],[5],[5],[8,1],[11,7],[5,2],[9,28],[1],[2,2],[7,4],[4,22],[7,24],[9,26],[13,28],[11,26]]
	Expected:
	[null,null,null,null,null,null,-1,null,19,17,null,-1,null,null,null,-1,null,-1,5,-1,12,null,null,3,5,5,null,null,1,null,-1,null,30,5,30,null,null,null,-1,null,-1,24,null,null,18,null,null,null,null,-1,null,null,18,null,null,-1,null,null,null,null,null,18,null,null,-1,null,4,29,30,null,12,-1,null,null,null,null,29,null,null,null,null,17,22,18,null,null,null,-1,null,null,null,20,null,null,null,-1,18,18,null,null,null,null,20,null,null,null,null,null,null,null]
	#endif
}