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
