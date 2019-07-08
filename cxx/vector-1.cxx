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
	for (auto i : v1) {
		cout << i << endl;
	}
	cout<< "size type " << sizeof(vector<int>::size_type) << endl;
	cout<< "size "<< v1.size() << "/" << v1.max_size() <<endl;
	return 0;
}
