#include <iostream>

class A {

	public:
		A() = default;
		A(int a1, int b1) {
			a = a1;
			b = b1;
		}
		int geta() const {
			return a;
		}
	private:
	int a;
	int b;

};

int main() {
	A a1 {1, 2};
	A a2 {3, 4};
	std::swap(a1, a2);
	std::cout << a1.geta()<<std::endl;;
	return 0;
}
