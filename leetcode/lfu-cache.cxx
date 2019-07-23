/*460. LFU Cache
Hard

Design and implement a data structure for Least Frequently Used (LFU) cache. It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reaches its capacity, it should invalidate the least frequently used item before inserting a new item. For the purpose of this problem, when there is a tie (i.e., two or more keys that have the same frequency), the least recently used key would be evicted.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LFUCache cache = new LFUCache(2); //capacity

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.get(3);       // returns 3.
cache.put(4, 4);    // evicts key 1.
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4

Accepted
42,462
Submissions
145,085
*/

#warning not completely tested.

#include <bits/stdc++.h>

using namespace std;

class LFUCache {
public:
    LFUCache(int capacity) {
        cap = capacity;
		cout << "capacity " << cap << endl;
    }

	void incrRefKey(int key) {
		int ref = refCntMap_[key]++;
		if (ref)
			prioMap_[ref].erase(key); {
			if (prioMap_[ref].size() == 0)
				prioMap_.erase(ref);
		}
		ref++;
        prioMap_[ref].emplace(key);
	}

    int get(int key) {
        auto it = valMap_.find(key);
        if (it == valMap_.end()) {
			cout << "get " << key << " = -1" << endl;
            return -1;
		}
		incrRefKey(key);
		cout << "get " << key << " = " << it->second << endl;

        return it->second;
    }
	void dumpPrioMap() {
		cout << "dumpPrioMap" << endl;
		for (auto it=prioMap_.begin(); it!=prioMap_.end(); it++) {
			cout << "prio " << it->first << endl;
			for (auto it2=it->second.begin(); it2!=it->second.end(); it2++) {
				cout << " " << *it2;
			}
			cout << endl;
		}
	}
    
    void put(int key, int value) {
		cout << "put " << key << " = " << value << endl;
        auto it = valMap_.find(key);

        if (valMap_.size() == cap && it == valMap_.end()) {
			dumpPrioMap();
			auto tmp = prioMap_.begin()->second.end();
			tmp--;
            int ekey = *tmp;
			cout << "evicts " << ekey << endl;
            valMap_.erase(ekey);
            int ref = refCntMap_[ekey];
            refCntMap_.erase(ekey);
            prioMap_[ref].erase(ekey);
			if (prioMap_[ref].size() == 0)
				prioMap_.erase(ref);
        }
		valMap_[key] = value;

        incrRefKey(key);
    }
    map<int, int> valMap_;
    map<int, int> refCntMap_;
    map<int, set<int>> prioMap_;
    int cap;
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {
	LFUCache cache = new LFUCache( 2 /* capacity */ );

	cache.put(1, 1);
	cache.put(2, 2);
	cache.get(1);       // returns 1
	cache.put(3, 3);    // evicts key 2
	cache.get(2);       // returns -1 (not found)
	cache.get(3);       // returns 3.
	cache.put(4, 4);    // evicts key 1.
	cache.get(1);       // returns -1 (not found)
	cache.get(3);       // returns 3
	cache.get(4);       // returns 4
}