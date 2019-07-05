#include <iostream>


int main() {
    int a= 10;
    int &b = a;
    int *pa = &a;
    int *pb = &b;
    std::cout << "pa " << pa << std::endl;
    std::cout << "pb " << pb << std::endl;
}
