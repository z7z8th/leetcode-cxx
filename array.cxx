#include <iostream>

int main() {
	using int_arr = int[14];
	int_arr abc = { 1, 3, 4, 6, 8, 90};
	for (auto i : abc) {
		std::cout << "abc " << i << std::endl;
	}
}