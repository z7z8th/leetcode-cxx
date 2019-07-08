#include <iostream>

class A {
public:
	A() = default;
	A(int aa) : a(aa) {
	}
	A(A&& rhs) :
		a(rhs.a)
	{
		std::cout<< "mov ctor of A"<< std::endl;
	}
	int a;
};

class B : public A {
public:
	B () : b(0) {
	}
	B (int aa, int bb): A(aa), b(bb) {
	}
	B(B&& rhs) :
		A(std::move(rhs)),
		b(rhs.b)
	{
		std::cout<< "mov ctor of B"<< std::endl;
	}
	int b;
	void print() {
		std::cout<< "a "<< a << " b " << b <<std::endl;
	}

};

int main() {
	B b1(1, 2);
	B b2(std::move(b1));
	b1.print();
	b2.print();
}
