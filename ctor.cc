#include <iostream>

struct A {
	A(): m_a(22) {
	}
	int m_a;
};

struct B {
	B(): m_b(33) {
	}
	A a1;
	int m_b;
};


int main() {
	B b1;
	std::cout << b1.a1.m_a <<std::endl;
}
