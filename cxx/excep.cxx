#include <iostream>
#include <exception>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

using std::exception;
using namespace std;

void handler(int sig) {
	void *array[30];
	size_t size;
	size = backtrace(array, end(array) - begin(array));
	fprintf(stderr, "Error: signal %d:\n", sig);
	backtrace_symbols_fd(array, size, STDERR_FILENO);
}


void bar() {
	throw "hello";
}

void foo() {
	bar();
}

void test_excep(int t) {
	foo();
}

int main() {
	signal(SIGABRT, handler);
	test_excep(0);
	return 0;
}