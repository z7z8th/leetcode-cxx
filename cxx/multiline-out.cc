#include <iostream>

int main() {
	std::cout<< 
		R"(
			hello
			world
		)" <<std::endl;
	std::wcout<< 
		LR"(
			wide hello
			wide world
		)" <<std::endl;
	return 0;
}
