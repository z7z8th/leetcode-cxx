#include <iostream>
using std::cout;
using std::endl;
int main(int argc, const char *argv[]) {
	int i = 0;
	int j = 3;
	const int *p = &i;
	//*p = 12;
	int * const p2 = &i;
	*p2 = 5;
	//p2 = &j;
	return 0;
}