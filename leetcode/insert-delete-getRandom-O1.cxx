/*
380. Insert Delete GetRandom O(1)
Medium

Design a data structure that supports all following operations in average O(1) time.

    insert(val): Inserts an item val to the set if not already present.
    remove(val): Removes an item val from the set if present.
    getRandom: Returns a random element from current set of elements. Each element must have the same probability of being returned.

Example:

// Init an empty set.
RandomizedSet randomSet = new RandomizedSet();

// Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomSet.insert(1);

// Returns false as 2 does not exist in the set.
randomSet.remove(2);

// Inserts 2 to the set, returns true. Set now contains [1,2].
randomSet.insert(2);

// getRandom should return either 1 or 2 randomly.
randomSet.getRandom();

// Removes 1 from the set, returns true. Set now contains [2].
randomSet.remove(1);

// 2 was already in the set, so return false.
randomSet.insert(2);

// Since 2 is the only number in the set, getRandom always return 2.
randomSet.getRandom();

Accepted
119,767
Submissions
278,034
 */


#include <unordered_map>
#include <vector>

using namespace std;
class RandomizedSet {
public:
    /** Initialize your data structure here. */
    RandomizedSet() : gen(rd()) {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        bool already = map_.find(val) != map_.end();
        if (!already) {
            vec_.push_back(val); // push back is constant time complexity
            map_.emplace(val, vec_.size()-1);
        }
        return !already;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        auto pos = map_.find(val);
        bool already = pos != map_.end();
        if (already) {
            map_[vec_.back()] = pos->second;
            vec_[pos->second] = vec_.back(); // swap with the last element
            vec_.resize(vec_.size()-1);
            map_.erase(pos);
        }
        return already;        
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        std::uniform_int_distribution<unsigned> uniform_dist(0, map_.size()-1);
        int rd = uniform_dist(gen);
        //return map_[rd];
        return vec_[rd];
    }
	vector<int> vec_;
	unordered_map<int, size_t> map_;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen; //Standard mersenne_twister_engine seeded with rd()
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
