#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

int main() {
	vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	for (auto &i : v1) {
		i *= i;
	}
	for (auto it = v1.begin(); it != v1.end(); it++) {
		cout << "*it "  << ", " << *it << endl;
	}
	for (auto it = v1.cbegin(); it != v1.cend(); it++) {
		cout << "*cit "  << ", " << *it << endl;
	}
	cout << "mid " << *(v1.begin() +  (v1.end() - v1.begin())/2) << endl;
	vector<int>::difference_type dist = v1.begin() - v1.end();
	cout << "dist " << dist <<endl;
	
	return 0;
}
