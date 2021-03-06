/* 31. Next Permutation
Medium

Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place and use only constant extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.

1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1
Accepted
261,570
Submissions
845,784 */

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void swap(int& a, int& b) {
        int c = a;
        a = b;
        b = c;
    }
    int findPeakFromBack(vector<int>& nums) {
        //int peak = nums.back();
#warning use ssize_t/long/int instead of size_t when compare to 0, \
	since size_t is unsigned and always > 0, even = 0xFFFFFFFF_FFFFFFFF
        for (ssize_t i=nums.size()-2; i>=0; i--) {
            if (nums[i] < nums[i+1])
                return i+1;
            //peak = nums[i];
        }
        return 0;
    }
    // 0 1 2 3
    // 4 3 2 1, 2
    // return 1
    // 0 1 2 3 4
    // 5 4 2 2 1, 3
    // return 1
	// 0  1 2
	// 1, 3 2; 1
    // return 2
    int binSearchDescUpper(vector<int>& nums, int l, int r, int target) {
		int lorig = l;
		int mid = (l+r)/2;
        while (l < r) {
            mid = (l+r)/2;
            if (nums[mid] == target) {
				r = mid;
                break;
            }
            if (nums[mid] >  target)
                l = mid+1;
            else if (target > nums[mid])
                r = mid-1;
        }
		while (lorig < r && target >= nums[r])
			r--;
        return r;
    }
    void reverseRange(vector<int>& nums, int l, int r) {
        while (l < r) {
            swap(nums[l++], nums[r--]);
        };
    }
    void nextPermutation(vector<int>& nums) {
        int peakIdx = findPeakFromBack(nums);
        //cout << "peakIdx " << peakIdx << endl;
        if (peakIdx > 0) {
			/* find the adjacent number larger than nums[peakIdx-1] */
            int swapIdx = binSearchDescUpper(nums, peakIdx, nums.size()-1, nums[peakIdx-1]);
            //cout << "swapIdx " << swapIdx << endl;
			swap(nums[peakIdx-1], nums[swapIdx]);
            reverseRange(nums, peakIdx, nums.size()-1);
        } else {
            reverseRange(nums, 0, nums.size()-1);
        }
    }
};



template<typename Type>
void printVector(vector<Type> vec) {
	cout << "[ ";
	for (size_t i=0; i<vec.size(); i++) {
		auto& val = vec[i];
		cout << val;
		if (i != vec.size()-1)
			cout << ", ";
	}
	cout << " ]" << endl;
}

int main() {
	tuple<vector<int>, vector<int>> tcs[] {
		{{1,3,2}, {2, 1, 3}},
		{{3,2,1}, {1, 2, 3}},
		{{1,2,3}, {1, 3, 2}},
		{{1,1,5}, {1, 5, 1}},
		{{1,2,4,6,5,3}, {1, 2, 5, 3, 4, 6}},
		{{1,2,4,5,4,3}, {1, 2, 5, 3, 4, 4}},
	};
	for (auto& tc : tcs) {
		cout << "case " << endl;
		auto& nums = get<0>(tc);
		printVector(nums);
		Solution sln;
		sln.nextPermutation(nums);
		printVector(nums);
		cout << "result " << (nums != get<1>(tc) ? "** WRONG **" : "OK") << endl;
		cout << endl;
	}
}

/* [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

[[1,2,3,4],[1,2,4,3],[1,3,2,4],[1,3,4,2],[1,4,2,3],[1,4,3,2],[2,1,3,4],[2,1,4,3],[2,3,1,4],[2,3,4,1],[2,4,1,3],[2,4,3,1],[3,1,2,4],[3,1,4,2],[3,2,1,4],[3,2,4,1],[3,4,1,2],[3,4,2,1],[4,1,2,3],[4,1,3,2],[4,2,1,3],[4,2,3,1],[4,3,1,2],[4,3,2,1]]

[
	[1,2,3,4,5,6],
	[1,2,3,4,6,5],
	[1,2,3,5,4,6],
	[1,2,3,5,6,4],
	[1,2,3,6,4,5],
	[1,2,3,6,5,4],
	[1,2,4,3,5,6],
	[1,2,4,3,6,5],
	[1,2,4,5,3,6],
	[1,2,4,5,6,3],
	[1,2,4,6,3,5],
	[1,2,4,6,5,3],
	[1,2,5,3,4,6],
	[1,2,5,3,6,4],[1,2,5,4,3,6],[1,2,5,4,6,3],[1,2,5,6,3,4],[1,2,5,6,4,3],[1,2,6,3,4,5],[1,2,6,3,5,4],[1,2,6,4,3,5],[1,2,6,4,5,3],[1,2,6,5,3,4],
	[1,2,6,5,4,3],
	[1,3,2,4,5,6],
	[1,3,2,4,6,5],[1,3,2,5,4,6],[1,3,2,5,6,4],[1,3,2,6,4,5],[1,3,2,6,5,4],[1,3,4,2,5,6],[1,3,4,2,6,5],[1,3,4,5,2,6],[1,3,4,5,6,2],[1,3,4,6,2,5],
	[1,3,4,6,5,2],
	[1,3,5,2,4,6],
	[1,3,5,2,6,4],[1,3,5,4,2,6],[1,3,5,4,6,2],[1,3,5,6,2,4],
	[1,3,5,6,4,2],
	[1,3,6,2,4,5],[1,3,6,2,5,4],[1,3,6,4,2,5],[1,3,6,4,5,2],[1,3,6,5,2,4],[1,3,6,5,4,2],[1,4,2,3,5,6],[1,4,2,3,6,5],[1,4,2,5,3,6],[1,4,2,5,6,3],[1,4,2,6,3,5],[1,4,2,6,5,3],[1,4,3,2,5,6],[1,4,3,2,6,5],[1,4,3,5,2,6],[1,4,3,5,6,2],[1,4,3,6,2,5],[1,4,3,6,5,2],[1,4,5,2,3,6],[1,4,5,2,6,3],[1,4,5,3,2,6],[1,4,5,3,6,2],[1,4,5,6,2,3],[1,4,5,6,3,2],[1,4,6,2,3,5],[1,4,6,2,5,3],[1,4,6,3,2,5],[1,4,6,3,5,2],[1,4,6,5,2,3],[1,4,6,5,3,2],[1,5,2,3,4,6],[1,5,2,3,6,4],[1,5,2,4,3,6],[1,5,2,4,6,3],[1,5,2,6,3,4],[1,5,2,6,4,3],[1,5,3,2,4,6],[1,5,3,2,6,4],[1,5,3,4,2,6],[1,5,3,4,6,2],[1,5,3,6,2,4],[1,5,3,6,4,2],[1,5,4,2,3,6],[1,5,4,2,6,3],[1,5,4,3,2,6],[1,5,4,3,6,2],[1,5,4,6,2,3],[1,5,4,6,3,2],[1,5,6,2,3,4],[1,5,6,2,4,3],[1,5,6,3,2,4],[1,5,6,3,4,2],[1,5,6,4,2,3],[1,5,6,4,3,2],[1,6,2,3,4,5],[1,6,2,3,5,4],[1,6,2,4,3,5],[1,6,2,4,5,3],[1,6,2,5,3,4],[1,6,2,5,4,3],[1,6,3,2,4,5],[1,6,3,2,5,4],[1,6,3,4,2,5],[1,6,3,4,5,2],[1,6,3,5,2,4],[1,6,3,5,4,2],[1,6,4,2,3,5],[1,6,4,2,5,3],[1,6,4,3,2,5],[1,6,4,3,5,2],[1,6,4,5,2,3],[1,6,4,5,3,2],[1,6,5,2,3,4],[1,6,5,2,4,3],[1,6,5,3,2,4],[1,6,5,3,4,2],[1,6,5,4,2,3],[1,6,5,4,3,2],[2,1,3,4,5,6],[2,1,3,4,6,5],[2,1,3,5,4,6],[2,1,3,5,6,4],[2,1,3,6,4,5],[2,1,3,6,5,4],[2,1,4,3,5,6],[2,1,4,3,6,5],[2,1,4,5,3,6],[2,1,4,5,6,3],[2,1,4,6,3,5],[2,1,4,6,5,3],[2,1,5,3,4,6],[2,1,5,3,6,4],[2,1,5,4,3,6],[2,1,5,4,6,3],[2,1,5,6,3,4],[2,1,5,6,4,3],[2,1,6,3,4,5],[2,1,6,3,5,4],[2,1,6,4,3,5],[2,1,6,4,5,3],[2,1,6,5,3,4],[2,1,6,5,4,3],[2,3,1,4,5,6],[2,3,1,4,6,5],[2,3,1,5,4,6],[2,3,1,5,6,4],[2,3,1,6,4,5],[2,3,1,6,5,4],[2,3,4,1,5,6],[2,3,4,1,6,5],[2,3,4,5,1,6],[2,3,4,5,6,1],[2,3,4,6,1,5],[2,3,4,6,5,1],[2,3,5,1,4,6],[2,3,5,1,6,4],[2,3,5,4,1,6],[2,3,5,4,6,1],[2,3,5,6,1,4],[2,3,5,6,4,1],[2,3,6,1,4,5],[2,3,6,1,5,4],[2,3,6,4,1,5],[2,3,6,4,5,1],[2,3,6,5,1,4],[2,3,6,5,4,1],[2,4,1,3,5,6],[2,4,1,3,6,5],[2,4,1,5,3,6],[2,4,1,5,6,3],[2,4,1,6,3,5],[2,4,1,6,5,3],[2,4,3,1,5,6],[2,4,3,1,6,5],[2,4,3,5,1,6],[2,4,3,5,6,1],[2,4,3,6,1,5],[2,4,3,6,5,1],[2,4,5,1,3,6],[2,4,5,1,6,3],[2,4,5,3,1,6],[2,4,5,3,6,1],[2,4,5,6,1,3],[2,4,5,6,3,1],[2,4,6,1,3,5],[2,4,6,1,5,3],[2,4,6,3,1,5],[2,4,6,3,5,1],[2,4,6,5,1,3],[2,4,6,5,3,1],[2,5,1,3,4,6],[2,5,1,3,6,4],[2,5,1,4,3,6],[2,5,1,4,6,3],[2,5,1,6,3,4],[2,5,1,6,4,3],[2,5,3,1,4,6],[2,5,3,1,6,4],[2,5,3,4,1,6],[2,5,3,4,6,1],[2,5,3,6,1,4],[2,5,3,6,4,1],[2,5,4,1,3,6],[2,5,4,1,6,3],[2,5,4,3,1,6],[2,5,4,3,6,1],[2,5,4,6,1,3],[2,5,4,6,3,1],[2,5,6,1,3,4],[2,5,6,1,4,3],[2,5,6,3,1,4],[2,5,6,3,4,1],[2,5,6,4,1,3],[2,5,6,4,3,1],[2,6,1,3,4,5],[2,6,1,3,5,4],[2,6,1,4,3,5],[2,6,1,4,5,3],[2,6,1,5,3,4],[2,6,1,5,4,3],[2,6,3,1,4,5],[2,6,3,1,5,4],[2,6,3,4,1,5],[2,6,3,4,5,1],[2,6,3,5,1,4],[2,6,3,5,4,1],[2,6,4,1,3,5],[2,6,4,1,5,3],[2,6,4,3,1,5],[2,6,4,3,5,1],[2,6,4,5,1,3],[2,6,4,5,3,1],[2,6,5,1,3,4],[2,6,5,1,4,3],[2,6,5,3,1,4],[2,6,5,3,4,1],[2,6,5,4,1,3],[2,6,5,4,3,1],[3,1,2,4,5,6],[3,1,2,4,6,5],[3,1,2,5,4,6],[3,1,2,5,6,4],[3,1,2,6,4,5],[3,1,2,6,5,4],[3,1,4,2,5,6],[3,1,4,2,6,5],[3,1,4,5,2,6],[3,1,4,5,6,2],[3,1,4,6,2,5],[3,1,4,6,5,2],[3,1,5,2,4,6],[3,1,5,2,6,4],[3,1,5,4,2,6],[3,1,5,4,6,2],[3,1,5,6,2,4],[3,1,5,6,4,2],[3,1,6,2,4,5],[3,1,6,2,5,4],[3,1,6,4,2,5],[3,1,6,4,5,2],[3,1,6,5,2,4],[3,1,6,5,4,2],[3,2,1,4,5,6],[3,2,1,4,6,5],[3,2,1,5,4,6],[3,2,1,5,6,4],[3,2,1,6,4,5],[3,2,1,6,5,4],[3,2,4,1,5,6],[3,2,4,1,6,5],[3,2,4,5,1,6],[3,2,4,5,6,1],[3,2,4,6,1,5],[3,2,4,6,5,1],[3,2,5,1,4,6],[3,2,5,1,6,4],[3,2,5,4,1,6],[3,2,5,4,6,1],[3,2,5,6,1,4],[3,2,5,6,4,1],[3,2,6,1,4,5],[3,2,6,1,5,4],[3,2,6,4,1,5],[3,2,6,4,5,1],[3,2,6,5,1,4],[3,2,6,5,4,1],[3,4,1,2,5,6],[3,4,1,2,6,5],[3,4,1,5,2,6],[3,4,1,5,6,2],[3,4,1,6,2,5],[3,4,1,6,5,2],[3,4,2,1,5,6],[3,4,2,1,6,5],[3,4,2,5,1,6],[3,4,2,5,6,1],[3,4,2,6,1,5],[3,4,2,6,5,1],[3,4,5,1,2,6],[3,4,5,1,6,2],[3,4,5,2,1,6],[3,4,5,2,6,1],[3,4,5,6,1,2],[3,4,5,6,2,1],[3,4,6,1,2,5],[3,4,6,1,5,2],[3,4,6,2,1,5],[3,4,6,2,5,1],[3,4,6,5,1,2],[3,4,6,5,2,1],[3,5,1,2,4,6],[3,5,1,2,6,4],[3,5,1,4,2,6],[3,5,1,4,6,2],[3,5,1,6,2,4],[3,5,1,6,4,2],[3,5,2,1,4,6],[3,5,2,1,6,4],[3,5,2,4,1,6],[3,5,2,4,6,1],[3,5,2,6,1,4],[3,5,2,6,4,1],[3,5,4,1,2,6],[3,5,4,1,6,2],[3,5,4,2,1,6],[3,5,4,2,6,1],[3,5,4,6,1,2],[3,5,4,6,2,1],[3,5,6,1,2,4],[3,5,6,1,4,2],[3,5,6,2,1,4],[3,5,6,2,4,1],[3,5,6,4,1,2],[3,5,6,4,2,1],[3,6,1,2,4,5],[3,6,1,2,5,4],[3,6,1,4,2,5],[3,6,1,4,5,2],[3,6,1,5,2,4],[3,6,1,5,4,2],[3,6,2,1,4,5],[3,6,2,1,5,4],[3,6,2,4,1,5],[3,6,2,4,5,1],[3,6,2,5,1,4],[3,6,2,5,4,1],[3,6,4,1,2,5],[3,6,4,1,5,2],[3,6,4,2,1,5],[3,6,4,2,5,1],[3,6,4,5,1,2],[3,6,4,5,2,1],[3,6,5,1,2,4],[3,6,5,1,4,2],[3,6,5,2,1,4],[3,6,5,2,4,1],[3,6,5,4,1,2],[3,6,5,4,2,1],[4,1,2,3,5,6],[4,1,2,3,6,5],[4,1,2,5,3,6],[4,1,2,5,6,3],[4,1,2,6,3,5],[4,1,2,6,5,3],[4,1,3,2,5,6],[4,1,3,2,6,5],[4,1,3,5,2,6],[4,1,3,5,6,2],[4,1,3,6,2,5],[4,1,3,6,5,2],[4,1,5,2,3,6],[4,1,5,2,6,3],[4,1,5,3,2,6],[4,1,5,3,6,2],[4,1,5,6,2,3],[4,1,5,6,3,2],[4,1,6,2,3,5],[4,1,6,2,5,3],[4,1,6,3,2,5],[4,1,6,3,5,2],[4,1,6,5,2,3],[4,1,6,5,3,2],[4,2,1,3,5,6],[4,2,1,3,6,5],[4,2,1,5,3,6],[4,2,1,5,6,3],[4,2,1,6,3,5],[4,2,1,6,5,3],[4,2,3,1,5,6],[4,2,3,1,6,5],[4,2,3,5,1,6],[4,2,3,5,6,1],[4,2,3,6,1,5],[4,2,3,6,5,1],[4,2,5,1,3,6],[4,2,5,1,6,3],[4,2,5,3,1,6],[4,2,5,3,6,1],[4,2,5,6,1,3],[4,2,5,6,3,1],[4,2,6,1,3,5],[4,2,6,1,5,3],[4,2,6,3,1,5],[4,2,6,3,5,1],[4,2,6,5,1,3],[4,2,6,5,3,1],[4,3,1,2,5,6],[4,3,1,2,6,5],[4,3,1,5,2,6],[4,3,1,5,6,2],[4,3,1,6,2,5],[4,3,1,6,5,2],[4,3,2,1,5,6],[4,3,2,1,6,5],[4,3,2,5,1,6],[4,3,2,5,6,1],[4,3,2,6,1,5],[4,3,2,6,5,1],[4,3,5,1,2,6],[4,3,5,1,6,2],[4,3,5,2,1,6],[4,3,5,2,6,1],[4,3,5,6,1,2],[4,3,5,6,2,1],[4,3,6,1,2,5],[4,3,6,1,5,2],[4,3,6,2,1,5],[4,3,6,2,5,1],[4,3,6,5,1,2],[4,3,6,5,2,1],[4,5,1,2,3,6],[4,5,1,2,6,3],[4,5,1,3,2,6],[4,5,1,3,6,2],[4,5,1,6,2,3],[4,5,1,6,3,2],[4,5,2,1,3,6],[4,5,2,1,6,3],[4,5,2,3,1,6],[4,5,2,3,6,1],[4,5,2,6,1,3],[4,5,2,6,3,1],[4,5,3,1,2,6],[4,5,3,1,6,2],[4,5,3,2,1,6],[4,5,3,2,6,1],[4,5,3,6,1,2],[4,5,3,6,2,1],[4,5,6,1,2,3],[4,5,6,1,3,2],[4,5,6,2,1,3],[4,5,6,2,3,1],[4,5,6,3,1,2],[4,5,6,3,2,1],[4,6,1,2,3,5],[4,6,1,2,5,3],[4,6,1,3,2,5],[4,6,1,3,5,2],[4,6,1,5,2,3],[4,6,1,5,3,2],[4,6,2,1,3,5],[4,6,2,1,5,3],[4,6,2,3,1,5],[4,6,2,3,5,1],[4,6,2,5,1,3],[4,6,2,5,3,1],[4,6,3,1,2,5],[4,6,3,1,5,2],[4,6,3,2,1,5],[4,6,3,2,5,1],[4,6,3,5,1,2],[4,6,3,5,2,1],[4,6,5,1,2,3],[4,6,5,1,3,2],[4,6,5,2,1,3],[4,6,5,2,3,1],[4,6,5,3,1,2],[4,6,5,3,2,1],[5,1,2,3,4,6],[5,1,2,3,6,4],[5,1,2,4,3,6],[5,1,2,4,6,3],[5,1,2,6,3,4],[5,1,2,6,4,3],[5,1,3,2,4,6],[5,1,3,2,6,4],[5,1,3,4,2,6],[5,1,3,4,6,2],[5,1,3,6,2,4],[5,1,3,6,4,2],[5,1,4,2,3,6],[5,1,4,2,6,3],[5,1,4,3,2,6],[5,1,4,3,6,2],[5,1,4,6,2,3],[5,1,4,6,3,2],[5,1,6,2,3,4],[5,1,6,2,4,3],[5,1,6,3,2,4],[5,1,6,3,4,2],[5,1,6,4,2,3],[5,1,6,4,3,2],[5,2,1,3,4,6],[5,2,1,3,6,4],[5,2,1,4,3,6],[5,2,1,4,6,3],[5,2,1,6,3,4],[5,2,1,6,4,3],[5,2,3,1,4,6],[5,2,3,1,6,4],[5,2,3,4,1,6],[5,2,3,4,6,1],[5,2,3,6,1,4],[5,2,3,6,4,1],[5,2,4,1,3,6],[5,2,4,1,6,3],[5,2,4,3,1,6],[5,2,4,3,6,1],[5,2,4,6,1,3],[5,2,4,6,3,1],[5,2,6,1,3,4],[5,2,6,1,4,3],[5,2,6,3,1,4],[5,2,6,3,4,1],[5,2,6,4,1,3],[5,2,6,4,3,1],[5,3,1,2,4,6],[5,3,1,2,6,4],[5,3,1,4,2,6],[5,3,1,4,6,2],[5,3,1,6,2,4],[5,3,1,6,4,2],[5,3,2,1,4,6],[5,3,2,1,6,4],[5,3,2,4,1,6],[5,3,2,4,6,1],[5,3,2,6,1,4],[5,3,2,6,4,1],[5,3,4,1,2,6],[5,3,4,1,6,2],[5,3,4,2,1,6],[5,3,4,2,6,1],[5,3,4,6,1,2],[5,3,4,6,2,1],[5,3,6,1,2,4],[5,3,6,1,4,2],[5,3,6,2,1,4],[5,3,6,2,4,1],[5,3,6,4,1,2],[5,3,6,4,2,1],[5,4,1,2,3,6],[5,4,1,2,6,3],[5,4,1,3,2,6],[5,4,1,3,6,2],[5,4,1,6,2,3],[5,4,1,6,3,2],[5,4,2,1,3,6],[5,4,2,1,6,3],[5,4,2,3,1,6],[5,4,2,3,6,1],[5,4,2,6,1,3],[5,4,2,6,3,1],[5,4,3,1,2,6],[5,4,3,1,6,2],[5,4,3,2,1,6],[5,4,3,2,6,1],[5,4,3,6,1,2],[5,4,3,6,2,1],[5,4,6,1,2,3],[5,4,6,1,3,2],[5,4,6,2,1,3],[5,4,6,2,3,1],[5,4,6,3,1,2],[5,4,6,3,2,1],[5,6,1,2,3,4],[5,6,1,2,4,3],[5,6,1,3,2,4],[5,6,1,3,4,2],[5,6,1,4,2,3],[5,6,1,4,3,2],[5,6,2,1,3,4],[5,6,2,1,4,3],[5,6,2,3,1,4],[5,6,2,3,4,1],[5,6,2,4,1,3],[5,6,2,4,3,1],[5,6,3,1,2,4],[5,6,3,1,4,2],[5,6,3,2,1,4],[5,6,3,2,4,1],[5,6,3,4,1,2],[5,6,3,4,2,1],[5,6,4,1,2,3],[5,6,4,1,3,2],[5,6,4,2,1,3],[5,6,4,2,3,1],[5,6,4,3,1,2],[5,6,4,3,2,1],[6,1,2,3,4,5],[6,1,2,3,5,4],[6,1,2,4,3,5],[6,1,2,4,5,3],[6,1,2,5,3,4],[6,1,2,5,4,3],[6,1,3,2,4,5],[6,1,3,2,5,4],[6,1,3,4,2,5],[6,1,3,4,5,2],[6,1,3,5,2,4],[6,1,3,5,4,2],[6,1,4,2,3,5],[6,1,4,2,5,3],[6,1,4,3,2,5],[6,1,4,3,5,2],[6,1,4,5,2,3],[6,1,4,5,3,2],[6,1,5,2,3,4],[6,1,5,2,4,3],[6,1,5,3,2,4],[6,1,5,3,4,2],[6,1,5,4,2,3],[6,1,5,4,3,2],[6,2,1,3,4,5],[6,2,1,3,5,4],[6,2,1,4,3,5],[6,2,1,4,5,3],[6,2,1,5,3,4],[6,2,1,5,4,3],[6,2,3,1,4,5],[6,2,3,1,5,4],[6,2,3,4,1,5],[6,2,3,4,5,1],[6,2,3,5,1,4],[6,2,3,5,4,1],[6,2,4,1,3,5],[6,2,4,1,5,3],[6,2,4,3,1,5],[6,2,4,3,5,1],[6,2,4,5,1,3],[6,2,4,5,3,1],[6,2,5,1,3,4],[6,2,5,1,4,3],[6,2,5,3,1,4],[6,2,5,3,4,1],[6,2,5,4,1,3],[6,2,5,4,3,1],[6,3,1,2,4,5],[6,3,1,2,5,4],[6,3,1,4,2,5],[6,3,1,4,5,2],[6,3,1,5,2,4],[6,3,1,5,4,2],[6,3,2,1,4,5],[6,3,2,1,5,4],[6,3,2,4,1,5],[6,3,2,4,5,1],[6,3,2,5,1,4],[6,3,2,5,4,1],[6,3,4,1,2,5],[6,3,4,1,5,2],[6,3,4,2,1,5],[6,3,4,2,5,1],[6,3,4,5,1,2],[6,3,4,5,2,1],[6,3,5,1,2,4],[6,3,5,1,4,2],[6,3,5,2,1,4],[6,3,5,2,4,1],[6,3,5,4,1,2],[6,3,5,4,2,1],[6,4,1,2,3,5],[6,4,1,2,5,3],[6,4,1,3,2,5],[6,4,1,3,5,2],[6,4,1,5,2,3],[6,4,1,5,3,2],[6,4,2,1,3,5],[6,4,2,1,5,3],[6,4,2,3,1,5],[6,4,2,3,5,1],[6,4,2,5,1,3],[6,4,2,5,3,1],[6,4,3,1,2,5],[6,4,3,1,5,2],[6,4,3,2,1,5],[6,4,3,2,5,1],[6,4,3,5,1,2],[6,4,3,5,2,1],[6,4,5,1,2,3],[6,4,5,1,3,2],[6,4,5,2,1,3],[6,4,5,2,3,1],[6,4,5,3,1,2],[6,4,5,3,2,1],[6,5,1,2,3,4],[6,5,1,2,4,3],[6,5,1,3,2,4],[6,5,1,3,4,2],[6,5,1,4,2,3],[6,5,1,4,3,2],[6,5,2,1,3,4],[6,5,2,1,4,3],[6,5,2,3,1,4],[6,5,2,3,4,1],[6,5,2,4,1,3],[6,5,2,4,3,1],[6,5,3,1,2,4],[6,5,3,1,4,2],[6,5,3,2,1,4],[6,5,3,2,4,1],[6,5,3,4,1,2],[6,5,3,4,2,1],[6,5,4,1,2,3],[6,5,4,1,3,2],[6,5,4,2,1,3],[6,5,4,2,3,1],[6,5,4,3,1,2],[6,5,4,3,2,1]]
 */